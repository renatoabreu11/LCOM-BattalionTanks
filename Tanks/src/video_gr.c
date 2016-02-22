#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "video_gr.h"
#include "vbe.h"

/* Constants for VBE 0x105 mode */

/* Private global variables */

static char *video_mem; /* Process address to which VRAM is mapped */
static char *Buffer; // in order to avoid flickering of the animations

static unsigned h_res; /* Horizontal screen resolution in pixels */
static unsigned v_res; /* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

int vg_exit() {
	struct reg86u reg86;

	reg86.u.b.intno = 0x10; /* BIOS video services */

	reg86.u.b.ah = 0x00; /* Set Video Mode function */
	reg86.u.b.al = 0x03; /* 80x25 text mode*/

	if (sys_int86(&reg86) != OK) {
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}

void *vg_init(unsigned short mode) {
	struct reg86u r;
	 r.u.w.ax = SET_VBE_MODE; // VBE call, function 02 -- set VBE mode
	 r.u.w.bx = 1 << 14 | mode; // set bit 14: linear framebuffer with mode passed as arg
	 r.u.b.intno = VIDEO_BIOS;
	 if (sys_int86(&r) != OK) {
	 printf("set_vbe_mode: sys_int86() failed \n");
	 return;
	 }


	vbe_mode_info_t video_mode_info;
	if (vbe_get_mode_info(mode, &video_mode_info) != 0) {
		printf("\nvbe_get_mode_info error\n");
		return;
	}

	h_res = video_mode_info.XResolution;
	v_res = video_mode_info.YResolution;
	bits_per_pixel = video_mode_info.BitsPerPixel;

	struct mem_range mr;
	/* Allow memory mapping */

	mr.mr_base = (phys_bytes)(video_mode_info.PhysBasePtr);
	mr.mr_limit = mr.mr_base + (h_res * v_res*bits_per_pixel)/8;

	if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))
		panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *) mr.mr_base,
			(h_res * v_res*bits_per_pixel)/8);
	Buffer = (char*) malloc((h_res * v_res*bits_per_pixel)/8);

	if (video_mem == MAP_FAILED)
		panic("video_txt couldn't map video memory");

	return video_mem;
}

void* getBuffer() {
	return Buffer;
}

void* get_video_mem() {
	return video_mem;
}

unsigned get_h_res() {

	return h_res;
}

unsigned get_v_res() {

	return v_res;
}

unsigned get_bytes_per_pixel() {
	return bits_per_pixel;
}

void updateScreenWithBuffer(){
	memcpy(video_mem, Buffer, h_res * v_res*bits_per_pixel/8);
}

void clearBuffer(){
	memset(Buffer, 0, h_res * v_res * bits_per_pixel/8);
}

void clearVideoMem(){
	memset(video_mem, 0, h_res * v_res * bits_per_pixel/8);
}

int vg_set_pixel(unsigned int x, unsigned int y, char color) {
	if(x < 0 || y < 0)
		return 1;

	*(Buffer + (x + y * h_res) * bits_per_pixel / 8) = color;
	*(Buffer + 1 + (x + y * h_res) * bits_per_pixel / 8) = color;
	return 0;
}

int vg_draw_rectangle(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {
	unsigned long i, j, xf = x + size, yf = y + size;

	if (x > h_res || y > v_res || xf > h_res || yf > v_res)
		return 1;

	for (i = y; i < yf; i++) {
		for (j = x; j < xf; j++) {
			if(vg_set_pixel(j, i, color) != 0)
		       return 1;
		}
	}
	return 0;
}

int vg_draw_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color) {
	if (xi > h_res || yi > v_res || xf > h_res || yf > v_res)
		return 1;

	//Digital Differential Analyzer (DDA) algorithm
	float x, y, steps, Xinc, Yinc;
	x = xi, y = yi;
	float dx = xf - xi;
	float dy = yf - yi;
	float m = dy / dx;
	unsigned int i;

	if (m > 1) {
		if (fabs(dx) > fabs(dy))
			steps = abs(dx);
		else
			steps = abs(dy);
	}
	else {
		if (fabs(dy) > fabs(dx))
			steps = abs(dy);
		else
			steps = abs(dx);
	}

	Xinc = dx / steps;
	Yinc = dy / steps;

	for (i = 0; i < steps; i++) {
		if (vg_set_pixel(x, y, color) != 0)
			return 1;
		x = x + Xinc;
		y = y + Yinc;
	}

	return 0;
}



int vg_draw_xpm(unsigned short xi, unsigned short yi, unsigned short width, unsigned short height, char * map){
	unsigned short xf = xi + width;
	unsigned short yf = yi + height;

	if (xi > h_res || yi > v_res || xf > h_res || yf > v_res)
		return 1;

	unsigned int i, j, x = 0;
	for (i = yi; i < yf; i++) {
		for (j = xi; j < xf; j++, x++) {
			if (vg_set_pixel(j, i, map[x]) != 0)
				return 1;
		}
	}
	return 0;
}

void vg_clear() {
	unsigned int i, j;
	for (i = 0; i < V_RES; i++) {
		for (j = 0; j < H_RES; j++) {
			vg_set_pixel(j, i, 0);
		}
	}
}



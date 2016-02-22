#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

#define VRAM_PHYS_ADDR		0xF0000000
#define H_RES           	1024
#define V_RES		  		768
#define BITS_PER_PIXEL		8

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 * 
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen, 
 *  and the number of colors
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

/**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 * 
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

/**
  * @brief Returns buffer pointer
 *
 * @return  buffer pointer
 */
void* getBuffer();

/**
 * @brief Returns video memory address
 *
 * @return Video memory address
 */
void* get_video_mem(void);

/**
 * @brief Returns horizontal resolution static variable
 *
 * @return Horizontal resolution
 */
unsigned get_h_res(void);

/**
 * @brief Returns vertical resolution static variable
 *
 * @return Vertical resolution
 */
unsigned get_v_res(void);

/**
 * return the number of bytes per pixel
 */
unsigned get_bytes_per_pixel();

/**
 * @brief clear double buffer
 *
 * @return
 */
void clearBuffer();

/**
 * @brief swap between video mem and double buffer
 *
 * @return
 */
void updateScreenWithBuffer();

/**
 * @brief Changes a pixel color to the input value
 *
 * Sets the color of the pixel at the specified position to the input value,
 *  by writing to the corresponding location in VRAM
 *
 * @param x horizontal position, 0 < x < h_res
 * @param y vertical position, 0 < y < v_res
 * @param color new pixel color
 * @return 0 on success, non-zero otherwise
 */
int vg_set_pixel(unsigned int x, unsigned int y, char color);

/**
 * @brief Changes the color of a rectangular area to the input value
 *
 * Sets the color of all the pixels within the specified limits to the input value,
 *  by looping vg_set_pixel
 *
 * @param x horizontal position, 0 < x < h_res
 * @param y vertical position, 0 < y < v_res
 * @param new area color
 * @return 0 on success, non-zero otherwise
 */
 int vg_draw_rectangle(unsigned short x, unsigned short y, unsigned short size, unsigned long color);

 /**
  * @brief draw a line on screen
  *
  * @param xi horizontal position, 0 < x < h_res
  * @param yi vertical position, 0 < y < v_res
  * @param xf horizontal final position, 0 < x < h_res
  * @param yf vertical final position, 0 < y < v_res
  * @param new area color
  * @return 0 on success, non-zero otherwise
  */
 int vg_draw_line(unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, unsigned long color);

 /**
  * @brief draw a xmp passed as arg on screen
  *
  * Sets the color of all the pixels within the specified limits to the input value,
  *  by looping vg_set_pixel
  *
  * @param x horizontal position, 0 < x < h_res
  * @param y vertical position, 0 < y < v_res
  * @param horizontal length
  * @param vertical length
  * @param xmp
  * @return 0 on success, non-zero otherwise
  */
 int vg_draw_xpm(unsigned short xi, unsigned short yi, unsigned short width, unsigned short height, char * map);

 /**
  * @brief clear all screen
  */
 void vg_clear();

/** @} end of video_gr */

#endif /* __VIDEO_GR_H */

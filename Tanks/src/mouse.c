#include "mouse.h"

static int hook_id;

int x = 512;
int y = 384;

Mouse* InitMouse() {
	Mouse *ms = (Mouse *) malloc(sizeof(Mouse));
	ms->x = 512;
	ms->y = 384;

	ms->leftButtonP = 0;
	ms->middleButtonP = 0;
	ms->rightButtonP = 0;

	ms->packetCounter = 0;

	ms->mouseWidth = 22;
	ms->mouseHeight = 22;
	ms->MouseBmp = loadBitmap("/home/lcom/Tanks/res/Cursor.bmp");

	return ms;
}

void deleteMouse(Mouse* ms) {
	deleteBitmap(ms->MouseBmp);
	free(ms);
}

void drawMouse(Mouse* ms, int mouse_flag) {
	drawBitmap(ms->MouseBmp, ms->x, ms->y, ALIGN_LEFT, mouse_flag);
}

int ms_subscribe_int(void) {
	hook_id = MS_IRQ;  //Mouse IRQ number is 12.
	if (sys_irqsetpolicy(MS_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id)
			!= OK) { //output the EOI command to the PIC
		printf("Irqsetpolicy failed \n");
		return -1;
	} else if (sys_irqenable((&hook_id)) != OK) { //enables interrupts on the IRQ line associated with the hook_id
		printf("Irqenable failed \n");
		return -1;
	} else
		return MS_IRQ;
}

int ms_unsubscribe_int() {

	if (sys_irqdisable(&hook_id) != OK)
		return 1;
	else if (sys_irqrmpolicy(&hook_id) != OK)
		return 1;

	else
		return 0;
}

int ms_read() {
	unsigned long stat, key;
	int i = 0;
	while (i < 10) {
		if (sys_inb(STAT_REG, &stat) != OK)
			return -1;
		if (stat & OBF) {

			sys_inb(OUT_BUF, &key);
			return key;
		}
		tickdelay(micros_to_ticks(DELAY_US));
		i++;
	}
}

int ms_write(unsigned char port, unsigned char command) {
	unsigned long stat;
	while (1) {
		/* loop while 8042 input buffer is not empty */
		if (sys_inb(STAT_REG, &stat) != OK)
			return -1;

		if ((stat & IBF) == 0) {
			sys_outb(port, command); /* no args command */
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int MS_to_KBD_Commands(unsigned char command) {
	unsigned long byte;

	do {
		ms_write(STAT_REG, MS_WRITE_BYTE); //first write command 0xD4 to the KBC, i.e. using port 0x64

		do {
			ms_write(OUT_BUF, command); // mouse command to port 0x60
			byte = ms_read(); //acknowledgment (message) in the output buffer
		} while (byte == MS_NACK); //the latest byte should be written again

	} while (byte == MS_ERROR);
}

void SetPacket(Mouse* ms) {
	ms->packet[ms->packetCounter] = ms_read();
	if (ms->packetCounter == 0 && !(ms->packet[ms->packetCounter] & BIT(3)))
		return;

	ms->packetCounter++;
}

void updateMouse(Mouse* ms, int menu_flag) {
	ms->Xsign = ms->packet[0] & BIT(4);
	ms->Ysign = ms->packet[0] & BIT(5);
	ms->Xdelta = ms->packet[1];
	ms->Ydelta = ms->packet[2];
	if (ms->Xsign)
		ms->Xdelta |= (-1 << 8);
	if (ms->Ysign)
		ms->Ydelta |= (-1 << 8);

	ms->leftButtonP = ms->packet[0] & BIT(0);
	ms->rightButtonP = ms->packet[0] & BIT(1);
	ms->middleButtonP = ms->packet[0] & BIT(2);

	if (ms->Xdelta != 0) {
		ms->x += ms->Xdelta;

		if(menu_flag){
			if (ms->x < 5)
				ms->x = 5;
			else if (ms->x + ms->mouseWidth > get_h_res() - 5)
				ms->x = get_h_res() - 5 - ms->mouseWidth;
		}
		else {
			if (ms->x < Border)
				ms->x = Border;
			else if (ms->x + ms->mouseWidth > get_h_res() - rightBorder)
				ms->x = get_h_res() - rightBorder - ms->mouseWidth;
		}
	}

	if (ms->Ydelta != 0) {
		ms->y -= ms->Ydelta;

		if(menu_flag){
			if (ms->y < 5)
				ms->y = 5;
			else if (ms->y + ms->mouseHeight > get_v_res() - 5)
				ms->y = get_v_res() - 5 - ms->mouseHeight;
		}
		else {
			if (ms->y < Border)
				ms->y = Border;
			else if (ms->y + ms->mouseHeight > get_v_res() - Border)
				ms->y = get_v_res() - Border - ms->mouseHeight;
		}
	}

	ms->Xdelta = ms->x - x;
	ms->Ydelta = ms->y - y;
	x = ms->x;
	y = ms->x;
}

void resetButtons(Mouse* ms){
	ms->leftButtonP = 0;
	ms->rightButtonP = 0;
	ms->middleButtonP = 0;
}

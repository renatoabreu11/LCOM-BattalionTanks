#ifndef __MOUSE_H
#define __MOUSE_H

#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include "i8042.h"
#include "Utilities.h"
#include "bitmap.h"

/** @defgroup mouse mouse
 * @{
 * 
 * Functions for using the mouse
 */

#define PAR_ERR BIT(7)
#define TO_ERR BIT(5)
#define OBF BIT(0)
#define IBF BIT(1)

#define Border                 24
#define rightBorder            136

typedef struct {
	int x, y;
	int Xsign, Ysign;
	int Xdelta, Ydelta;

	unsigned long packet[3];
	int packetCounter;

	int leftButtonP, middleButtonP, rightButtonP;

	int mouseWidth, mouseHeight;
	Bitmap *MouseBmp;
} Mouse;

/**
 * @brief init the mouse struct
 *
 * @param
 * @return mouse struct
 */
Mouse* InitMouse();

/**
 * @brief draw mouse bmp, in the mouse buffer, accordingly to the actual coordinates
 *
 * @param mouse struct
 * @return
 */
void drawMouse(Mouse* ms, int mouse_flag);

/**
 * @brief free all resources allocated by mouse struct
 *
 * @param mouse struct
 * @return
 */
void deleteMouse(Mouse* ms);

/**
 * @brief subscribe mouse interrupts
 *
 * @param
 * @return
 */
int ms_subscribe_int(void);

/**
 * @brief unsubscribe mouse interrupts
 *
 * @param
 * @return
 */
int ms_unsubscribe_int();

/**
 * @brief read byte from mouse buffer
 *
 * @param
 * @return the byte read
 */
int ms_read();


/**
 * @brief write command to port
 *
 * @param command to write and respective port
 * @return
 */
int ms_write(unsigned char port, unsigned char command);

/**
 * @brief first write command 0xD4 to the KBC, i.e. using port 0x64 then mouse command to port 0x60
 *
 * @param command to write
 * @return
 */
int MS_to_KBD_Commands(unsigned char command);

/**
 * @brief read a byte from mouse buffer and set the respective packet
 *
 * @param mouse struct pointer
 * @return
 */
void SetPacket(Mouse* ms);

/**
 * @brief when the 3 bytes packet is read, update the mouse accordingly to the information in those packets
 *        the menu flag means if the actual game state is  menu or playing
 *
 * @param mouse struct pointer
 * @return
 */
void updateMouse(Mouse* ms, int menu_flag);

#endif

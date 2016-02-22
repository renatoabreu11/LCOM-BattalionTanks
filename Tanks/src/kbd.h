#ifndef __KBD_H
#define __KBD_H

#include "i8042.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/sysutil.h>
#include <stdbool.h>

/** @defgroup kbd kbd
 * @{
 * 
 * Functions for using the keyboard
 */

#define KBD_IRQ		1
#define BIT(n) (0x01<<(n))
#define PAR_ERR BIT(7)
#define TO_ERR BIT(5)
#define OBF BIT(0)
#define IBF BIT(1)

typedef enum {
	ESC = 0x01,
	k1 = 0x02,
	k2 = 0x03,
	k3 = 0x04,
	k4 = 0x05,
	k5 = 0x06,
	k6 = 0x07,
	k7 = 0x08,
	k8 = 0x09,
	k9 = 0x0A,
	k0 = 0x0B,
	kQ = 0x10,
	kW = 0x11,
	kE = 0x12,
	kR = 0x13,
	kT = 0x14,
	kY = 0x15,
	kU = 0x16,
	kI = 0x17,
	kO = 0x18,
	kP = 0x19,
	kA = 0x1E,
	kS = 0x1F,
	kD = 0x20,
	kF = 0x21,
	kG = 0x22,
	kH = 0x23,
	kJ = 0x24,
	kK = 0x25,
	kL = 0x26,
	kZ = 0x2C,
	kX = 0x2D,
	kC = 0x2E,
	kV = 0x2F,
	kB = 0x30,
	kN = 0x31,
	kM = 0x32,
	kSPACE = 0x39,
	kENTER = 0xE01C,
	kUp = 0xE048,
	kLeft = 0xE04B,
	kRight = 0xE04D,
	kDown = 0xE050,
	BreakUp = 0xE0C8,
	BreakLeft = 0xE0CB,
	BreakRight = 0xE0CD,
	BreakDown = 0xE0D0,
} KEY;

/**
 * @brief reads the bytes from the Keyboard OUT_BUF
 *
 * @param
 * @return the byte readed
 */
int kbd_read();

/**
 * @brief subscribe the keyboard interruptions
 *
 * @param
 * @return 1 if sucessfull
 */
int kbd_subscribe_int(void );

/**
 * @brief unsubscribe the keyboard interruptions
 *
 * @param
 * @return 1 if sucessfull
 */
int kdb_unsubscribe_int();

/**
 * @brief write a command to the keyboard
 *
 * @param
 * @return 1 if sucessfull
 */
int kbd_write(unsigned char command);

/**
 * @brief read notifcations given by the keyboard during the interrup loop until esc key is pressed
 *
 * @param
 * @return
 */
int kbd_scan(unsigned long key_code);

/**
 * @brief receive a key from kbd interruption and return that key in the equivalent ascii code
 *
 * @param
 * @return the ascii code of key
 */
char MinixKeyToAscii(KEY minixKey);

#endif /* _KBD_H */

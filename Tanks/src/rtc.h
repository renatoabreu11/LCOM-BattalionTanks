#ifndef __RTC_H
#define __RTC_H

#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include "i8042.h"
#include "Utilities.h"
#include "font.h"

/** @defgroup rtc rtc
 * @{
 * 
 * 
 * Functions for using the real time clock
 */

#define RTC_IRQ				8
#define SECONDS				0x00
#define MINUTES				0x02
#define HOURS				0x04
#define WEEKDAYS			0x06
#define DAYS				0x07
#define MONTHS				0x08
#define YEARS				0x09

typedef struct {
	unsigned long seconds;
	unsigned long minutes;
	unsigned long hours;
	unsigned long weekday;
	unsigned long day;
	unsigned long month;
	unsigned long year;
} Date;

/**
 * @brief subscribe rtc
 *
 * @param
 * @return RTC_IRQ if sucess, -1 otherwise
 */
int rtc_subscribe_int();

/**
 * @brief unsubscribe rtc
 *
 * @param
 * @return 0 if sucess, 1 otherwise
 */
int rtc_unsubscribe_int();

/**
 * @brief transform char in bcd to bin
 *
 * @param bcd char
 * @return char passed as argument in binary
 */
unsigned char bcd_to_bin(unsigned char bcd);

/**
 * @brief get the ascii code
 *
 * @param int
 * @return ascii code of respective int
 */
unsigned char int_to_char(int n);

/**
 * @brief init the date struct
 *
 * @param
 * @return date struct
 */
Date* InitDate();

/**
 * @brief update the date struct members acordingly to the rtc registers
 *
 * @param date struct
 * @return
 */
void updateDate(Date* d);

/**
 * @brief draw actual date to the buffer
 *
 * @param date struct, and coordinates to start drawing
 * @return
 */
void drawDate(Date* d, int x, int y);

/**
 * @brief free all resources allocated by date struct
 *
 * @param date struct
 * @return
 */
void deleteDate(Date* d);

#endif

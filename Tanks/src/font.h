#ifndef __FONT_H
#define __FONT_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "video_gr.h"
#include "Utilities.h"
#include <ctype.h>

/** @defgroup Font Font
 * @{
 * 
 * Functions related to the font system
 * used for variable text
 */

typedef struct {
	Bitmap* character;
} Font;

typedef struct {
	Bitmap* bmp0;
	Bitmap* bmp1;
	Bitmap* bmp2;
	Bitmap* bmp3;
	Bitmap* bmp4;
	Bitmap* bmp5;
	Bitmap* bmp6;
	Bitmap* bmp7;
	Bitmap* bmp8;
	Bitmap* bmp9;
	Bitmap* bmp_colon;
	Bitmap* bmp_dash;
} SmallFont;

/**
 * @brief init of font struct
 *
 * @param
 * @return pointer to the font struct
 */
Font* InitFont();

/**
 * @brief this function draws on the buffer the char passed as arg
 *
 * @param pointer to struct font, char to be wrote, x and y position
 * @return
 */
void drawChar(Font *font, char ch, int x, int y);

/**
 * @brief this function draws on the buffer the text passed as arg. In order to do this it calls the function draw char
 * to each character in the text
 *
 * @param pointer to struct font, text to be wrote, x and y position
 * @return
 */
void drawText(Font *font, char text[], int x, int y);

/**
 * @brief free all resources used by the font struct
 *
 * @param pointer to struct font
 * @return
 */
Font* deleteFont(Font* font);

/**
 * @brief init of smallfont struct (struct used to draw the current hours)
 *
 * @param
 * @return pointer to the smallfont struct
 */
SmallFont* InitSmallFont();

/**
 * @brief this function draws on the buffer the char passed as arg but with a small bitmap
 *
 * @param pointer to struct font, char to be wrote, x and y position
 * @return
 */
void drawSmallChar(SmallFont *f, char ch, int x, int y);

/**
 * @brief free all resources used by the struct
 *
 * @param pointer to struct font
 * @return
 */
void deleteSmallFont(SmallFont* font);

#endif

#include "font.h"

Font* InitFont() {
	Font * font = (Font *) malloc(sizeof(Font));
	if (font == NULL)
		return NULL;
	font->character = NULL;
}

void drawChar(Font *font, char ch, int x, int y) {
	char *labelPtr;
	char str1[] = "/home/lcom/Tanks/res/font/0.bmp";
	ch = toupper(ch);
	labelPtr = str1;
    labelPtr[26] = ch;
    font->character = loadBitmap(str1);
    drawBitmap(font->character, x, y, ALIGN_LEFT, 0);
}

void drawText(Font *font, char text[], int x, int y) {
	char *labelPtr;
	labelPtr = text;
	int i = 0;
	for (i; i < strlen(text); i++) {
		drawChar(font, labelPtr[i], x, y);
		x += 30;
	}
}

Font* deleteFont(Font* font){
	deleteBitmap(font->character);
}

SmallFont* InitSmallFont() {
	SmallFont * f = (SmallFont *) malloc(sizeof(SmallFont));
	if (f == NULL)
		return NULL;
	f->bmp0 = loadBitmap("/home/lcom/Tanks/res/font/s0.bmp");
	f->bmp1 = loadBitmap("/home/lcom/Tanks/res/font/s1.bmp");
	f->bmp2 = loadBitmap("/home/lcom/Tanks/res/font/s2.bmp");
	f->bmp3 = loadBitmap("/home/lcom/Tanks/res/font/s3.bmp");
	f->bmp4 = loadBitmap("/home/lcom/Tanks/res/font/s4.bmp");
	f->bmp5 = loadBitmap("/home/lcom/Tanks/res/font/s5.bmp");
	f->bmp6 = loadBitmap("/home/lcom/Tanks/res/font/s6.bmp");
	f->bmp7 = loadBitmap("/home/lcom/Tanks/res/font/s7.bmp");
	f->bmp8 = loadBitmap("/home/lcom/Tanks/res/font/s8.bmp");
	f->bmp9 = loadBitmap("/home/lcom/Tanks/res/font/s9.bmp");
	f->bmp_colon = loadBitmap("/home/lcom/Tanks/res/font/colon.bmp");
	f->bmp_dash = loadBitmap("/home/lcom/Tanks/res/font/dash.bmp");
	return f;
}

void drawSmallChar(SmallFont *f, char ch, int x, int y) {
	switch(ch) {
	case '0':
		drawBitmap(f->bmp0, x, y, ALIGN_LEFT, 0);
		break;
	case '1':
		drawBitmap(f->bmp1, x, y, ALIGN_LEFT, 0);
		break;
	case '2':
		drawBitmap(f->bmp2, x, y, ALIGN_LEFT, 0);
		break;
	case '3':
		drawBitmap(f->bmp3, x, y, ALIGN_LEFT, 0);
		break;
	case '4':
		drawBitmap(f->bmp4, x, y, ALIGN_LEFT, 0);
		break;
	case '5':
		drawBitmap(f->bmp5, x, y, ALIGN_LEFT, 0);
		break;
	case '6':
		drawBitmap(f->bmp6, x, y, ALIGN_LEFT, 0);
		break;
	case '7':
		drawBitmap(f->bmp7, x, y, ALIGN_LEFT, 0);
		break;
	case '8':
		drawBitmap(f->bmp8, x, y, ALIGN_LEFT, 0);
		break;
	case '9':
		drawBitmap(f->bmp9, x, y, ALIGN_LEFT, 0);
		break;
	case ':':
		drawBitmap(f->bmp_colon, x, y, ALIGN_LEFT, 0);
		break;
	case '-':
		drawBitmap(f->bmp_dash, x, y, ALIGN_LEFT, 0);
		break;
	}
}

void deleteSmallFont(SmallFont* f){
	deleteBitmap(f->bmp0);
	deleteBitmap(f->bmp1);
	deleteBitmap(f->bmp2);
	deleteBitmap(f->bmp3);
	deleteBitmap(f->bmp4);
	deleteBitmap(f->bmp5);
	deleteBitmap(f->bmp6);
	deleteBitmap(f->bmp7);
	deleteBitmap(f->bmp8);
	deleteBitmap(f->bmp9);
	deleteBitmap(f->bmp_colon);
	deleteBitmap(f->bmp_dash);
	free(f);
}

#include "bitmap.h"
#include "stdio.h"
#include "video_gr.h"
#include "math.h"

Bitmap* loadBitmap(const char* filename) {
	// allocating necessary size
	Bitmap* bmp = (Bitmap*) malloc(sizeof(Bitmap));

	// open filename in read binary mode
	FILE *filePtr;
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	BitmapFileHeader bitmapFileHeader;
	fread(&bitmapFileHeader, 2, 1, filePtr);

	// verify that this is a bmp file by check bitmap id
	if (bitmapFileHeader.type != 0x4D42) {
		fclose(filePtr);
		return NULL;
	}

	int rd;
	do {
		if ((rd = fread(&bitmapFileHeader.size, 4, 1, filePtr)) != 1)
			break;
		if ((rd = fread(&bitmapFileHeader.reserved, 4, 1, filePtr)) != 1)
			break;
		if ((rd = fread(&bitmapFileHeader.offset, 4, 1, filePtr)) != 1)
			break;
	} while (0);

	if (rd = !1) {
		fprintf(stderr, "Error reading file\n");
		exit(-1);
	}

	// read the bitmap info header
	BitmapInfoHeader bitmapInfoHeader;
	fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);

	// move file pointer to the begining of bitmap data
	fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

	// allocate enough memory for the bitmap image data
	unsigned char* bitmapImage = (unsigned char*) malloc(
			bitmapInfoHeader.imageSize);

	// verify memory allocation
	if (!bitmapImage) {
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, bitmapInfoHeader.imageSize, 1, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL) {
		fclose(filePtr);
		return NULL;
	}

	// close file and return bitmap image data
	fclose(filePtr);

	bmp->bitmapData = bitmapImage;
	bmp->bitmapInfoHeader = bitmapInfoHeader;

	return bmp;
}

void drawBitmap(Bitmap* bmp, int x, int y, Alignment alignment, int mouse_flag) {
	if (bmp == NULL)
		return;

	int width = bmp->bitmapInfoHeader.width;
	int drawWidth = width;
	int height = bmp->bitmapInfoHeader.height;

	if (alignment == ALIGN_CENTER)
		x -= width / 2;
	else if (alignment == ALIGN_RIGHT)
		x -= width;

	if (x + width < 0 || x > get_h_res() || y + height < 0 || y > get_v_res())
		return;

	int xCorrection = 0;
	if (x < 0) {
		xCorrection = -x;
		drawWidth -= xCorrection;
		x = 0;

		if (drawWidth > get_h_res())
			drawWidth = get_h_res();
	} else if (x + drawWidth >= get_h_res()) {
		drawWidth = get_h_res() - x;
	}

	char* bufferStartPos;
	char* imgStartPos;

	int i, j;
	for (i = 0; i < height; i++) {
		int pos = y + height - 1 - i;

		if (pos < 0 || pos >= get_v_res())
			continue;

		if (mouse_flag)
			bufferStartPos = get_video_mem();
		else
			bufferStartPos = getBuffer();

		bufferStartPos += x * 2 + (pos + 1) * get_h_res() * 2;

		for (j = 0; j < width * 2; j++, bufferStartPos++) {
			if (x + j < 0 || x * 2 + j >= get_h_res() * 2)
				continue;

			int pos = j + i * width * 2;
			unsigned short tmp1 = bmp->bitmapData[pos];
			unsigned short tmp2 = bmp->bitmapData[pos + 1];
			unsigned short temp = (tmp1 | (tmp2 << 8));

			if (temp != 2016) { //2016 is the rgb code for green in base 10
				*bufferStartPos = bmp->bitmapData[j + i * width * 2];
				j++;
				bufferStartPos++;
				*bufferStartPos = bmp->bitmapData[j + i * width * 2];
			} else {
				j++;
				bufferStartPos++;
			}
		}
	}
}

void rotateBitmap(Bitmap* bmp, int n){
	if (bmp == NULL)
		return;

	int width = bmp->bitmapInfoHeader.width;
	int height = bmp->bitmapInfoHeader.height;

	unsigned char* newMap = (unsigned char*) malloc(
			bmp->bitmapInfoHeader.imageSize);

	int i, j;

	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++) {
			if(n == -6 || n == 2){
				*(newMap + ((height - i - 1)*width + j) * 2)= *(bmp->bitmapData
						+ (j * width + i) * 2);
				*(newMap + ((height - i - 1)*width + j) * 2 + 1) =
						*(bmp->bitmapData + (j * width + i) * 2 + 1);
			}
			else if (abs(n) == 4){
				*(newMap + ((height- j - 1)*width  + width - i - 1) * 2) = *(bmp->bitmapData
						+ (j * width + i) * 2);
				*(newMap + ((height- j - 1)*width  + width - i - 1) * 2 + 1) =
						*(bmp->bitmapData + (j * width + i) * 2 + 1);
			}
			else if (n == -2 || n == 6) {
				*(newMap + (height - j - 1 + i * height) * 2) =
						*(bmp->bitmapData + (j * width + i) * 2);
				*(newMap + (height - j - 1 + i * height) * 2 + 1) =
						*(bmp->bitmapData + (j * width + i) * 2 + 1);
			}
		}
	bmp->bitmapData = newMap;
}


void deleteBitmap(Bitmap* bmp) {
	if (bmp == NULL)
		return;

	free(bmp->bitmapData);
	free(bmp);
}

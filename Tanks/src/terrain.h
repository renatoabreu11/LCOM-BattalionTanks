#ifndef __TERRAIN_H
#define __TERRAIN_H
#include "video_gr.h"
#include "bitmap.h"
#include "font.h"

/** @defgroup terrain terrain
 * @{
 * 
 * Functions for managing the game terrain
 */

/**
 * The game will use 864*720 pixels, so each cell will have 36 pixels
 *
 * 0 is floor bmp
 * 1 is grass bmp
 * 2 is wall bmp
 * 3 is mini tank bmp
 * 4 is score bmp
 * 5 is live bmp
 */

#define CellSize          36
#define HorizontalCells   24
#define VerticalCells     20
#define CellInitialPos    24
#define Width             864
#define Height            720
#define BarInitialX       895
#define arraySize         480
#define LateralBarSize    60
#define ScreenWidth       1024

typedef struct{
	Bitmap * grass;
	Bitmap * wall;
	Bitmap * live;
	Bitmap * score;
	Bitmap * minitank;
	Bitmap * secondLive;
	int cells[arraySize];
	int lateralBar[LateralBarSize];
}Terrain;

/**
 * @brief initialize the terrain
 *
 * @param
 * @return pointer to terrain struct
 */
Terrain* InitTerrain(int multiplayerflag);

/**
 * @brief draw all bitmaps that belong to terrain struct
 *
 * @param pointer to terrain struct
 * @return
 */
void drawTerrain(Terrain* terr);

/**
 * @brief delete all resources allocated by the terrain struct
 *
 * @param pointer to terrain struct
 * @return
 */
void deleteTerrain(Terrain* terr);

#endif

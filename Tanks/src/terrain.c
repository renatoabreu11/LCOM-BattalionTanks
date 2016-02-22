#include "terrain.h"

Terrain* InitTerrain(int multiplayerflag){
     Terrain * terr = (Terrain*)malloc(sizeof(Terrain));
     terr->grass = loadBitmap("/home/lcom/Tanks/res/Grass.bmp");
     terr->wall = loadBitmap("/home/lcom/Tanks/res/Wall.bmp");
     terr->live = loadBitmap("/home/lcom/Tanks/res/Live.bmp");
     terr->secondLive = loadBitmap("/home/lcom/Tanks/res/Live2.bmp");
     terr->score = loadBitmap("/home/lcom/Tanks/res/Score.bmp");
     terr->minitank = loadBitmap("/home/lcom/Tanks/res/MiniTank.bmp");
     int cellsBmp[arraySize] = {
    		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1,
			 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
			 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     };

     if(multiplayerflag){
    	 int RightBarBmp[LateralBarSize] = {
    	     	    		     -1, -1, -1,
    	     					 -1, -1, -1,
								 10, 11, 12,
								 -1, 2, -1,
								 -6, -6, -6,
								 -6, -6, -6,
								 -1, -1, -1,
								 -1, -1, -1,
								 -1, -1, -1,
    	     					 -1, -1, -1,
    	     					 -1, -1, -1,
								 -1, -1, -1,
								 -1, -1, -1,
								 10, 11, 12,
    	     					 -1, 1, -1,
    	     					 -5, -5, -5,
    	     					 -1, -1, -1,
								 -1, -1, -1,
    	     					 -1, -1, -1,
    	     					 -1, -1, -1,
    	     	          };
    	  memcpy(terr->lateralBar, RightBarBmp, LateralBarSize*sizeof(int));
     }
     else{
    	 int RightBarBmp[LateralBarSize] = {
    	    		     -1, -1, -1,
    					 -1, -1, -1,
    					 -3, -3, -3,
    					 -3, -3, -3,
    					 -3, -3, -3,
    					 -3, -3, -3,
    					 -3, -3, -3,
    					 -3, -3, -3,
    					 -3, -3, -3,
    					 -1, -1, -1,
    					 -1, -1, -1,
    					 -1, -1, -1,
    					 -4, -1, -1,
    					 -1, -1, -1,
    					 0, 0, 0,
    					 -1, -1, -1,
    					 -1, -1, -1,
    					 -5, -5, -5,
    					 -1, -1, -1,
    					 -1, -1, -1,
    	          };
    	  memcpy(terr->lateralBar, RightBarBmp, LateralBarSize*sizeof(int));
     }

     memcpy(terr->cells, cellsBmp, arraySize*sizeof(int));
     return terr;
}

void drawTerrain(Terrain* terr){
	int i= 0, j = 0;
	int Xpos = CellInitialPos;
	int Ypos = CellInitialPos;
	for(; i < arraySize; i++){
		switch (terr->cells[i]) {
		case 1:
			drawBitmap(terr->grass, Xpos, Ypos, ALIGN_LEFT, 0);
			break;
		case 2:
			drawBitmap(terr->wall, Xpos, Ypos, ALIGN_LEFT, 0);
			break;
		}
		Xpos = Xpos + CellSize;
		if (Xpos == Width + CellInitialPos) {
			Xpos = CellInitialPos;
			Ypos += CellSize;
		}
    }

	Font * font = InitFont();
	Xpos = BarInitialX;
	Ypos = CellInitialPos;
	for (; j < LateralBarSize; j++) {
		if(terr->lateralBar[j] >= 0){
			if (terr->lateralBar[j] == 10)
				drawChar(font, 'T', Xpos, Ypos);
			else if (terr->lateralBar[j] == 11)
				drawChar(font, 'N', Xpos, Ypos);
			else if (terr->lateralBar[j] == 12)
				drawChar(font, 'K', Xpos, Ypos);
			else
				drawChar(font, terr->lateralBar[j] + '0', Xpos, Ypos);
		}
		switch (terr->lateralBar[j]) {
		case -3:
			drawBitmap(terr->minitank, Xpos, Ypos, ALIGN_LEFT, 0);
			break;
		case -4:
			drawBitmap(terr->score, Xpos + 7, Ypos, ALIGN_LEFT, 0);
			break;
		case -5:
			drawBitmap(terr->live, Xpos, Ypos, ALIGN_LEFT, 0);
			break;
		case -6:
			drawBitmap(terr->secondLive, Xpos, Ypos, ALIGN_LEFT, 0);
			break;
		}
		Xpos = Xpos + CellSize + 7;
		if (Xpos == ScreenWidth) {
			Xpos = BarInitialX;
			Ypos += CellSize;
		}
	}
	deleteFont(font);
}

void deleteTerrain(Terrain* terr){
     deleteBitmap(terr->grass);
     deleteBitmap(terr->wall);
     deleteBitmap(terr->live);
     deleteBitmap(terr->score);
     deleteBitmap(terr->minitank);
     deleteBitmap(terr->secondLive);
     free(terr);
}

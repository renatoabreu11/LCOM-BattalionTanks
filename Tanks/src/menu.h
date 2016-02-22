#ifndef __MENU_H
#define __MENU_H

#include "bitmap.h"
#include "mouse.h"
#include "rtc.h"
#include "font.h"
#include "kbd.h"

/** @defgroup menu menu
 * @{
 * 
 * Functions related to the Menus 
 * (Main, Pause, Highscores, and Save)
 */

#define Title1X       		312
#define Title1Y       		50
#define Title2X       		312
#define Title2Y       		150
#define SinglePlayX       	100
#define SinglePlayY        	275
#define MultiPlayX       	400
#define MultiPlayY      	400
#define HighScoreX  		200
#define HighScoreY  		525
#define ExitX       		400
#define ExitY       		650
#define ResumeX       		312
#define ResumeY       		200
#define Exit2X       		312
#define Exit2Y       		500
#define MenuWidth       	394
#define MenuHeight      	70
#define Exit3X       		74
#define Exit3Y       		624
#define HighScore2X  		312
#define HighScore2Y  		50

//****************************************Main Menu****************************************//

typedef struct{
	Bitmap* Title1Bmp;
	Bitmap* Title2Bmp;
	Bitmap* SinglePlayBmp;
	Bitmap* MultiPlayBmp;
	Bitmap* HighScoreBmp;
	Bitmap* ExitBmp;
	Bitmap* Highlight;

	int singlePlay;
	int multiPlay;
	int highScores;
	int exit;

	int option;

}MainMenu;

/**
 * @brief init of main menu struct
 *
 * @param
 * @return pointer to the main menu struct
 */
MainMenu* InitMainMenu();

/**
 * @brief update all the flags accordingly to mouse input
 *
 * @param pointer to the main menu struct and mouse
 * @return
 */
void updateMainMenu(MainMenu* mm, Mouse* ms);

/**
 * @brief draw all bmps to the buffer
 *
 * @param pointer to the main menu struct
 * @return
 */
void drawMainMenu(MainMenu* mm, Date* d);

/**
 * @brief free all resources allocated by main menu struct
 *
 * @param pointer to the main menu struct
 * @return
 */
void deleteMainMenu(MainMenu* mm);

/**
 * @brief check if mouse actual position is over the bmp
 *
 * @param x and y are the initial coordinates of the bmp
 * @return 1 if is over, 0 otherwise
 */
int MouseOverBmp(int x, int y, int width, int height, Mouse* ms);

//***************************************Pause Menu****************************************//

typedef struct{
	Bitmap* ResumeBmp;
	Bitmap* ExitBmp;
	Bitmap* Highlight;

	int resume;
	int exit;

	int option;

}PauseMenu;

/**
 * @brief init of pause menu struct
 *
 * @param
 * @return pointer to the pause menu struct
 */
PauseMenu* InitPauseMenu();

/**
 * @brief update all the flags accordingly to mouse input
 *
 * @param pointer to the pause menu struct and mouse
 * @return
 */
void updatePauseMenu(PauseMenu* mm, Mouse* ms);

/**
 * @brief draw all bmps to the buffer
 *
 * @param pointer to the pause menu struct
 * @return
 */
void drawPauseMenu(PauseMenu* mm);

/**
 * @brief free all resources allocated by pause menu struct
 *
 * @param pointer to the pause menu struct
 * @return
 */
void deletePauseMenu(PauseMenu* mm);

//***************************************HighScores****************************************//

typedef struct{
	Bitmap* HighScore;
	Bitmap* Highlight;
	Bitmap* Exit;

	char cells[9][14];

	int counter;
	int exit;

	int option;
}HighScores;

/**
 * @brief init of highscores struct
 *
 * @param
 * @return pointer to the highscores struct
 */
HighScores* InitHighScores();

/**
 * @brief update all the flags accordingly to mouse input
 *
 * @param pointer to HighScores struct and mouse
 * @return
 */
void updateHighScores(HighScores* hs, Mouse* ms);

/**
 * @brief draw all bmps to the buffer
 *
 * @param pointer to highscores struct
 * @return
 */
void drawHighScores(HighScores* hs);

/**
 * @brief free all resources allocated by highscores struct
 *
 * @param pointer to highscores struct
 * @return
 */
void deleteHighScores(HighScores* hs);

//***************************************SaveMenu****************************************//

typedef struct{
	Bitmap* Highlight;
	Bitmap* Highlight2;
	Bitmap* Exit;

	char key;
	int exit;
	int score;
	int option;
	int flag1, flag2, flag3;
	char Letter1;
	char Letter2;
	char Letter3;
}SaveMenu;

/**
 * @brief init of SaveMenu struct
 *
 * @param
 * @return pointer to the SaveMenu struct
 */
SaveMenu* InitSaveMenu(int score);

/**
 * @brief update all the flags accordingly to mouse input
 *
 * @param pointer to SaveMenu struct and mouse
 * @return
 */
void updateSaveMenu(SaveMenu* sm, Mouse* ms);

/**
 * @brief draw all bmps to the buffer
 *
 * @param pointer to SaveMenu struct
 * @return
 */
void drawSaveMenu(SaveMenu* sm);

/**
 * @brief free all resources allocated by SaveMenu struct
 *
 * @param pointer to SaveMenu struct
 * @return
 */
void deleteSaveMenu(SaveMenu* sm);

/**
 * @brief check if the key passed as parameter is eligible and if so, letter1, 2 or 3 is set, accordingly to the mouse position
 *
 * @param pointer to SaveMenu struct and key
 * @return
 */
void KeyboardHandler(SaveMenu* sm, int key);

#endif

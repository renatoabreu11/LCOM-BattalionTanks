#ifndef __BATTALIONTANKS_H
#define __BATTALIONTANKS_H

#include <minix/drivers.h>
#include <minix/syslib.h>
#include "stdbool.h"
#include "i8042.h"
#include "i8254.h"
#include "mouse.h"
#include "timer.h"
#include "kbd.h"
#include "rtc.h"
#include "tank.h"
#include "stdio.h"
#include "game.h"
#include "menu.h"
#include "font.h"

/** @defgroup BattalionTanks BattalionTanks
 * @{
 * 
 * Functions related to the game's state machine
 */

typedef enum {
	HighScoreS, PlayS, ExitS, MainMenuS, PauseMenuS, SaveMenuS, MultiPlayS,
} GameState;

typedef struct{
	int irq_timer;
	int irq_mouse;
	int irq_keyboard;
	int irq_rtc;

	int timer_flag;
	int keyboard_flag;
	int mouse_flag;
	int timer_counter;

	Game* g;
	MainMenu* mm;
	PauseMenu* pm;
	MultiPlayerMode* mp;
	SaveMenu* sm;
	HighScores* hs;
	GameState currentState;

	Date* d;
	Mouse* ms;
}BattalionTanks;

/**
 * @brief initialize the main struct
 *
 * @param
 * @return pointer to main struct
 */
BattalionTanks* InitBattalionTanks();


/**
 * @brief update accordingly to current state
 *
 * @param pointer to main struct
 * @return
 */
void updateBattalionTanks(BattalionTanks* bt);

/**
 * @brief delete all resources allocated by the struct
 *
 * @param pointer to main struct
 * @return
 */
void deleteBattalionTanks(BattalionTanks* bt);

/**
 * @brief interruption loop
 *
 * @param pointer to main struct
 * @return
 */
void Loop(BattalionTanks* bt);

/**
 * @brief reset timer, kbd and mouse flags
 *
 * @param pointer to main struct
 * @return
 */
void resetFlags(BattalionTanks* bt);

#endif

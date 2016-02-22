#ifndef __GAME_H
#define __GAME_H

#include "i8042.h"
#include "i8254.h"
#include "tank.h"
#include "bullet.h"
#include "mouse.h"
#include "Utilities.h"
#include "terrain.h"
#include "math.h"

/** @defgroup game game
 * @{
 * 
 * Functions related to the actual game
 */

#define Spawn            5           //number of seconds between enemy tanks to respawn

typedef struct {
	Tank* player;
	EnemyTank* enemy1;
	EnemyTank* enemy2;

	int EnemyTanks;
	int counterEnemy1;
	int counterEnemy2;

	int score;

	Terrain* GameTerrain;
} Game;

typedef struct {
	Tank* player1;
	Tank* player2;

	Terrain* GameTerrain;
} MultiPlayerMode;

/**
 * @brief init of game
 *
 * @param
 * @return pointer to the game struct
 */
Game* InitGame();

/**
 * @brief do the update of all tanks
 *
 * @param pointer to the game struct
 * @return
 */
void updateGame(Game* g);

/**
 * @brief draw of all tanks and terrain to the buffer
 *
 * @param pointer to the game struct
 * @return
 */
void drawGame(Game* g);

/**
 * @brief free all resources allocated by game struct
 *
 * @param pointer to the game struct
 * @return
 */
void deleteGame(Game* g);

/**
 * @brief check if the "square" formed by the tank passed as arg is inside a cell defined by a wall
 *
 * @param x and y left upper coordinate, pointer to terrain
 * @return 1 if brief is true, 0 otherwise
 */
int checkTankWallCollision(int x, int y, int width, int height, Terrain *terr);

/**
 * @brief check if the "square" formed by the bullet passed as arg is inside a cell defined by a wall
 *
 * @param x and y left upper coordinate, pointer to terrain
 * @return 1 if brief is true, 0 otherwise
 */
void checkBulletWallCollison(BulletPool* bp, Terrain *terr);

/**
 * @brief with the "square" formed by the points given, return the respective cell in the terrain
 *
 * @param x and y left upper coordinate, tolerance is how much pixels the square can be inside the cell and as such not considered inside that cell
 * @return the respective cell in the terrain
 */
int getCell(int x, int y, int width, int height, int tolerance);

/**
 * @brief
 *
 * @param pointer to game
 * @return 1 if the player has no more lives or 0 otherwise
 */
int OutOfLives(Game* g);

/**
 * @brief
 *
 * @param pointer to game
 * @return 1 if the battalion of enemy tanks is fully destroyed
 */
int BattalionDestroyed(Game* g);

/**
 * @brief
 *
 * @param tank x and y position, width and height, pointer to enemy tank 1 and 2, pointer to game terrain
 * @return
 */
int LineOfSight(int x, int y, int width, int height, EnemyTank * et, EnemyTank * et2,  Terrain * terr);

MultiPlayerMode* InitMultiplayerMode();

#endif

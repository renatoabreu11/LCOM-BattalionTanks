#ifndef __TANK_H
#define __TANK_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "bitmap.h"
#include "stdbool.h"
#include "kbd.h"
#include "bullet.h"
#include "video_gr.h"
#include "Utilities.h"
#include "mouse.h"

/** @defgroup tank tank
 * @{
 * 
 * Functions used for the general workings
 * of both the player tank and the enemy tanks
 */

#define InitialX               24         //Tank initial position
#define InitialY               674
#define Tank_speed             5
#define Tank_lives             3
#define EnemyTankInitialX1     94           //Enemy tank initial position
#define EnemyTankInitialY1     24
#define EnemyTankInitialX2     748         //Enemy tank secondary position
#define EnemyTankInitialY2     24
#define BulletWidth            28
#define BulletHeight           28
#define k					   (sqrt(2)-1) //trigonometric constant
#define Border                 24
#define rightBorder            136

//***************************************Tank struct*************************************************//

typedef struct{
	Bitmap* Explosion;
	int explosionNumber;
	int x;
	int y;
}TankExplosion;

typedef enum{
	rotatingCanon,
	rotatingTank,
	shooting,
	moving,
	standing,
	destroyed,
}TankState;

/*
* Orientation:
* 2 3 4
* 1 T 5
* 8 7 6
*/

typedef struct{
	int x;
	int y;
	int tnk_ori;
	int cnn_ori;
	int width;
	int height;
	double velocity;
	int kbd_key;
	int ms_x;
	int ms_y;
	Bitmap *bot_bmp;
	Bitmap *top1_bmp;
	Bitmap *top2_bmp;
	BulletPool TankAmmunition;
	TankState tankS;
	TankExplosion TankExp;
	int tankCounter;
	int lives;
	int multiplayerflag;
} Tank;

typedef struct {
	int x;
	int y;
	int ori;
	int width;
	int height;
	double velocity;
	Bitmap *bmap;
	TankExplosion TankExp;
	BulletPool TankAmmunition;
	int destroyed;
	int bulletInterval;
	int type;
	int flag;
} EnemyTank;


/**
 * @brief initialize tank object
 *
 * @param
 * @return pointer to the tank struct
 */
Tank *InitTank(int mode);

/**
 * @brief set of tank state accordingly by the key pressed by user
 *
 * @param pointer to tank object and scancode
 * @return
 */
void KeyboardInputHandler(Tank *t, int key);

/**
 * @brief set of tank state accordingly by mouse changes
 *
 * @param pointer to tank object and mouse pointer
 * @return
 */
void MouseInputHandler(Tank *t, Mouse* m);

/**
 * @brief rotate the tank accordingly to the key passed as argument
 *
 * @param pointer to tank object and pressed key
 * @return
 */
void rotateTank(Tank *t);

/**
 * @brief rotate the tank cannon accordingly to the mouse position
 *
 * @param pointer to tank object
 * @return
 */
void rotateCanon(Tank *t);

/**
 * @brief check if the tank position is out of memory range
 *
 * @param pointer to tank object
 * @return true if there is collision, false otherwise
 */
int checkBordersCollision(Tank *t);

/**
 * @brief check collision between tanks passed as arg
 *
 * @param pointer to tank object and enemy Tank
 * @return true if there is collision, false otherwise
 */
int checkTankCollision(Tank* t, EnemyTank * et1);

/**
 * @brief check collision between player tank and the bullets activated in the respective bulletpool
 *
 * @param pointer to tank object and bulletpool
 * @return
 */
void TankBulletCollision(BulletPool *bp, Tank * t);

/**
 * @brief check collision between tanks passed as arg, destroyed or not
 *
 * @param pointer to tank object and enemy Tank
 * @return true if there is collision, false otherwise
 */
int checkTankCollisionDestroyed(Tank* t, EnemyTank * et);

/**
 * @brief move the tank accordingly to the key passed as argument
 *
 * @param pointer to tank object and pressed key
 * @return 1 if there is some collision, 0 otherwise
 */
void moveTank(Tank *t);

/**
 * @brief pass to the double buffer the tank bmp
 *
 * @param pointer to tank object and pressed key
 * @return
 */
void drawTank(Tank *t);

/**
 * @brief update the tank accordingly to the information received by the kbd, mouse, etc
 *
 * @param pointer to tank
 * @return
 */
void updateTank(Tank *t);

/**
 * @brief create a new bullet that is added to the bulletpool
 *
 * @param pointer to tank object
 * @return
 */
void shootCanon(Tank *t);

/**
 * @brief free resources allocated by tank initialization
 *
 * @param pointer to tank object
 * @return
 */
void deleteTank(Tank *t);

//*********************************Enemy Tank struct**************************************************//

/**
 * @brief initialize enemy tank object
 *
 * @param i define the bmp to use
 * @return pointer to the enemy tank object
 */
EnemyTank *InitEnemyTank(int i);

/**
 * @brief move the tank randomly
 *
 * @param pointer to tank object
 * @return
 */
void moveEnemyTank(EnemyTank *et);

/**
 * @brief rotate enemy tank randomly
 *
 * @param pointer to tank object
 * @return
 */
void rotateEnemyTank(EnemyTank *et, int ori);

/**
 * @brief check if the tank will collide with another tank
 *
 * @param pointer to tank object
 * @return
 */
int checkEnemyTankCollision(EnemyTank *t1, EnemyTank *t2);

/**
 * @brief check collision between tanks passed as arg, destroyed or not
 *
 * @param pointer to tank object and enemy Tank
 * @return true if there is collision, false otherwise
 */
int checkEnemyTankCollisionDestroyed(EnemyTank *t1, EnemyTank *t2);

/**
 * @brief check if the tank will collide with the borders
 *
 * @param pointer to tank object
 * @return
 */
int checkEnemyTankBordersCollision(EnemyTank *t);

/**
 * @brief draw enemy tank bitmap
 *
 * @param pointer to tank object
 * @return
 */
void drawEnemyTank(EnemyTank *et);

/**
 * @brief free resources allocated by enemy tank initialization
 *
 * @param pointer to tank object
 * @return
 */
void deleteEnemyTank(EnemyTank *et);

/**
 * @brief create a new bullet that is added to the bulletpool
 *
 * @param pointer to tank object
 * @return
 */
void shootCanonEnemyTank(EnemyTank *t);

/**
 * @brief update the tank accordingly to the information that depends on the tank mode
 *
 * @param pointer to tank
 * @return
 */
void updateEnemyTank(EnemyTank *t, int ori, int shoot_flag);

/**
 * @brief check if the tank will collide with a bullet
 *
 * @param pointer to tank object and the bulletpool
 * @return
 */
void EnemyTankBulletCollision(BulletPool *bp, EnemyTank * t);

/**
 * @brief check if there are collisions between two bulletpools
 *
 * @param pointer to bulletpools
 * @return
 */
void BulletsCollision(BulletPool *bp, BulletPool *bp1);

#endif

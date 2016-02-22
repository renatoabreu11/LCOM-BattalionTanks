#ifndef __BULLET_H
#define __BULLET_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "video_gr.h"

/** @defgroup Bullet Bullet
 * @{
 * 
 * Functions for manipulating
 * the bullets shot by the tanks
 */

#define Border                 24
#define rightBorder            136

typedef struct Bullet{
	int x;
	int y;
	int x_vel;
	int y_vel;

	int width;
	int height;
	int bulletOrientation;

	int inUse;
	int explosion_counter;

	Bitmap* bullet_exp;
	Bitmap* bullet_bmp;
}Bullet;

typedef struct BulletPool{
	Bullet* particles_[5];
}BulletPool;

/**
 * @brief initialize bullet object
 *
 * @param x_pos - bullet position in x axis
 * y_pos - bullet position in y axis
 * x_vel - bullet velocity in x axis
 * y_vel - bullet velocity in y axis
 * cnn_orientation - current tank canon orientation which is the same orientation as the bullet
 * @return pointer to the bullet struct
 */
Bullet* InitBullet(int x_pos, int y_pos, int velx, int vely, int cnn_orientation);

/**
 * @brief initialize bullet object only with inUse defined to zero
 *
 * @param
 * @return pointer to the bullet struct
 */
Bullet* CreateBullet(int use);

/**
 * @brief update bullet coordinates
 *
 * @param pointer to bullet
 * @return
 */
void moveBullet(Bullet* b);

/**
 * @brief draw bullet to second buffer
 *
 * @param pointer to bullet
 * @return
 */
void drawBullet(Bullet* b);

/**
 * @brief check if there is collision with the screen borders
 *
 * @param pointer to bullet
 * @return 1 if yes, 0 otherwise
 */
int checkScreenCollision(Bullet *b);

/**
 * @brief delete bullet
 *
 * @param pointer to bullet
 * @return
 */
void deleteBullet(Bullet* b);

/**
 * @brief create a new bullet in the tank object pool
 *
 * @param x position of bmp
 * y position of bmp
 * xVel velocity of bmp
 * yVel velocity of bmp
 * bp - pointer to tank bullet pool
 * cnn_orientation - cannon current orientation
 * @return
 */
void create(double x, double y, double xVel, double yVel, BulletPool *bp, int cnn_orientation);

/**
 * @brief update all objects (bullets) currently used by the tank
 *
 * @param tank bulletpool
 * @return
 */
void updateBulletPool(BulletPool *bp);

/**
 * @brief draw to buffer all objects (bullets) currently used by the tank
 *
 * @param tank bulletpool
 * @return
 */
void drawBulletPool(BulletPool *bp);

/**
 * @brief free all resources used by the struct passed as arg
 *
 * @param tank bulletpool
 * @return
 */
void deleteBulletPool(BulletPool *bp);

#endif

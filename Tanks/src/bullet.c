#include "bullet.h"

/******************************* Bullet functions *****************************************/

Bullet* CreateBullet(int use){
	Bullet *b = (Bullet *) malloc(sizeof(Bullet));
	b->inUse = use;
	b->explosion_counter = 0;
}

Bullet* InitBullet(int x_pos, int y_pos, int velx, int vely, int cnn_orientation){
     Bullet *b = (Bullet *)malloc(sizeof(Bullet));
     b->x = x_pos;
     b->y = y_pos;
     b->x_vel = velx;
     b->y_vel = vely;
     b->inUse = 1;
     b->explosion_counter = 0;

	if (cnn_orientation == 1 || cnn_orientation == 3 || cnn_orientation == 5
			|| cnn_orientation == 7)
		b->bullet_bmp = loadBitmap("/home/lcom/Tanks/res/Bullet1.bmp");
	else{
		b->bullet_bmp = loadBitmap("/home/lcom/Tanks/res/Bullet2.bmp");
	}

	b->bulletOrientation = cnn_orientation;
	b->width = b->bullet_bmp->bitmapInfoHeader.width;
	b->height = b->bullet_bmp->bitmapInfoHeader.height;

    switch(cnn_orientation){
    case 1: rotateBitmap(b->bullet_bmp, 4); break;
    case 2: rotateBitmap(b->bullet_bmp, 4); break;
    case 3: rotateBitmap(b->bullet_bmp, -2); break;
    case 4: rotateBitmap(b->bullet_bmp, -2); break;
    case 7: rotateBitmap(b->bullet_bmp, 2); break;
    case 8: rotateBitmap(b->bullet_bmp, 2); break;
    default: break;
    }
     return b;
}

void moveBullet(Bullet* b){
    b->x = b->x + b->x_vel;
    b->y = b->y + b->y_vel;
}

void drawBullet(Bullet* b) {
	if (b->inUse)
		drawBitmap(b->bullet_bmp, b->x, b->y, ALIGN_LEFT, 0);
	else if(b->explosion_counter > 0 && b->explosion_counter <= 5){
		drawBitmap(b->bullet_exp, b->x, b->y, ALIGN_LEFT, 0);
		b->explosion_counter++;
		switch (b->explosion_counter) {
		case 2:
			b->bullet_exp = loadBitmap(
					"/home/lcom/Tanks/res/Spark2.bmp");
			break;
		case 3:
			b->bullet_exp = loadBitmap(
								"/home/lcom/Tanks/res/Spark3.bmp");
			break;
		case 4:
			b->bullet_exp = loadBitmap("/home/lcom/Tanks/res/Spark4.bmp");
			break;
		case 5:
			b->bullet_exp = loadBitmap("/home/lcom/Tanks/res/Spark5.bmp");
			break;
		}
	}
}

int checkScreenCollision(Bullet *b) {
	switch (b->bulletOrientation) {
	case 1:
		return b->x < Border;
	case 2:
		return (b->x < Border || b->y < Border);
	case 3:
		return b->y < Border;
	case 4:
		return (b->y < Border || b->x + b->width > get_h_res() - rightBorder);
	case 5:
		return b->x + b->width > get_h_res() - rightBorder;
	case 6:
		return (b->y + b->height > get_v_res()- Border || b->x + b->width > get_h_res()- rightBorder);
	case 7:
		return b->y + b->height > get_v_res()- Border;
	case 8:
		return (b->y + b->height > get_v_res() - Border || b->x < Border);
	}
}

void deleteBullet(Bullet* b){
	if (b->inUse)
		deleteBitmap(b->bullet_bmp);
	free(b);
}

/******************************* BulletPool functions *************************************/

void create(double x, double y, double xVel, double yVel, BulletPool* bp, int cnn_orientation){
	int i;
	for (i = 0; i < 5; i++) {
		if (bp->particles_[i]->inUse == 0) {
			bp->particles_[i] = InitBullet(x, y, xVel, yVel, cnn_orientation);
			return;
		}
	}
}

void updateBulletPool(BulletPool *bp){
	int i;
	for (i = 0; i < 5; i++) {
		if (bp->particles_[i]->inUse == 1 && bp->particles_[i]->explosion_counter == 0){
			moveBullet(bp->particles_[i]);
			if(checkScreenCollision(bp->particles_[i])){
				bp->particles_[i]->inUse = 0;
				bp->particles_[i]->explosion_counter = 1;
				bp->particles_[i]->bullet_exp = loadBitmap("/home/lcom/Tanks/res/Spark1.bmp");
			}
		}
		else if(bp->particles_[i]->inUse == 0 && bp->particles_[i]->explosion_counter == 5)
			bp->particles_[i] = CreateBullet(0);
	}
}

void drawBulletPool(BulletPool *bp){
	int i;
	for (i = 0; i < 5; i++) {
			drawBullet(bp->particles_[i]);
	}
}

void deleteBulletPool(BulletPool *bp){
	int i;
	for (i = 0; i < 5; i++) {
		deleteBullet(bp->particles_[i]);
	}
	free(bp);
}

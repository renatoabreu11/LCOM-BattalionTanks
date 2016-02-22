#include "tank.h"

int Orientation_cannon1;
int Orientation_cannon2;

//***************************************Tank functions****************************************//

Tank *InitTank(int mode) {
	Tank * t = (Tank *) malloc(sizeof(Tank));
	if (t == NULL)
		return NULL;
	if (mode == 0) {
		t->bot_bmp = loadBitmap("/home/lcom/Tanks/res/Tank.bmp");
		t->top1_bmp = loadBitmap("/home/lcom/Tanks/res/Cannon1.bmp");
		t->top2_bmp = loadBitmap("/home/lcom/Tanks/res/Cannon2.bmp");
		rotateBitmap(t->bot_bmp, -2);
		rotateBitmap(t->top1_bmp, -2);
		t->x = InitialX;
		t->y = InitialY;
		t->multiplayerflag = 0;
		t->tnk_ori = 3;
		t->cnn_ori = 3;
		Orientation_cannon1 = 3;
		Orientation_cannon2 = 4;
		t->lives = Tank_lives;
	} else {
		t->bot_bmp = loadBitmap("/home/lcom/Tanks/res/Enemy1.bmp");
		t->x = EnemyTankInitialX1;
		t->y = EnemyTankInitialY1;
		rotateBitmap(t->bot_bmp, 4);
		t->multiplayerflag = 1;
		t->tnk_ori = 7;
		t->cnn_ori = 7;
		t->lives = 6;
	}
	t->kbd_key = 0;
	t->velocity = Tank_speed;
	t->width = t->bot_bmp->bitmapInfoHeader.width;
	t->height = t->bot_bmp->bitmapInfoHeader.height;
	t->tankS = standing;
	t->ms_x = 512;
	t->ms_y = 384;
	int i;
	for (i = 0; i < 5; i++) {
		t->TankAmmunition.particles_[i] = (Bullet*) malloc(sizeof(Bullet));
		t->TankAmmunition.particles_[i] = CreateBullet(0);
	}
	t->tankCounter = 0;

	return t;
}

void KeyboardInputHandler(Tank *t, int key) {
	int aux = t->kbd_key;
	t->kbd_key = key;
	t->velocity = Tank_speed;
	if (t->multiplayerflag) {
		if (t->tankS == moving) {
			if (key >> 7 == 1 && key != 0xB9) { //0xB9 is the space break code
				t->tankS = standing;
			} else {
				t->kbd_key = aux;
				if (key == kSPACE) {
					shootCanon(t);
				}
			}
		}

		else {
			if (!(t->tankS == destroyed)) {
				if (!(t->kbd_key == kD || t->kbd_key == kW || t->kbd_key == kA
						|| t->kbd_key == kS)) {
					t->tankS = standing;
				}

				else if (!((t->kbd_key == kA && t->tnk_ori == 1
						|| (t->kbd_key == kW && t->tnk_ori == 3)
						|| (t->kbd_key == kD && t->tnk_ori == 5)
						|| (t->kbd_key == kS && t->tnk_ori == 7)))) {
					t->tankS = moving;
					rotateTank(t);
				}

				else {
					t->tankS = moving;
				}

				if (t->kbd_key == kSPACE) {
					t->tankS = shooting;
				}
			}
		}
	} else {
		if (t->tankS == moving) {
			if (key >> 7 == 0x1C1) {
				t->tankS = standing;
			} else {
				t->kbd_key = aux;
			}
		}
		if (!(t->tankS == destroyed)) {
			if (!(t->kbd_key == kLeft || t->kbd_key == kUp
					|| t->kbd_key == kRight || t->kbd_key == kDown)) {
			t->tankS = standing;
		}

			else if (!((t->kbd_key == kLeft && t->tnk_ori == 1
					|| (t->kbd_key == kUp && t->tnk_ori == 3)
					|| (t->kbd_key == kRight && t->tnk_ori == 5)
					|| (t->kbd_key == kDown && t->tnk_ori == 7)))) {
				t->tankS = moving;
				rotateTank(t);
			}

			else {
				t->tankS = moving;
			}
		}
	}
}

void MouseInputHandler(Tank *t, Mouse* m) {
	t->velocity = Tank_speed;
	if (!(t->tankS == destroyed)) {
		if (t->ms_x != m->x || t->ms_y != m->y) {
			t->ms_x = m->x;
			t->ms_y = m->y;
			t->tankS = rotatingCanon;
		} else if (m->leftButtonP) {
			t->tankS = shooting;
		}
	}
}

void moveTank(Tank *t) {
	if (t->multiplayerflag) {
		switch (t->kbd_key) {
		case kW:
			t->y -= t->velocity;
			break;
		case kA:
			t->x -= t->velocity;
			break;
		case kS:
			t->y += t->velocity;
			break;
		case kD:
			t->x += t->velocity;
			break;
		default:
			return;
		}
	} else {
		switch (t->kbd_key) {
		case kUp:
			t->y -= t->velocity;
			break;
		case kLeft:
			t->x -= t->velocity;
			break;
		case kDown:
			t->y += t->velocity;
			break;
		case kRight:
			t->x += t->velocity;
			break;
		default:
			return;
		}
	}
}

void rotateTank(Tank *t) {
	int aux;
	if (t->multiplayerflag) {
		switch (t->kbd_key) {
		case kA:
			aux = 1 - t->tnk_ori;
			t->tnk_ori = 1;
			break;
		case kW:
			aux = 3 - t->tnk_ori;
			t->tnk_ori = 3;
			break;
		case kD:
			aux = 5 - t->tnk_ori;
			t->tnk_ori = 5;
			break;
		case kS:
			aux = 7 - t->tnk_ori;
			t->tnk_ori = 7;
			break;
		default:
			return;
		}
	} else {
		switch (t->kbd_key) {
		case kLeft:
			aux = 1 - t->tnk_ori;
			t->tnk_ori = 1;
			break;
		case kUp:
			aux = 3 - t->tnk_ori;
			t->tnk_ori = 3;
			break;
		case kRight:
			aux = 5 - t->tnk_ori;
			t->tnk_ori = 5;
			break;
		case kDown:
			aux = 7 - t->tnk_ori;
			t->tnk_ori = 7;
			break;
		default:
			return;
		}
	}
	rotateBitmap(t->bot_bmp, aux);
}

void TankBulletCollision(BulletPool *bp, Tank * t) {
	int i;
	for (i = 0; i < 5; i++) {
		if (bp->particles_[i]->inUse == 1) {
			if (!(bp->particles_[i]->x + bp->particles_[i]->width < t->x
					|| bp->particles_[i]->x > t->x + t->width
					|| bp->particles_[i]->y + bp->particles_[i]->height < t->y
					|| bp->particles_[i]->y > t->y + t->height)) {
				bp->particles_[i] = CreateBullet(0);
				t->lives--;
				t->TankExp.x = t->x;
				t->TankExp.y = t->y;
				if (t->multiplayerflag == 0) {
					deleteBitmap(t->bot_bmp);
					deleteBitmap(t->top1_bmp);
					deleteBitmap(t->top2_bmp);
					t->bot_bmp = loadBitmap("/home/lcom/Tanks/res/Tank.bmp");
					t->top1_bmp = loadBitmap(
							"/home/lcom/Tanks/res/Cannon1.bmp");
					t->top2_bmp = loadBitmap(
							"/home/lcom/Tanks/res/Cannon2.bmp");
					rotateBitmap(t->bot_bmp, -2);
					rotateBitmap(t->top1_bmp, -2);
					t->x = InitialX;
					t->y = InitialY;
					t->tnk_ori = 3;
					t->cnn_ori = 3;
					Orientation_cannon1 = 3;
					Orientation_cannon2 = 4;
				} else {
					deleteBitmap(t->bot_bmp);
					t->bot_bmp = loadBitmap("/home/lcom/Tanks/res/Enemy1.bmp");
					t->x = EnemyTankInitialX1;
					t->y = EnemyTankInitialY1;
					rotateBitmap(t->bot_bmp, 4);
					t->tnk_ori = 7;
					t->cnn_ori = 7;
				}
				t->tankS = destroyed;
				t->TankExp.explosionNumber = 1;
				t->TankExp.Explosion = loadBitmap(
						"/home/lcom/Tanks/res/Explosion1.bmp");
			}
		}
	}
}

void rotateCanon(Tank *t) {
	int dx = (t->x + t->width / 2) - t->ms_x;
	int dy = (t->y + t->height / 2) - t->ms_y;
	int aux = t->cnn_ori;

	if (-dx * k < dy && dy <= dx * k) {
		t->cnn_ori = 1;
	} else if (dx * k < dy && dy <= dx / k) {
		t->cnn_ori = 2;
	} else if (-dy * k <= dx && dx < dy * k) {
		t->cnn_ori = 3;
	} else if (-dx * k <= dy && dy < -dx / k) {
		t->cnn_ori = 4;
	} else if (dx * k <= dy && dy < -dx * k) {
		t->cnn_ori = 5;
	} else if (dx / k <= dy && dy < dx * k) {
		t->cnn_ori = 6;
	} else if (dy * k < dx && dx <= -dy * k) {
		t->cnn_ori = 7;
	} else if (-dx / k < dy && dy <= -dx * k) {
		t->cnn_ori = 8;
	}

	if (aux == t->cnn_ori)
		return;

	if (t->multiplayerflag == 0) {
		if (t->cnn_ori == 1 || t->cnn_ori == 3 || t->cnn_ori == 5
				|| t->cnn_ori == 7) {
			if (t->cnn_ori != Orientation_cannon1)
				rotateBitmap(t->top1_bmp, t->cnn_ori - Orientation_cannon1);
			Orientation_cannon1 = t->cnn_ori;
		} else {
			if (t->cnn_ori != Orientation_cannon2)
				rotateBitmap(t->top2_bmp, t->cnn_ori - Orientation_cannon2);
			Orientation_cannon2 = t->cnn_ori;
		}
	}
}

void shootCanon(Tank *t) {
	int x, y, velx = 0, vely = 0;

	if (t->multiplayerflag) {
		t->cnn_ori = t->tnk_ori;
		switch (t->tnk_ori) {
		case 1:
			x = t->x;
			y = t->y + t->height / 2 - BulletHeight / 2;
			velx = -7;
			break;
		case 3:
			x = t->x + t->width / 2 - BulletWidth / 2;
			y = t->y;
			vely = -7;
			break;
		case 5:
			x = t->x + t->width;
			y = t->y + t->height / 2 - BulletHeight / 2;
			velx = 7;
			break;
		case 7:
			x = t->x + t->width / 2 - BulletWidth / 2;
			y = t->y + t->height - BulletHeight / 2;
			vely = 7;
			break;
		}
	} else {
		switch (t->cnn_ori) {
		case 1:
			x = t->x;
			y = t->y + t->height / 2 - BulletHeight / 2;
			velx = -7;
			break;
		case 2:
			x = t->x - BulletWidth / 8;
			y = t->y + BulletHeight / 32;
			vely = -7;
			velx = -7;
			break;
		case 3:
			x = t->x + t->width / 2 - BulletWidth / 2;
			y = t->y;
			vely = -7;
			break;
		case 4:
			x = t->x + t->width - BulletWidth;
			y = t->y + BulletHeight / 32;
			vely = -7;
			velx = 7;
			break;
		case 5:
			x = t->x + t->width;
			y = t->y + t->height / 2 - BulletHeight / 2;
			velx = 7;
			break;
		case 6:
			x = t->x + t->width - BulletWidth;
			y = t->y + t->height - BulletHeight;
			vely = 7;
			velx = 7;
			break;
		case 7:
			x = t->x + t->width / 2 - BulletWidth / 2;
			y = t->y + t->height - BulletHeight / 2;
			vely = 7;
			break;
		case 8:
			x = t->x - BulletWidth / 8;
			y = t->y + t->height - BulletHeight;
			vely = 7;
			velx = -7;
			break;
		}
	}

	create(x, y, velx, vely, &t->TankAmmunition, t->cnn_ori);
}

int checkBordersCollision(Tank *t) {
	switch (t->tnk_ori) {
	case 1:
		if (t->x - t->velocity < Border) {
			t->x = Border;
			return 1;
		}
		return 0;
	case 7:
		if (t->y + t->velocity + t->height > get_v_res() - Border) {
			t->y = get_v_res() - t->height - Border;
			return 1;
		}
		return 0;
	case 5:
		if (t->x + t->velocity + t->width > get_h_res() - rightBorder) {
			t->x = get_h_res() - t->width - rightBorder;
			return 1;
		}
		return 0;
	case 3:
		if (t->y - t->velocity < Border) {
			t->y = Border;
			return 1;
		}
		return 0;
	default:
		return 0;
	}
}

int checkTankCollision(Tank* t, EnemyTank * et) {
	if (et->destroyed)
		return false;
	return !(t->x + t->width < et->x || t->x > et->x + et->width
			|| t->y + t->height < et->y || t->y > et->y + et->height);
}

int checkTankCollisionDestroyed(Tank* t, EnemyTank * et) {
	return !(t->x + t->width < et->x || t->x > et->x + et->width
			|| t->y + t->height < et->y || t->y > et->y + et->height);
}

int checkCollisions(Tank* t, Tank * et) {
	if (et->tankS == destroyed)
		return false;
	return !(t->x + t->width < et->x || t->x > et->x + et->width
			|| t->y + t->height < et->y || t->y > et->y + et->height);
}

int checkCollisionsDestroyed(Tank* t, Tank * et) {
	return !(t->x + t->width < et->x || t->x > et->x + et->width
			|| t->y + t->height < et->y || t->y > et->y + et->height);
}

void updateTank(Tank *t) {
	switch (t->tankS) {
	case standing:
		break;
	case moving:
		if (!checkBordersCollision(t)) {
			rotateCanon(t);
			moveTank(t);
		}
		break;
	case shooting:
		shootCanon(t);
		if (!checkBordersCollision(t))
			moveTank(t);
		if (!(t->tankS == destroyed))
			t->tankS = standing;
		break;
	case rotatingTank:
		if (!checkBordersCollision(t))
			moveTank(t);
		break;
	case rotatingCanon:
		rotateCanon(t);
		if (!checkBordersCollision(t))
			moveTank(t);
		if (!(t->tankS == destroyed))
			t->tankS = standing;
		break;
	case destroyed:
		t->tankCounter++;
		break;
	}
	updateBulletPool(&t->TankAmmunition);
}

void drawTank(Tank *t) {
	if (t->tankS == destroyed) {
		if (t->TankExp.explosionNumber > 0 && t->TankExp.explosionNumber <= 5) {
			drawBitmap(t->TankExp.Explosion, t->TankExp.x, t->TankExp.y,
					ALIGN_LEFT, 0);
			t->TankExp.explosionNumber++;
			switch (t->TankExp.explosionNumber) {
			case 2:
				t->TankExp.Explosion = loadBitmap(
						"/home/lcom/Tanks/res/Explosion2.bmp");
				break;
			case 3:
				t->TankExp.Explosion = loadBitmap(
						"/home/lcom/Tanks/res/Explosion3.bmp");
				break;
			case 4:
				t->TankExp.Explosion = loadBitmap(
						"/home/lcom/Tanks/res/Explosion4.bmp");
				break;
			case 5:
				t->TankExp.Explosion = loadBitmap(
						"/home/lcom/Tanks/res/Explosion5.bmp");
				break;
			}
		}
	} else {
		drawBitmap(t->bot_bmp, t->x, t->y, ALIGN_LEFT, 0);
		if (t->multiplayerflag == 0) {
			if (t->cnn_ori == 1 || t->cnn_ori == 3 || t->cnn_ori == 5
					|| t->cnn_ori == 7)
				drawBitmap(t->top1_bmp, t->x, t->y, ALIGN_LEFT, 0);
			else
				drawBitmap(t->top2_bmp, t->x, t->y, ALIGN_LEFT, 0);
		}
	}
	drawBulletPool(&t->TankAmmunition);
}

void deleteTank(Tank *t) {
	deleteBitmap(t->bot_bmp);
	if (t->multiplayerflag == 0) {
		deleteBitmap(t->top1_bmp);
		deleteBitmap(t->top2_bmp);
	}
	if (t->TankExp.Explosion != NULL)
		deleteBitmap(t->TankExp.Explosion);
	deleteBulletPool(&t->TankAmmunition);
	free(t);
}

//*********************************Enemy Tank functions***********************************//

EnemyTank *InitEnemyTank(int i) {
	EnemyTank * t = (EnemyTank *) malloc(sizeof(EnemyTank));
	if (t == NULL)
		return NULL;
	char *labelPtr;
	srand(time(NULL));
	int aux = (rand() % 4) + 1;
	char str1[] = "/home/lcom/Tanks/res/Enemy1.bmp";
	labelPtr = str1;
	labelPtr[26] = aux + '0';
	if (i == 1) {
		t->bmap = loadBitmap(str1);
		t->x = EnemyTankInitialX1;
		t->y = EnemyTankInitialY1;
	} else if (i == 2) {
		t->bmap = loadBitmap(str1);
		t->x = EnemyTankInitialX2;
		t->y = EnemyTankInitialY2;
	} else
		return NULL;
	t->TankExp.Explosion = NULL;
	t->TankExp.explosionNumber = 0;
	t->ori = 3;
	t->width = t->bmap->bitmapInfoHeader.width;
	t->height = t->bmap->bitmapInfoHeader.height;
	int j;
	for (j = 0; j < 5; j++) {
		t->TankAmmunition.particles_[j] = (Bullet*) malloc(sizeof(Bullet));
		t->TankAmmunition.particles_[j] = CreateBullet(0);
	}
	int bulletInterval = 0;
	t->velocity = Tank_speed;
	t->destroyed = 0;
	t->type = i;
	t->flag = 0;
	return t;
}

void moveEnemyTank(EnemyTank *t) {
	switch (t->ori) {
	case 1:
		t->x -= t->velocity;
		break;
	case 3:
		t->y -= t->velocity;
		break;
	case 5:
		t->x += t->velocity;
		break;
	case 7:
		t->y += t->velocity;
		break;
	default:
		return;
	}
}

void rotateEnemyTank(EnemyTank *t, int ori) {
	int aux;
	if (ori != 0) {
		aux = (ori - t->ori);
		if (ori != t->ori)
			rotateBitmap(t->bmap, aux);
		t->ori = ori;
	} else {
		srand(time(NULL));
		srand(rand() % (127 + 127 * t->type)); //0<seed0<127, 127<seed1<254
		int i = (rand() % 4) + 1;
		if (i == 2)
			i = 3;
		else if (i == 3)
			i = 5;
		else if (i == 4)
			i = 7;
		aux = (i - t->ori);
		if (i != t->ori) {
			rotateBitmap(t->bmap, aux);
			t->ori = i;
		}
	}
}

void shootCanonEnemyTank(EnemyTank *t) {
	int x, y, velx = 0, vely = 0;
	switch (t->ori) {
	case 1:
		x = t->x;
		y = t->y + t->height / 2 - BulletHeight / 2;
		velx = -7;
		break;
	case 3:
		x = t->x + t->width / 2 - BulletWidth / 2;
		y = t->y;
		vely = -7;
		break;
	case 5:
		x = t->x + t->width;
		y = t->y + t->height / 2 - BulletHeight / 2;
		velx = 7;
		break;
	case 7:
		x = t->x + t->width / 2 - BulletWidth / 2;
		y = t->y + t->height - BulletHeight / 2;
		vely = 7;
		break;
	}
	create(x, y, velx, vely, &t->TankAmmunition, t->ori);
}

void updateEnemyTank(EnemyTank *t, int ori, int shoot_flag) {
	t->bulletInterval++;
	rotateEnemyTank(t, ori);
	if (checkEnemyTankBordersCollision(t)) {
		if (t->bulletInterval % 60 == 0 && shoot_flag != 0)
			shootCanonEnemyTank(t);
		updateBulletPool(&t->TankAmmunition);
		return;
	}
	moveEnemyTank(t);
	if (t->bulletInterval % 60 == 0 && shoot_flag != 0)
		shootCanonEnemyTank(t);
	updateBulletPool(&t->TankAmmunition);
}

int checkEnemyTankBordersCollision(EnemyTank *t) {
	switch (t->ori) {
	case 1:
		if (t->x - t->velocity < Border) {
			t->x = Border;
			return 1;
		}
		return 0;
	case 7:
		if (t->y + t->velocity + t->height > get_v_res() - Border) {
			t->y = get_v_res() - t->height - Border;
			return 1;
		}
		return 0;
	case 5:
		if (t->x + t->velocity + t->width > get_h_res() - rightBorder) {
			t->x = get_h_res() - t->width - rightBorder;
			return 1;
		}
		return 0;
	case 3:
		if (t->y - t->velocity < Border) {
			t->y = Border;
			return 1;
		}
		return 0;
	default:
		return 0;
	}
}

int checkEnemyTankCollision(EnemyTank *t1, EnemyTank *t2) {
	if (t1->destroyed || t2->destroyed)
		return false;
	return !(t1->x + t1->width < t2->x || t1->x > t2->x + t2->width
			|| t1->y + t1->height < t2->y || t1->y > t2->y + t2->height);
}

int checkEnemyTankCollisionDestroyed(EnemyTank *t1, EnemyTank *t2) {
	return !(t1->x + t1->width < t2->x || t1->x > t2->x + t2->width
			|| t1->y + t1->height < t2->y || t1->y > t2->y + t2->height);
}

void drawEnemyTank(EnemyTank *t) {
	if (!t->destroyed)
		drawBitmap(t->bmap, t->x, t->y, ALIGN_LEFT, 0);
	else if (t->TankExp.explosionNumber > 0
			&& t->TankExp.explosionNumber <= 5) {
		drawBitmap(t->TankExp.Explosion, t->TankExp.x, t->TankExp.y, ALIGN_LEFT,
				0);
		t->TankExp.explosionNumber++;
		switch (t->TankExp.explosionNumber) {
		case 2:
			t->TankExp.Explosion = loadBitmap(
					"/home/lcom/Tanks/res/Explosion2.bmp");
			break;
		case 3:
			t->TankExp.Explosion = loadBitmap(
					"/home/lcom/Tanks/res/Explosion3.bmp");
			break;
		case 4:
			t->TankExp.Explosion = loadBitmap(
					"/home/lcom/Tanks/res/Explosion4.bmp");
			break;
		case 5:
			t->TankExp.Explosion = loadBitmap(
					"/home/lcom/Tanks/res/Explosion5.bmp");
			break;
		}
	}
	drawBulletPool(&t->TankAmmunition);
}

void deleteEnemyTank(EnemyTank *t) {
	deleteBitmap(t->bmap);
	if (t->TankExp.Explosion != NULL)
		deleteBitmap(t->TankExp.Explosion);
	deleteBulletPool(&t->TankAmmunition);
	free(t);
}

void EnemyTankBulletCollision(BulletPool *bp, EnemyTank * t) {
	int i;
	for (i = 0; i < 5; i++) {
		if (bp->particles_[i]->inUse == 1) {
			if (!(bp->particles_[i]->x + bp->particles_[i]->width < t->x
					|| bp->particles_[i]->x > t->x + t->width
					|| bp->particles_[i]->y + bp->particles_[i]->height < t->y
					|| bp->particles_[i]->y > t->y + t->height)) {
				bp->particles_[i] = CreateBullet(0);
				t->destroyed = 1;
				deleteBitmap(t->bmap);
				t->ori = 3;
				t->TankExp.x = t->x;
				t->TankExp.y = t->y;
				char *labelPtr;
				srand(time(NULL));
				int aux = (rand() % 4) + 1;
				char str1[] = "/home/lcom/Tanks/res/Enemy1.bmp";
				labelPtr = str1;
				labelPtr[26] = aux + '0';
				if (t->type == 1) {
					t->bmap = loadBitmap(str1);
					t->x = EnemyTankInitialX1;
					t->y = EnemyTankInitialY1;
				} else if (t->type == 2) {
					t->bmap = loadBitmap(str1);
					t->x = EnemyTankInitialX2;
					t->y = EnemyTankInitialY2;
				}
				t->TankExp.explosionNumber = 1;
				t->TankExp.Explosion = loadBitmap(
						"/home/lcom/Tanks/res/Explosion1.bmp");
			}
		}
	}
}

void BulletsCollision(BulletPool *bp, BulletPool *bp1) {
	int i, j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (bp->particles_[i]->inUse == 1
					&& bp1->particles_[j]->inUse == 1) {
				if (!(bp->particles_[i]->x + bp->particles_[i]->width
						< bp1->particles_[j]->x
						|| bp->particles_[i]->x
								> bp1->particles_[j]->x
										+ bp1->particles_[j]->width
						|| bp->particles_[i]->y + bp->particles_[i]->height
								< bp1->particles_[j]->y
						|| bp->particles_[i]->y
								> bp1->particles_[j]->y
										+ bp1->particles_[j]->height)) {
					bp->particles_[i]->inUse = 0;
					bp->particles_[i]->explosion_counter = 1;
					bp->particles_[i]->bullet_exp = loadBitmap(
							"/home/lcom/Tanks/res/Spark1.bmp");
					bp1->particles_[j]->inUse = 0;
					bp1->particles_[j]->explosion_counter = 5;
				}
			}
		}
	}
}


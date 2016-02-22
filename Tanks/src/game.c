#include "game.h"

Game* InitGame() {
	Game* g = (Game*) malloc(sizeof(Game));
	g->player = (Tank*) malloc(sizeof(Tank));
	g->player = InitTank(0);
	g->enemy1 = (EnemyTank*) malloc(sizeof(EnemyTank));
	g->enemy1 = InitEnemyTank(1);
	g->enemy2 = (EnemyTank*) malloc(sizeof(EnemyTank));
	g->enemy2 = InitEnemyTank(2);

	g->EnemyTanks = 21;
	g->counterEnemy1 = 0;
	g->counterEnemy2 = 0;
	g->score = 0;

	g->GameTerrain = (Terrain*) malloc(sizeof(Terrain));
	g->GameTerrain = InitTerrain(0);
	return g;
}

void updateGame(Game* g) {
	int auxCoordX = g->player->x;
	int auxCoordY = g->player->y;

	updateTank(g->player);
	checkBulletWallCollison(&g->player->TankAmmunition, g->GameTerrain);
	if (!(g->player->tankS == destroyed)) {
		if (g->player->x != auxCoordX || g->player->y != auxCoordY) {
			if (checkTankCollision(g->player, g->enemy1)
					|| checkTankCollision(g->player, g->enemy2)
					|| checkTankWallCollision(g->player->x, g->player->y,
							g->player->width, g->player->height,
							g->GameTerrain)) {
				g->player->x = auxCoordX;
				g->player->y = auxCoordY;
			}
		}
	}

	else {
		if (g->player->tankCounter / 60 == 3) {
			if (checkTankCollisionDestroyed(g->player, g->enemy2)
					 || checkTankCollisionDestroyed(g->player, g->enemy1)) {
				g->player->x = 700;
			}
			g->player->TankExp.explosionNumber = 0;
			g->player->tankS = standing;
			g->player->tankCounter = 0;
		}
	}

	auxCoordX = g->enemy1->x;
	auxCoordY = g->enemy1->y;

	if (!g->enemy1->destroyed) {
		if (g->player->tankS == destroyed)
			updateEnemyTank(g->enemy1, 0, 0);
		else if (g->enemy1->flag == 1)
			updateEnemyTank(g->enemy1, 0, 0);
		else if (!LineOfSight(g->player->x, g->player->y, g->player->width,
				g->player->height, g->enemy1, g->enemy2, g->GameTerrain))
			updateEnemyTank(g->enemy1, 0, 0);

		g->enemy1->flag = 0;
		if (g->enemy1->x != auxCoordX || g->enemy1->y != auxCoordY) {
			if (checkTankCollision(g->player, g->enemy1)
					|| checkEnemyTankCollision(g->enemy1, g->enemy2)
					|| checkTankWallCollision(g->enemy1->x, g->enemy1->y,
							g->enemy1->width, g->enemy1->height,
							g->GameTerrain)) {
				g->enemy1->x = auxCoordX;
				g->enemy1->y = auxCoordY;
			}
		}

		auxCoordX = g->enemy1->x;
		auxCoordY = g->enemy1->y;
		EnemyTankBulletCollision(&g->player->TankAmmunition, g->enemy1);
		if (g->enemy1->destroyed) {
			g->score += 25;
			g->EnemyTanks--;
			g->GameTerrain->lateralBar[6 + g->EnemyTanks] = -1;
			g->GameTerrain->lateralBar[42] = g->score / 100;
			g->GameTerrain->lateralBar[43] = (g->score % 100) / 10;
			g->GameTerrain->lateralBar[44] = (g->score % 100) % 10;
		}
	}

	else {
		updateBulletPool(&g->enemy1->TankAmmunition);
		if (g->counterEnemy1 / 60 == Spawn) {
			if (!checkEnemyTankCollisionDestroyed(g->enemy2, g->enemy1)
					&& !checkTankCollisionDestroyed(g->player, g->enemy1)) {

				g->enemy1->destroyed = 0;
				g->counterEnemy1 = 0;
			}
		} else
			g->counterEnemy1++;
	}
	checkBulletWallCollison(&g->enemy1->TankAmmunition, g->GameTerrain);
	BulletsCollision(&g->enemy1->TankAmmunition, &g->player->TankAmmunition);

	auxCoordX = g->enemy2->x;
	auxCoordY = g->enemy2->y;

	if (!g->enemy2->destroyed) {
		if (g->player->tankS == destroyed)
			updateEnemyTank(g->enemy2, 0, 0);
		else if (g->enemy2->flag == 1)
				updateEnemyTank(g->enemy2, 0, 0);
		else if (!LineOfSight(g->player->x, g->player->y, g->player->width,
				g->player->height, g->enemy2, g->enemy1, g->GameTerrain))
			updateEnemyTank(g->enemy2, 0, 0);

		g->enemy2->flag = 0;
		checkBulletWallCollison(&g->enemy2->TankAmmunition, g->GameTerrain);
		if (g->enemy2->x != auxCoordX || g->enemy2->y != auxCoordY) {
			if (checkTankCollision(g->player, g->enemy2)
					|| checkEnemyTankCollision(g->enemy2, g->enemy1)
					|| checkTankWallCollision(g->enemy2->x, g->enemy2->y,
							g->enemy2->width, g->enemy2->height,
							g->GameTerrain)) {
				g->enemy2->x = auxCoordX;
				g->enemy2->y = auxCoordY;
			}
		}
		EnemyTankBulletCollision(&g->player->TankAmmunition, g->enemy2);
		if (g->enemy2->destroyed) {
			g->score += 25;
			g->EnemyTanks--;
			g->GameTerrain->lateralBar[6 + g->EnemyTanks] = -1;
			g->GameTerrain->lateralBar[42] = g->score / 100;
			g->GameTerrain->lateralBar[43] = (g->score % 100) / 10;
			g->GameTerrain->lateralBar[44] = (g->score % 100) % 10;
		}
	}

	else {
		updateBulletPool(&g->enemy2->TankAmmunition);
		if (g->counterEnemy2 / 60 == Spawn) {
			if (!checkEnemyTankCollisionDestroyed(g->enemy2, g->enemy1)
					&& !checkTankCollisionDestroyed(g->player, g->enemy2)) {

				g->enemy2->destroyed = 0;
				g->counterEnemy2 = 0;
			}
		} else
			g->counterEnemy2++;
	}
	BulletsCollision(&g->enemy2->TankAmmunition, &g->player->TankAmmunition);
	BulletsCollision(&g->enemy2->TankAmmunition, &g->enemy1->TankAmmunition);
	checkBulletWallCollison(&g->enemy2->TankAmmunition, g->GameTerrain);

	if (g->player->tankS != destroyed) {
		TankBulletCollision(&g->enemy1->TankAmmunition, g->player);
		TankBulletCollision(&g->enemy2->TankAmmunition, g->player);
	}
	if (!g->enemy2->destroyed && !g->enemy1->destroyed) {
		EnemyTankBulletCollision(&g->enemy1->TankAmmunition, g->enemy2);
		EnemyTankBulletCollision(&g->enemy2->TankAmmunition, g->enemy1);
	}
	if (g->player->tankS == destroyed) {
		g->GameTerrain->lateralBar[51 + g->player->lives] = -1;
	}
}

void drawGame(Game* g) {
	drawTerrain(g->GameTerrain);
	drawTank(g->player);
	drawEnemyTank(g->enemy1);
	drawEnemyTank(g->enemy2);
}

void deleteGame(Game* g) {
	deleteTank(g->player);
	deleteEnemyTank(g->enemy1);
	deleteEnemyTank(g->enemy2);
	deleteTerrain(g->GameTerrain);
	free(g);
}

int checkTankWallCollision(int x, int y, int width, int height, Terrain *terr) {
	int XCell1, YCell1, XCell2, YCell2, XCell3, YCell3, XCell4, YCell4, XCell5, YCell5;

	XCell1 = getCell(x, 0, 0, 0, 2);
	YCell1 = getCell(0, y, 0, 0, 2);
	XCell2 = getCell(x, 0, width, 0, -2);
	YCell2 = getCell(0, y, 0, 0, 2);
	XCell3 = getCell(x, 0, 0, 0, 2);
	YCell3 = getCell(0, y, 0, height, -2);
	XCell4 = getCell(x, 0, width, 0, -2);
	YCell4 = getCell(0, y, 0, height, -2);

	if (terr->cells[XCell1 + YCell1 * 24] == 2
			|| terr->cells[XCell2 + YCell2 * 24] == 2
			|| terr->cells[XCell3 + YCell3 * 24] == 2
			|| terr->cells[XCell4 + YCell4 * 24] == 2
			|| terr->cells[XCell5 + YCell5 * 24] == 2)
		return 1;

	XCell1 = getCell(x, 0, width/2, 0, 2);
	XCell2 = getCell(x, 0, width, 0, -2);
	YCell2 = getCell(0, y, 0, height/2, 0);
	YCell3 = getCell(0, y, 0, height/2, 0);
	XCell4 = getCell(x, 0, width/2, 0, 0);
	YCell4 = getCell(0, y, 0, height, -2);

	if (terr->cells[XCell1 + YCell1 * 24] == 2
			|| terr->cells[XCell2 + YCell2 * 24] == 2
			|| terr->cells[XCell3 + YCell3 * 24] == 2
			|| terr->cells[XCell4 + YCell4 * 24] == 2
			|| terr->cells[XCell5 + YCell5 * 24] == 2)
		return 1;
	else
		return 0;
}

void checkBulletWallCollison(BulletPool* bp, Terrain *terr) {
	int XCell1, YCell1, XCell2, YCell2, XCell3, YCell3, XCell4, YCell4;
	int destroyed = 0;

	int i;
	for (i = 0; i < 5; i++) {
		destroyed = 0;
		if (bp->particles_[i]->inUse == 1) {
			XCell1 = getCell(bp->particles_[i]->x, 0, 0, 0, 4);
			YCell1 = getCell(0, bp->particles_[i]->y, 0, 0, 4);
			XCell2 = getCell(bp->particles_[i]->x, 0, bp->particles_[i]->width,
					0, -4);
			YCell2 = getCell(0, bp->particles_[i]->y, 0, 0, 4);
			XCell3 = getCell(bp->particles_[i]->x, 0, 0, 0, 4);
			YCell3 = getCell(0, bp->particles_[i]->y, 0,
					bp->particles_[i]->height, -4);
			XCell4 = getCell(bp->particles_[i]->x, 0, bp->particles_[i]->width,
					0, -4);
			YCell4 = getCell(0, bp->particles_[i]->y, 0,
					bp->particles_[i]->height, -4);

			if (terr->cells[XCell1 + YCell1 * 24] == 2) {
				terr->cells[XCell1 + YCell1 * 24] = 1;
				destroyed = 1;
			}
			if (terr->cells[XCell2 + YCell2 * 24] == 2) {
				terr->cells[XCell2 + YCell2 * 24] = 1;
				destroyed = 1;
			}
			if (terr->cells[XCell3 + YCell3 * 24] == 2) {
				terr->cells[XCell3 + YCell3 * 24] = 1;
				destroyed = 1;
			}
			if (terr->cells[XCell4 + YCell4 * 24] == 2) {
				terr->cells[XCell4 + YCell4 * 24] = 1;
				destroyed = 1;
			}

			if (destroyed) {
				bp->particles_[i]->inUse = 0;
				bp->particles_[i]->explosion_counter = 1;
				bp->particles_[i]->bullet_exp = loadBitmap(
						"/home/lcom/Tanks/res/Spark1.bmp");
			}
		}
	}
}

int getCell(int x, int y, int width, int height, int tolerance) {
	return floor((y + x + height + width - 24 + tolerance) / 36);
}

int OutOfLives(Game* g) {
	return (g->player->lives == 0);
}

int BattalionDestroyed(Game* g) {
	return (g->EnemyTanks == 0);
}

int LineOfSight(int x, int y, int width, int height, EnemyTank * et,
		EnemyTank * et2, Terrain * terr) {
	int XCell1, XCell2, YCell1, YCell2, XCell3, YCell3;
	int CellsBetween;
	int WallCellCounter = 0;
	int counter1 = 0, counter2 = 0;
	int i, j;
	double cateto1, cateto2;
	int auxCoordX = et->x;
	int auxCoordY = et->y;

	XCell1 = getCell(x, 0, width / 2, 0, -2);
	XCell2 = getCell(et->x, 0, et->width / 2, 0, -2);
	YCell1 = getCell(0, y, 0, height / 2, 4);
	YCell2 = getCell(0, et->y, 0, et->height / 2, 4);
	XCell3 = getCell(et2->x, 0, et2->width / 2, 0, 2);
	YCell3 = getCell(0, et2->y, 0, et2->height / 2, 2);

	cateto1 = fabs(YCell1 - YCell2);
	cateto2 = fabs(XCell1 - XCell2);

	if (XCell1 == XCell2) {
		CellsBetween = abs(YCell1 - YCell2);
		if (YCell1 > YCell2) {
			for (i = 0; i < CellsBetween; i++) {
				if (terr->cells[XCell2 + YCell2 * 24 * (i + 1)] == 2)
					WallCellCounter++;
			}
			if (WallCellCounter < 20) {
				if (XCell3 != XCell2)
					updateEnemyTank(et, 7, 1);
				else if (XCell3 == XCell2) {
					if (YCell3 < YCell2)
						updateEnemyTank(et, 7, 1);
					else
						updateEnemyTank(et, 7, 0);
				}
				return 1;
			} else{
				et->flag = 1;
				return 0;
			}
		} else if (YCell1 < YCell2) {
			for (i = 0; i < CellsBetween; i++) {
				if (terr->cells[XCell1 + YCell1 * 24 * (i + 1)] == 2)
					WallCellCounter++;
			}
			if (WallCellCounter < 20) {
				if (XCell3 != XCell2)
					updateEnemyTank(et, 3, 1);
				else if (XCell3 == XCell2) {
					if (YCell3 > YCell2)
						updateEnemyTank(et, 3, 1);
					else
						updateEnemyTank(et, 3, 0);
				}
				return 1;
			} else{
				et->flag = 1;
				return 0;
			}
		}
	} else if (YCell1 == YCell2) {
		CellsBetween = abs(XCell1 - XCell2);
		if (XCell1 > XCell2) {
			for (i = 0; i < CellsBetween; i++) {
				if (terr->cells[XCell2 * (i + 1) + YCell2 * 24 * (i + 1)] == 2)
					WallCellCounter++;
			}
			if (WallCellCounter < 20) {
				if (YCell3 != YCell2)
					updateEnemyTank(et, 5, 1);
				else if (YCell3 == YCell2) {
					if (XCell3 < XCell2)
						updateEnemyTank(et, 5, 1);
					else
						updateEnemyTank(et, 5, 0);
				}
				return 1;
			} else{
				et->flag = 1;
				return 0;
			}
		} else if (XCell1 < XCell2) {
			for (i = 0; i < CellsBetween; i++) {
				if (terr->cells[XCell1 * (i + 1) + YCell1 * 24] == 2)
					WallCellCounter++;
			}
			if (WallCellCounter < 20) {
				if (YCell3 != YCell2)
					updateEnemyTank(et, 1, 1);
				else if (YCell3 == YCell2) {
					if (XCell3 > XCell2)
						updateEnemyTank(et, 1, 1);
					else
						updateEnemyTank(et, 1, 0);
				}
				return 1;
			} else{
				et->flag = 1;
				return 0;
			}
		}
	} else {
		if ((YCell1 > YCell2 || YCell1 < YCell2) && XCell1 < XCell2) {
			for (i = 0; i < cateto2; i++) {
				if (terr->cells[XCell1 * (i + 1) + YCell2 * 24] == 2)
					counter2++;
			}
		}

		else if ((YCell1 > YCell2 || YCell1 < YCell2) && XCell1 > XCell2) {
			for (i = 0; i < cateto2; i++) {
				if (terr->cells[XCell2 * (i + 1) + YCell2 * 24] == 2)
					counter2++;
			}
		}

		if (YCell1 > YCell2) {
			for (j = 0; j < cateto1; j++) {
				if (terr->cells[XCell2 + YCell2 * 24 * (j + 1)] == 2)
					counter1++;
			}
		} else {
			for (j = 0; j < cateto1; j++) {
				if (terr->cells[XCell2 + YCell1 * 24 * (j + 1)] == 2)
					counter1++;
			}
		}

		if (XCell1 < XCell2) {
			if (counter1 <= counter2 && counter1 <  20) {
				if (YCell1 > YCell2)
					updateEnemyTank(et, 7, 1);
				else
					updateEnemyTank(et, 3, 1);

				if (checkTankWallCollision(et->x, et->y, et->width, et->height,
						terr)) {
					et->x = auxCoordX;
					et->y = auxCoordY;
					rotateEnemyTank(et, 0);
					moveEnemyTank(et);
					et->flag = 1;
				}
				return 1;
			} else if (counter1 > counter2 && counter2 <  20) {
				updateEnemyTank(et, 1, 1);
				if (checkTankWallCollision(et->x, et->y, et->width, et->height,
						terr)) {
					et->x = auxCoordX;
					et->y = auxCoordY;
					rotateEnemyTank(et, 0);
					moveEnemyTank(et);
					et->flag = 1;
				}
				return 1;
			} else
				return 0;
		} else if (XCell1 > XCell2) {
			if (counter1 <= counter2 && counter1 <  20) {
				if (YCell1 > YCell2)
					updateEnemyTank(et, 7, 1);
				else
					updateEnemyTank(et, 3, 1);

				if (checkTankWallCollision(et->x, et->y, et->width, et->height,
						terr)) {
					et->x = auxCoordX;
					et->y = auxCoordY;
					rotateEnemyTank(et, 0);
					moveEnemyTank(et);
					et->flag = 1;
				}
				return 1;
			} else if (counter1 > counter2 && counter2 <  20) {
				updateEnemyTank(et, 5, 1);
				if (checkTankWallCollision(et->x, et->y, et->width, et->height,
						terr)) {
					et->x = auxCoordX;
					et->y = auxCoordY;
					rotateEnemyTank(et, 0);
					moveEnemyTank(et);
					et->flag = 1;
				}
				return 1;
			} else{
				et->flag = 1;
				return 0;
			}

		}
	}
}

MultiPlayerMode* InitMultiplayerMode(){
	MultiPlayerMode* mp = (MultiPlayerMode*)malloc(sizeof(MultiPlayerMode));
	mp->player1 = (Tank*) malloc(sizeof(Tank));
	mp->player1 = InitTank(0);
	mp->player2 = (Tank*) malloc(sizeof(Tank));
	mp->player2 = InitTank(1);
	mp->GameTerrain = (Terrain*) malloc(sizeof(Terrain));
	mp->GameTerrain = InitTerrain(1);
	return mp;
}

void updateMultiPlayer(MultiPlayerMode* mp){
	int auxCoordX = mp->player1->x;
	int auxCoordY = mp->player1->y;

	updateTank(mp->player1);
	checkBulletWallCollison(&mp->player1->TankAmmunition, mp->GameTerrain);
	BulletsCollision(&mp->player1->TankAmmunition, &mp->player2->TankAmmunition);
	if (!(mp->player1->tankS == destroyed)) {
		if (mp->player1->x != auxCoordX || mp->player1->y != auxCoordY) {
			if (checkCollisions(mp->player1, mp->player2)
					|| checkTankWallCollision(mp->player1->x, mp->player1->y,
							mp->player1->width, mp->player1->height,
							mp->GameTerrain)) {
				mp->player1->x = auxCoordX;
				mp->player1->y = auxCoordY;
			}
		}
	}

	else {
		if (mp->player1->tankCounter / 60 == 3) {
			if (checkCollisionsDestroyed(mp->player1, mp->player2)) {
				mp->player1->x = 700;
			}
			mp->player1->TankExp.explosionNumber = 0;
			mp->player1->tankS = standing;
			mp->player1->tankCounter = 0;
		}
	}

	auxCoordX = mp->player2->x;
	auxCoordY = mp->player2->y;

	updateTank(mp->player2);
	checkBulletWallCollison(&mp->player2->TankAmmunition, mp->GameTerrain);
	BulletsCollision(&mp->player1->TankAmmunition, &mp->player2->TankAmmunition);
	if (!(mp->player2->tankS == destroyed)) {
		if (mp->player2->x != auxCoordX || mp->player2->y != auxCoordY) {
			if (checkCollisions(mp->player1, mp->player2)
					|| checkTankWallCollision(mp->player2->x, mp->player2->y,
							mp->player2->width, mp->player2->height,
							mp->GameTerrain)) {
				mp->player2->x = auxCoordX;
				mp->player2->y = auxCoordY;
			}
		}
	}

	else {
		if (mp->player2->tankCounter / 60 == 3) {
			if (checkCollisionsDestroyed(mp->player2, mp->player1)) {
				mp->player2->x = 748;
				mp->player2->y = 24;
			}
			mp->player2->TankExp.explosionNumber = 0;
			mp->player2->tankS = standing;
			mp->player2->tankCounter = 0;
		}
	}

	if (mp->player1->tankS != destroyed) {
		TankBulletCollision(&mp->player2->TankAmmunition, mp->player1);
	}

	if (mp->player2->tankS != destroyed) {
		TankBulletCollision(&mp->player1->TankAmmunition, mp->player2);
	}

	if (mp->player1->tankS == destroyed) {
		mp->GameTerrain->lateralBar[45 + mp->player1->lives] = -1;
	}
	if (mp->player2->tankS == destroyed) {
		mp->GameTerrain->lateralBar[12 + mp->player2->lives] = -1;
	}
}

void drawMultiPlayer(MultiPlayerMode* mp){
	drawTerrain(mp->GameTerrain);
	drawTank(mp->player1);
	drawTank(mp->player2);
}

void deleteMultiPlayer(MultiPlayerMode* mp){
	deleteTerrain(mp->GameTerrain);
	deleteTank(mp->player1);
	deleteTank(mp->player2);
}


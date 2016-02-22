#include "menu.h"

//****************************************Main Menu****************************************//

MainMenu* InitMainMenu(){
	MainMenu* mm = (MainMenu*) malloc(sizeof(MainMenu));
	mm->Title1Bmp = loadBitmap("/home/lcom/Tanks/res/Battalion.bmp");
	mm->Title2Bmp = loadBitmap("/home/lcom/Tanks/res/Tanks.bmp");
	mm->SinglePlayBmp = loadBitmap("/home/lcom/Tanks/res/SinglePlayer.bmp");
	mm->MultiPlayBmp = loadBitmap("/home/lcom/Tanks/res/MultiPlayer.bmp");
	mm->HighScoreBmp = loadBitmap("/home/lcom/Tanks/res/Highscores.bmp");
	mm->ExitBmp = loadBitmap("/home/lcom/Tanks/res/Exit.bmp");
	mm->Highlight = loadBitmap("/home/lcom/Tanks/res/Selection.bmp");
	mm->singlePlay = 0;
	mm->multiPlay = 0;
	mm->exit = 0;
	mm->highScores = 0;
	mm->option = 0;
	return mm;
}

void updateMainMenu(MainMenu* mm, Mouse* ms){
	if (mm->exit == 1 && ms->leftButtonP) {
		mm->option = 3;
	} else if (mm->highScores == 1 && ms->leftButtonP) {
		mm->option = 2;
	} else if (mm->singlePlay == 1 && ms->leftButtonP) {
		mm->option = 1;
	} else if (mm->multiPlay == 1 && ms->leftButtonP) {
		mm->option = 4;
	} else {
		if (MouseOverBmp(SinglePlayX, SinglePlayY, 394, 70, ms)) {
			mm->singlePlay = 1;
			mm->highScores = 0;
			mm->exit = 0;
			mm->multiPlay = 0;
		} else if (MouseOverBmp(HighScoreX, HighScoreY, 394, 70, ms)) {
			mm->highScores = 1;
			mm->singlePlay = 0;
			mm->exit = 0;
			mm->multiPlay = 0;
		} else if (MouseOverBmp(ExitX, ExitY, 394, 70, ms)) {
			mm->exit = 1;
			mm->highScores = 0;
			mm->singlePlay = 0;
			mm->multiPlay = 0;
		}else if (MouseOverBmp(MultiPlayX, MultiPlayY, 394, 70, ms)) {
			mm->exit = 0;
			mm->highScores = 0;
			mm->singlePlay = 0;
			mm->multiPlay = 1;
		} else {
			mm->exit = 0;
			mm->highScores = 0;
			mm->singlePlay = 0;
			mm->multiPlay = 0;
		}
	}
}

void drawMainMenu(MainMenu* mm, Date* d){
	drawBitmap(mm->Title1Bmp, Title1X, Title1Y, ALIGN_LEFT, 0);
	drawBitmap(mm->Title2Bmp, Title2X, Title2Y, ALIGN_LEFT, 0);
	drawBitmap(mm->SinglePlayBmp, SinglePlayX, SinglePlayY, ALIGN_LEFT, 0);
	drawBitmap(mm->MultiPlayBmp, MultiPlayX, MultiPlayY, ALIGN_LEFT, 0);
	drawBitmap(mm->HighScoreBmp, HighScoreX, HighScoreY, ALIGN_LEFT, 0);
	drawBitmap(mm->ExitBmp, ExitX, ExitY, ALIGN_LEFT, 0);
	drawDate(d, 10, 10);
	if (mm->singlePlay == 1) {
		drawBitmap(mm->Highlight, SinglePlayX, SinglePlayY, ALIGN_LEFT, 0);
	} else if (mm->highScores == 1) {
		drawBitmap(mm->Highlight, HighScoreX, HighScoreY, ALIGN_LEFT, 0);
	} else if (mm->exit == 1) {
		drawBitmap(mm->Highlight, ExitX, ExitY, ALIGN_LEFT, 0);
	} else if (mm->multiPlay == 1) {
		drawBitmap(mm->Highlight, MultiPlayX, MultiPlayY, ALIGN_LEFT, 0);
	}
}

void deleteMainMenu(MainMenu* mm) {
	deleteBitmap(mm->Title1Bmp);
	deleteBitmap(mm->Title2Bmp);
	deleteBitmap(mm->SinglePlayBmp);
	deleteBitmap(mm->MultiPlayBmp);
	deleteBitmap(mm->HighScoreBmp);
	deleteBitmap(mm->ExitBmp);
	deleteBitmap(mm->Highlight);
	free(mm);
}

int MouseOverBmp(int x, int y, int width, int height, Mouse* ms){
	return !(x + width < ms->x || x > ms->x + ms->mouseWidth
					|| y + height < ms->y || y > ms->y + ms->mouseHeight);
}


//***************************************Pause Menu****************************************//

PauseMenu* InitPauseMenu(){
	PauseMenu* pm = (PauseMenu*) malloc(sizeof(PauseMenu));
	pm->ResumeBmp = loadBitmap("/home/lcom/Tanks/res/Resume.bmp");
	pm->ExitBmp = loadBitmap("/home/lcom/Tanks/res/Exit.bmp");
	pm->Highlight = loadBitmap("/home/lcom/Tanks/res/Selection.bmp");
	pm->resume = 0;
	pm->exit = 0;
	pm->option = 0;
	return pm;
}

void updatePauseMenu(PauseMenu* pm, Mouse* ms){
	if (pm->exit == 1 && ms->leftButtonP) {
		pm->option = 2;
	} else if (pm->resume == 1 && ms->leftButtonP) {
		pm->option = 1;
	} else {
		if (MouseOverBmp(ResumeX, ResumeY, 394, 70, ms)) {
			pm->resume = 1;
			pm->exit = 0;
		} else if (MouseOverBmp(Exit2X, Exit2Y, 394, 70, ms)) {
			pm->exit = 1;
			pm->resume = 0;
		}
		else{
			pm->exit = 0;
			pm->resume = 0;
		}
	}
}

void drawPauseMenu(PauseMenu* pm){
	drawBitmap(pm->ResumeBmp, ResumeX, ResumeY, ALIGN_LEFT, 0);
	drawBitmap(pm->ExitBmp, Exit2X, Exit2Y, ALIGN_LEFT, 0);
	if (pm->resume == 1) {
		drawBitmap(pm->Highlight, ResumeX, ResumeY, ALIGN_LEFT, 0);
	} else if (pm->exit == 1) {
		drawBitmap(pm->Highlight, Exit2X, Exit2Y, ALIGN_LEFT, 0);
	}
}

void deletePauseMenu(PauseMenu* pm){
	deleteBitmap(pm->ResumeBmp);
	deleteBitmap(pm->Highlight);
	deleteBitmap(pm->ExitBmp);
	free(pm);
}

//***************************************HighScores****************************************//

HighScores* InitHighScores() {
	HighScores* hs = (HighScores*) malloc(sizeof(HighScores));
	hs->HighScore = loadBitmap("/home/lcom/Tanks/res/Highscores.bmp");
	hs->Exit = loadBitmap("/home/lcom/Tanks/res/Exit.bmp");
	hs->Highlight = loadBitmap("/home/lcom/Tanks/res/Selection.bmp");
	hs->exit = 0;
	hs->option = 0;
	hs->counter = 0;
	FILE *file;
	file = fopen("/home/lcom/Tanks/src/Highscores.txt", "r");
	if (file != NULL) {
		int i;
		for(i = 0; i < 9; ++i)
		{
		  if(fgets(hs->cells[i], sizeof hs->cells[i], file) == NULL)
		  {
		   return NULL;
		  }
		  LOG_MSG(hs->cells[i]);
		}
	} else
		return NULL;
	fclose(file);
	int i;
	return hs;
}

void updateHighScores(HighScores* hs, Mouse* ms){
	if (hs->exit == 1 && ms->leftButtonP) {
		hs->option = 1;
	} else {
		if (MouseOverBmp(Exit3X, Exit3Y, 394, 70, ms)) {
			hs->exit = 1;
		} else {
			hs->exit = 0;
		}
	}
}

void drawHighScores(HighScores* hs){
	drawBitmap(hs->HighScore, HighScore2X, HighScore2Y, ALIGN_LEFT, 0);
	drawBitmap(hs->Exit, Exit3X, Exit3Y, ALIGN_LEFT, 0);
	if (hs->exit == 1) {
		drawBitmap(hs->Highlight, Exit3X, Exit3Y, ALIGN_LEFT, 0);
	}
	Font* font = InitFont();
	int i, j;
	int Xpos = 350;
	int Ypos = 150;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++) {
			drawChar(font, hs->cells[i][j], Xpos, Ypos);
			Xpos = Xpos + 30;
		}
		if (Xpos == 680) {
			Xpos = 350;
			Ypos += 50;
		}
	}
	deleteFont(font);
	hs->counter++;
}

void deleteHighScores(HighScores* hs){
	deleteBitmap(hs->HighScore);
	deleteBitmap(hs->Exit);
	deleteBitmap(hs->Highlight);
	free(hs);
}

//***************************************SaveMenu****************************************//

SaveMenu* InitSaveMenu(int score) {
	SaveMenu* sm = (SaveMenu*) malloc(sizeof(SaveMenu));
	sm->Exit = loadBitmap("/home/lcom/Tanks/res/Exit.bmp");
	sm->Highlight = loadBitmap("/home/lcom/Tanks/res/Selection.bmp");
	sm->Highlight2 = loadBitmap("/home/lcom/Tanks/res/Selection2.bmp");
	sm->flag1 = 0;
	sm->flag2 = 0;
	sm->flag3 = 0;
	sm->Letter1 = 'X';
	sm->Letter2 = 'X';
	sm->Letter3 = 'X';
	sm->key = 0;
	sm->exit = 0;
	sm->option = 0;
	sm->score = score;
	return sm;
}

void KeyboardHandler(SaveMenu* sm, int key){
	sm->key = MinixKeyToAscii(key);
}

void updateSaveMenu(SaveMenu* sm, Mouse* ms) {
	if (sm->exit == 1 && ms->leftButtonP) {
		sm->option = 1;
		char a[9][14];
		char garbage[20], names[9][4];
		int ints[9];
		FILE *file;
		file = fopen("/home/lcom/Tanks/src/Highscores.txt", "r");
		if (file != NULL) {
			int i;
			for (i = 0; i < 9; ++i) {
				if (fgets(a[i], sizeof a[i], file) == NULL) {
					return;
				}
				sscanf(a[i], "%s %s %d", garbage, &names[i], &ints[i]);
			}
		} else
			return;
		fclose(file);

		if(ints[8] < sm->score){
          ints[8] = sm->score;
          names[8][0] = sm->Letter1;
          names[8][1] = sm->Letter2;
          names[8][2] = sm->Letter3;
		}

		int i, j;
		int aux;
		char aux1[4];
		for (i = 0; i < 9; ++i) {
			for (j = i + 1; j < 9; ++j) {
				if (ints[i] < ints[j]) {
					aux = ints[i];
					strcpy(aux1, names[i]);
					strcpy(names[i], names[j]);
					ints[i] = ints[j];
					strcpy(names[j], aux1);
					ints[j] = aux;
				}
			}
		}

		file = fopen("/home/lcom/Tanks/src/Highscores.txt", "w");
		for (j = 0; j < 9; j++) {
			if (j == 0)
				fprintf(file, "%dST %s %d\n", j + 1, names[j], ints[j]);
			else if (j == 1)
				fprintf(file, "%dND %s %d\n", j + 1, names[j], ints[j]);
			else if (j == 2)
				fprintf(file, "%dRD %s %d\n", j + 1, names[j], ints[j]);
			else
				fprintf(file, "%dTH %s %d\n", j + 1, names[j], ints[j]);
		}
		fclose(file);


	} else {
		if (MouseOverBmp(Exit3X, Exit3Y, 394, 70, ms)) {
			sm->exit = 1;
			sm->flag1 = 0;
			sm->flag2 = 0;
			sm->flag3 = 0;
		} else if (MouseOverBmp(500, 200, 36, 36, ms)) {
			if (sm->key != '\0'){
				sm->Letter1 = sm->key;
			}
			sm->exit = 0;
			sm->flag1 = 1;
			sm->flag2 = 0;
			sm->flag3 = 0;
		} else if (MouseOverBmp(550, 200, 36, 36, ms)) {
			if (sm->key != '\0') {
				sm->Letter2 = sm->key;
			}
			sm->exit = 0;
			sm->flag1 = 0;
			sm->flag2 = 1;
			sm->flag3 = 0;
		} else if (MouseOverBmp(600, 200, 36, 36, ms)) {
			if (sm->key != '\0') {
				sm->Letter3 = sm->key;
			}
			sm->exit = 0;
			sm->exit = 0;
			sm->flag1 = 0;
			sm->flag2 = 0;
			sm->flag3 = 1;
		} else {
			sm->exit = 0;
			sm->flag1 = 0;
			sm->flag2 = 0;
			sm->flag3 = 0;
		}

	}
}

void drawSaveMenu(SaveMenu* sm){
	Font* font = InitFont();
	drawBitmap(sm->Exit, Exit3X, Exit3Y, ALIGN_LEFT, 0);
	if (sm->exit == 1) {
		drawBitmap(sm->Highlight, Exit3X, Exit3Y, ALIGN_LEFT, 0);
	} else if (sm->flag1 == 1) {
		drawBitmap(sm->Highlight2, 500, 235, ALIGN_LEFT, 0);
	} else if (sm->flag2 == 1) {
		drawBitmap(sm->Highlight2, 550, 235, ALIGN_LEFT, 0);
	} else if (sm->flag3 == 1) {
		drawBitmap(sm->Highlight2, 600, 235, ALIGN_LEFT, 0);
	}
	drawChar(font, sm->Letter1, 500, 200);
	drawChar(font, sm->Letter3, 600, 200);
	drawChar(font, sm->Letter2, 550, 200);
	char str[15];
	sprintf(str, "%d", sm->score);
	char score[] = "SCORE";
	char name[] = "NAME";
	drawText(font, name, 300, 200);
	drawText(font, score, 270, 400);
	drawText(font, str, 500, 400);
	deleteFont(font);

}

void deleteSaveMenu(SaveMenu* sm){
	deleteBitmap(sm->Exit);
	deleteBitmap(sm->Highlight);
	deleteBitmap(sm->Highlight2);
	free(sm);
}

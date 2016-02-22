#include "BattalionTanks.h"

BattalionTanks* InitBattalionTanks(){
	BattalionTanks* bt = (BattalionTanks*) malloc(sizeof(BattalionTanks));

	bt->irq_timer = timer_subscribe_int();
	bt->irq_timer = BIT(bt->irq_timer);
	bt->irq_mouse = ms_subscribe_int();
	bt->irq_mouse = BIT(bt->irq_mouse);
	bt->irq_keyboard = kbd_subscribe_int();
	bt->irq_keyboard = BIT(bt->irq_keyboard);
	bt->irq_rtc = rtc_subscribe_int();
	bt->irq_rtc = BIT(bt->irq_rtc);
	if (bt->irq_timer == -1 || bt->irq_keyboard == -1 || bt->irq_mouse == -1 || bt->irq_rtc == -1)
		return NULL;

	bt->timer_flag = 0;
	bt->keyboard_flag = 0;
	bt->mouse_flag = 0;
	bt->timer_counter = 0;

	bt->g = NULL;
	bt->mp = NULL;
	bt->mm = NULL;
	bt->pm = NULL;
	bt->hs = NULL;
	bt->sm = NULL;

	bt->d = malloc(sizeof(Date));
	bt->d = InitDate();
	
	bt->ms = malloc(sizeof(Mouse));
	bt->ms = InitMouse();

	MS_to_KBD_Commands(MS_SET_STR_MODE);
	MS_to_KBD_Commands(MS_DATA_PACKETS);

	bt->currentState = MainMenuS;
	return bt;
}

void updateBattalionTanks(BattalionTanks* bt) {
	resetFlags(bt);
	switch (bt->currentState) {
	case MainMenuS: {
		bt->mm = (MainMenu*) malloc(sizeof(MainMenu));
		bt->mm = InitMainMenu();
		Loop(bt);
		deleteMainMenu(bt->mm);
		break;
	}
	case MultiPlayS: {
		bt->mp = (MultiPlayerMode*) malloc(sizeof(MultiPlayerMode));
		bt->mp = InitMultiplayerMode();
		Loop(bt);
		break;
	}
	case PlayS: {
		bt->g = (Game*) malloc(sizeof(Game));
		bt->g = InitGame();
		Loop(bt);
		break;
	}
	case HighScoreS:
		bt->hs = (HighScores*) malloc(sizeof(HighScores));
		bt->hs = InitHighScores();
		Loop(bt);
		deleteHighScores(bt->hs);
		break;
	case ExitS:
		bt->currentState = ExitS;
		break;
	}
}

void deleteBattalionTanks(BattalionTanks* bt){
	kdb_unsubscribe_int();
	timer_unsubscribe_int();
	MS_to_KBD_Commands(MS_DSB_STREAM_M);
	ms_unsubscribe_int();
	deleteDate(bt->d);
	deleteMouse(bt->ms);
	free(bt);
}

void Loop(BattalionTanks* bt){
	int ipc_status, r;
	bool endGame = false;
	unsigned long key;
	message msg;
	timer_set_square(0, 60);

	int break_code_flag = false, two_byte = false;
	int pause_flagM = false;
	int pause_flagS = false;
	while (1) {
		r = driver_receive(ANY, &msg, &ipc_status);
		if (r != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & bt->irq_mouse) {
					SetPacket(bt->ms);
					if (bt->ms->packetCounter > 2) {
						bt->mouse_flag = 1;
					}
				}
				if (msg.NOTIFY_ARG & bt->irq_keyboard) {
					key = kbd_read();
					if (key == 0xE0) {
						two_byte = true;
					} else if (two_byte) {
						key |= 0xE0 << 8;
						two_byte = false;
						bt->keyboard_flag = 1;
					} else {
						bt->keyboard_flag = 1;
					}
				}
				if (msg.NOTIFY_ARG & bt->irq_timer) {
					bt->timer_counter++;
					bt->timer_flag = 1;
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {
		}

		switch (bt->currentState) {
		case PlayS:
			if (bt->keyboard_flag) {
				if (key == ESC) {
					pause_flagS = true;
				} else {
					KeyboardInputHandler(bt->g->player, key);
				}
				bt->keyboard_flag = 0;
			}
			if (bt->mouse_flag) {
				updateMouse(bt->ms, 0);
				MouseInputHandler(bt->g->player, bt->ms);
				bt->ms->packetCounter = 0;
				bt->mouse_flag = 0;
			}

			if (bt->timer_flag && bt->timer_counter % 2 == 0) {
				clearBuffer();
				updateGame(bt->g);
				drawGame(bt->g);
				drawMouse(bt->ms, 0);
				updateScreenWithBuffer();
				bt->timer_flag = 0;
				if (OutOfLives(bt->g) && bt->g->player->TankExp.explosionNumber == 0) {
					bt->currentState = MainMenuS;
					//deleteGame(bt->g);
					return;
				}

				else if (BattalionDestroyed(bt->g)) {
					bt->sm = (SaveMenu*) malloc(sizeof(SaveMenu));
					bt->sm = InitSaveMenu(bt->g->score + 100*bt->g->player->lives);
					//deleteGame(bt->g);
					bt->currentState = SaveMenuS;
				}
			}

			if (pause_flagS) {
				bt->pm = (PauseMenu*) malloc(sizeof(PauseMenu));
				bt->pm = InitPauseMenu();
				bt->currentState = PauseMenuS;
			}
			break;

		case MultiPlayS:
			if (bt->keyboard_flag) {
				if (key == ESC) {
					pause_flagM = true;
				} else {
					KeyboardInputHandler(bt->mp->player1, key);
					KeyboardInputHandler(bt->mp->player2, key);
				}
				bt->keyboard_flag = 0;
			}
			if (bt->mouse_flag) {
				updateMouse(bt->ms, 0);
				MouseInputHandler(bt->mp->player1, bt->ms);
				bt->ms->packetCounter = 0;
				bt->mouse_flag = 0;
			}

			if (bt->timer_flag && bt->timer_counter % 2 == 0) {
				clearBuffer();
				updateMultiPlayer(bt->mp);
				drawMultiPlayer(bt->mp);
				drawMouse(bt->ms, 0);
				updateScreenWithBuffer();
				bt->timer_flag = 0;

				if ((bt->mp->player1->lives == 0 && bt->mp->player1->TankExp.explosionNumber == 0) || (bt->mp->player2->lives == 0 && bt->mp->player2->TankExp.explosionNumber == 0)) {
					bt->currentState = MainMenuS;
					//deleteMultiPlayer(bt->mp);
					return;
				}
			}

			if (pause_flagM) {
				bt->pm = (PauseMenu*) malloc(sizeof(PauseMenu));
				bt->pm = InitPauseMenu();
				bt->currentState = PauseMenuS;
			}
			break;

		case MainMenuS:
			if (bt->mouse_flag) {
				updateMouse(bt->ms, 1);
				bt->ms->packetCounter = 0;
				bt->mouse_flag = 0;
			}

			if (bt->timer_flag) {
				updateDate(bt->d);
				clearBuffer();
				updateMainMenu(bt->mm, bt->ms);
				drawMainMenu(bt->mm, bt->d);
				drawMouse(bt->ms, 0);
				updateScreenWithBuffer();
				bt->timer_flag = 0;
			}
			switch (bt->mm->option) {
			case 1:
				bt->currentState = PlayS;
				return;
			case 2:
				bt->currentState = HighScoreS;
				return;
			case 3:
				bt->currentState = ExitS;
				return;
			case 4:
				bt->currentState = MultiPlayS;
				return;
			default:
				break;
			}
			break;

		case PauseMenuS:
			if (bt->mouse_flag) {
				updateMouse(bt->ms, 1);
				bt->ms->packetCounter = 0;
				bt->mouse_flag = 0;
			}

			if (bt->timer_flag) {
				clearBuffer();
				updatePauseMenu(bt->pm, bt->ms);
				drawPauseMenu(bt->pm);
				drawMouse(bt->ms, 0);
				updateScreenWithBuffer();
				bt->timer_flag = 0;
			}
			switch (bt->pm->option) {
			case 1:
				if(pause_flagS){
					bt->currentState = PlayS;
					pause_flagS = false;
					deletePauseMenu(bt->pm);
				} else if (pause_flagM) {
					bt->currentState = MultiPlayS;
					pause_flagM = false;
					deletePauseMenu(bt->pm);
				}
				break;
			case 2:
				bt->currentState = MainMenuS;
				deletePauseMenu(bt->pm);
				resetButtons(bt->ms);
				return;
			default:
				break;
			}
			break;

		case HighScoreS:
			if (bt->mouse_flag) {
				updateMouse(bt->ms, 1);
				bt->ms->packetCounter = 0;
				bt->mouse_flag = 0;
			}

			if (bt->timer_flag) {
				if(bt->hs->counter == 0){
					clearBuffer();
					drawHighScores(bt->hs);
				}
				updateHighScores(bt->hs, bt->ms);
				drawBitmap(bt->hs->HighScore, HighScore2X, HighScore2Y, ALIGN_LEFT, 0);
				drawBitmap(bt->hs->Exit, Exit3X, Exit3Y, ALIGN_LEFT, 0);
				if (bt->hs->exit == 1) {
					drawBitmap(bt->hs->Highlight, Exit3X, Exit3Y, ALIGN_LEFT, 0);
				}
				updateScreenWithBuffer();
				drawMouse(bt->ms, 1);
				bt->timer_flag = 0;
			}
			if (bt->hs->option) {
				bt->currentState = MainMenuS;
				return;
			}
			break;

		case SaveMenuS:
			if (bt->keyboard_flag) {
				KeyboardHandler(bt->sm, key);
				bt->keyboard_flag = 0;
			}
			if (bt->mouse_flag) {
				updateMouse(bt->ms, 1);
				bt->ms->packetCounter = 0;
				bt->mouse_flag = 0;
			}

			if (bt->timer_flag) {
				clearBuffer();
				updateSaveMenu(bt->sm, bt->ms);
				drawSaveMenu(bt->sm);
				drawMouse(bt->ms, 0);
				updateScreenWithBuffer();
				bt->timer_flag = 0;
			}
			switch (bt->sm->option) {
			case 1:
				bt->currentState = MainMenuS;
				deleteSaveMenu(bt->sm);
				return;
			default:
				break;
			}
			break;
		}
	}
}

void resetFlags(BattalionTanks* bt){
	bt->timer_flag = 0;
	bt->keyboard_flag = 0;
	bt->mouse_flag = 0;
}


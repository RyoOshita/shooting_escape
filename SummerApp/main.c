#include "dglib2.h"
#include <time.h>
#include <stdlib.h>
char_far gvram;
char_far bb;
#define white RGB(255, 255, 255)
#define black RGB(107, 107, 107)
#define blue RGB(72, 172, 239)
#define red RGB(192, 57, 43)
#define green RGB(39, 174, 96)
#define NOW timeGetTime()

//�֐��v���g�^�C�v�錾
void TitleProc(void);
void GameProc(void);
//void print_fps(void);
void torisetu1(int wait);
void torisetu2(wait);
void torisetu3(wait);
void player(void);
int countdown(count);
void tama(void);
void tamamove(void);
void enemy(void);
void enemymove(void);
int count = 0;
int x = 25, y = 80;
int g = 3;
int wait = 0;
int wait1 = 0;
int waite1 = 0, waite2;
int t, tx[10], ty[10], tflg[10], te[10];
int e, ex[3], ey[3], eflg[3], ee[3];
int MP = 100;
int life = 3;
int endflg = 0, score = 0;
int levelcount = 0;

main() {
	dg_setscreen(250, 100, 320, 180, 1, "�����Ă悯��I");
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		tflg[i] = 0;
	}
	bb = dg_createBB();
	TitleProc();
}
/****************************************************************************/
void TitleProc(void) {
	int fp = 1, i;
	int ff[2] = { 0,0 };
	int cursor = 0, wait = 0;
	unsigned long starttime;
	starttime = NOW;
	COLORREF pushEnter = white;
	while (1) {
		if (NOW - starttime < 1000 / 60) {
			continue;
		}
		starttime = NOW;
		/********************�w�i�ƃ^�C�g���\���v���O����*****************/
		if (ff[0] == 0) {
			i = 0;
			while (i < 255) {
				dg_gcls(bb, RGB(i, i, i));
				i += 1;
				dg_flip(gvram, bb);
				ML();
			}
		}

		if (ff[0] == 0) {
			dg_setfont(25, 40, "���C���I");
			i = 255;
			while (i > 107) {
				dg_printf2(bb, 125, 15, RGB(i, i, i), -1,
					"�����Ă悯��I");
				i -= 1;
				ff[0] = 1;
				dg_flip(gvram, bb);
				ML();
			}
		}
		dg_gcls(bb, white);
		dg_setfont(25, 40, "���C���I");
		dg_printf2(bb, 125, 15, black, -1,
			"�����Ă悯��I");
		/*************************��������APushEnter�̏���********************************/
		if (ff[1] == 0) {
			dg_deletefont();
			dg_printf2(bb, 120, 130, pushEnter, -1, "Push Enter");
			if (fp == 0) {
				pushEnter += RGB(2, 2, 2);
				if (pushEnter == white) fp = 1;
			}
			else if (fp == 1) {
				pushEnter -= RGB(2, 2, 2);
				if (pushEnter == black) fp = 0;
			}

			if (getch3(VK_RETURN)) {
				getch2(100);
				ff[1] = 1;
			}
		}
		/*********************���j���[����****************************************/
		if (ff[1] == 1) {
			dg_setfont(10, 20, "���C���I");
			if (cursor == 0) {
				dg_printf2(bb, 20, 90, black, blue, "GAMESTART");
			}
			else {
				dg_printf2(bb, 20, 90, black, -1, "GAMESTART");
			}
			if (cursor == 1) {
				dg_printf2(bb, 20, 120, black, blue, "�V�ѕ�");
			}
			else {
				dg_printf2(bb, 20, 120, black, -1, "�V�ѕ�");
			}
			if (cursor == 2) {
				dg_printf2(bb, 20, 150, black, blue, "END");
			}
			else {
				dg_printf2(bb, 20, 150, black, -1, "END");
			}
		}
		dg_deletefont();
		if (getch3(VK_UP) && wait == 0 && ff[1] == 1) {
			if (cursor != 0) {
				cursor--;
			}
			else {
				cursor = 2;
			}
			wait++;
		}
		if (getch3(VK_DOWN) && wait == 0 && ff[1] == 1) {
			if (cursor != 2) {
				cursor++;
			}
			else {
				cursor = 0;
			}
			wait++;
		}
		if (wait > 0) {
			wait++;
			if (wait > 10) {
				wait = 0;
			}
		}
		if (getch3(VK_RETURN)) {
			switch (cursor) {
			case 0:
				GameProc();
			case 1:
				torisetu1(0);
			case 2:
				dg_deleteBB(bb);
				exit(0);
			}
		}
		dg_flip(gvram, bb);
		ML();
	}
}
/***************************************************************************************/
void GameProc(void) {
	int mewait = 0;
	int cf = 0;
	int ef = 0;
	int endwait = 0;
	int MC = 0;
	unsigned long starttime;
	starttime = NOW;
	while (endflg != 1) {
		if (NOW - starttime < 1000 / 60) {
			continue;
		}
		starttime = NOW;
		dg_gcls(bb, white);	//��ʃN���A
		if (MP < 100 && MC >= 15) {
			MP++;
			MC = 0;
		}
		dg_box(bb, 0, 150, 320, 5, 1, black);
		dg_line(bb, x, y, x, y + 30, black);
		dg_line(bb, x, y, x + 25, y + 15, black);
		dg_line(bb, x, y + 30, x + 25, y + 15, black);
		if (MP > 29) {
			dg_box(bb, 270, 5, MP / 2, 10, 1, blue);
		}
		else {
			dg_box(bb, 270, 5, MP / 2, 10, 1, red);
		}
		for (int lifei = 1; lifei <= life; lifei++) {
			dg_circle(bb, lifei * 15, 5, 5, red);
		}
		dg_printf2(bb, 0, 15, black, -1, "score : %09d", score);

		if (cf != 0) {
			enemy();
			player();
			tama();
			tamamove();
			enemymove();

			/**********************************�G�Ǝ��@�̓����蔻��***********************/
			for (e = 0; e < 3; e++) {
				if (x <= ex[e] + 15 && x + 15 >= ex[e] && y + 10 <= ey[e] + 30 && y + 22 >= ey[e] && mewait == 0 && eflg[e] == 1) {
					x -= 10;
					eflg[e] = 0;
					life--;
					mewait = 1;
					if (life <= 0) { life = 0; endflg = 1; break; }
				}
				if (mewait != 0) {
					mewait++;
				}
				if (mewait >= 60) { x += 10; mewait = 0; }

			}
			/**********************************************�ʂ̓����蔻��*****************************************************/
			for (t = 0; t < 10; t++) {
				if (tflg[t] == 1) {
					for (e = 0; e < 3; e++) {
						if (eflg[e] == 1) {
							if (ee[e] == 0 && tx[t] <= ex[e] + 15 && tx[t] + 5 >= ex[e] && ty[t] <= ey[e] + 30 && ty[t] + 5 >= ey[e]) {
								tflg[t] = 0;
								eflg[e] = 0;
								score += 100;
								levelcount += 100;
								break;
							}

							if (ee[e] == 1 && tx[t] <= ex[e] + 15 && tx[t] + 5 >= ex[e] && ty[t] <= ey[e] + 30 && ty[t] + 5 >= ey[e] && te[t] == ee[e]) {
								tflg[t] = 0;
								eflg[e] = 0;
								score += 100;
								levelcount += 100;
								break;
							}

							if (ee[e] == 2 && tx[t] <= ex[e] + 15 && tx[t] + 5 >= ex[e] && ty[t] <= ey[e] + 30 && ty[t] + 5 >= ey[e] && te[t] == ee[e]) {
								tflg[t] = 0;
								eflg[e] = 0;
								score += 100;
								levelcount += 100;
								break;
							}

							if (ee[e] == 3 && tx[t] <= ex[e] + 15 && tx[t] + 5 >= ex[e] && ty[t] <= ey[e] + 30 && ty[t] + 5 >= ey[e] && te[t] == ee[e]) {
								tflg[t] = 0;
								eflg[e] = 0;
								score += 100;
								levelcount += 100;
								break;
							}

							if (ee[e] == 4 && tx[t] <= ex[e] + 15 && tx[t] + 5 >= ex[e] && ty[t] <= ey[e] + 30 && ty[t] + 5 >= ey[e]) {
								tflg[t] = 0;
								eflg[e] = 0;
								score -= 10;
								levelcount -= 10;
								break;
							}
						}
					}
				}
			}
		}


		if (cf == 0) {
			cf = countdown();
		}
		MC++;
		dg_flip(gvram, bb);
		ML();
	}
	while (getch3('E') != 1) {
			if (NOW - starttime < 1000 / 60) {
				continue;
			}
			starttime = NOW;

			dg_gcls(bb,white);
			dg_setfont(30, 60, "���C���I");
			if (ef == 0) {
				dg_printf2(bb, 50, 50, black, -1, "GameOver");
				endwait++;
				if (endwait > 120) { endwait = 0; ef = 1; }
			}
			else if (ef == 1) {
				dg_printf2(bb, 50, 50, black, -1, "score %d", score);
				dg_setfont(5, 10, "���C���I");
				dg_printf2(bb, 0, 170, black, -1, "�uZ�v�L�[�ł�����x");
				dg_printf2(bb, 280, 170, black, -1, "�uX�v�L�[�ŏI��");

				if (getch3('Z') && wait == 0) {
					count = 0;
					wait1 = 0;
					x = 25, y = 80;
					g = 3;
					waite1 = 0, waite2;
					t, tx[10], ty[10], tflg[10], te[10];
					e, ex[3], ey[3], eflg[3], ee[3];
					MP = 10;
					life = 3;
					MP = 100;
					endflg = 0, score = 0;
					for (int i = 0; i < 10; i++) {
						tflg[i] = 0;
					}
					GameProc();
				}
				else if (getch3('X') && wait == 0) {
					dg_deleteBB(bb);
					exit(0);
				}
				if (wait > 0) {
					wait++;
					if (wait > 10) {
						wait = 0;
					}
				}
			}
			dg_deletefont();
			dg_flip(gvram, bb);
			ML();
	}
	dg_deleteBB(bb);
	return;
}

void torisetu1(int wait) {
	unsigned long starttime;
	starttime = NOW;
	COLORREF pushEnter = white;
	while (1) {
		if (NOW - starttime < 1000 / 60) {
			continue;
		}
		starttime = NOW;

		dg_gcls(bb, white);
		dg_setfont(20, 40, "���C���I");
		dg_printf2(bb, 115, 0, black, -1, "�V�ѕ�");
		dg_setfont(10, 20, "���C���I");
		dg_printf2(bb, 90, 60, black, -1, "���͑ł��āZ�͂悯��I");
		dg_printf2(bb, 90, 90, black, -1, "�ʂ�");
		dg_printf2(bb, 90, 110, black, -1, "�m�[�}���A���A���A��");
		dg_printf2(bb, 90, 130, black, -1, "�̂S��ނ���");
		dg_printf2(bb, 90, 150, black, -1, "���A���A����MP�������");
		dg_setfont(5, 10, "���C���I");
		dg_printf2(bb, 0, 170, black, -1, "�uZ�v�L�[�őO��");
		dg_printf2(bb, 280, 170, black, -1, "�uX�v�L�[�Ŏ���");
		if (getch3('Z') && wait == 0) {
			TitleProc();
		}
		else if (getch3('X') && wait == 0) {
			wait++;
			torisetu2(wait);
		}
		if (wait > 0) {
			wait++;
			if (wait > 10) {
				wait = 0;
			}
		}
		dg_flip(gvram, bb);
	}
}

void torisetu2(wait) {
	unsigned long starttime;
	starttime = NOW;
	COLORREF pushEnter = white;
	while (1) {
		if (NOW - starttime < 1000 / 60) {
			continue;
		}
		starttime = NOW;

		dg_gcls(bb, white);
		dg_setfont(20, 40, "���C���I");
		dg_printf2(bb, 115, 0, black, -1, "��������");
		dg_setfont(10, 20, "���C���I");
		dg_printf2(bb, 90, 60, black, -1, "�������̂Ƃ��͉��ōU�����Ă��������I");
		dg_printf2(bb, 90, 90, black, -1, "�����Ԃ̂Ƃ��͐������ōU��");
		dg_printf2(bb, 90, 120, black, -1, "�����̂Ƃ��͑������ōU��");
		dg_printf2(bb, 90, 150, black, -1, "�����΂̂Ƃ��͉������ōU��");
		dg_setfont(5, 10, "���C���I");
		dg_printf2(bb, 0, 170, black, -1, "�uZ�v�L�[�őO��");
		dg_printf2(bb, 280, 170, black, -1, "�uX�v�L�[�Ŏ���");
		if (getch3('Z') && wait == 0) {
			wait++;
			torisetu1(wait);
		}
		else if (getch3('X') && wait == 0) {
			wait++;
			torisetu3(wait);
		}
		if (wait > 0) {
			wait++;
			if (wait > 10) {
				wait = 0;
			}
		}
		dg_flip(gvram, bb);

	}
}

void torisetu3(wait) {
	unsigned long starttime;
	starttime = NOW;
	COLORREF pushEnter = white;
	while (1) {
		if (NOW - starttime < 1000 / 60) {
			continue;
		}
		starttime = NOW;

		dg_gcls(bb, white);
		dg_setfont(20, 40, "���C���I");
		dg_printf2(bb, 115, 0, black, -1, "�������");
		dg_setfont(10, 20, "���C���I");
		dg_printf2(bb, 90, 60, black, -1, "�uZ�v�Ńm�[�}��");
		dg_printf2(bb, 90, 80, black, -1, "�uX�v�ŉ�");
		dg_printf2(bb, 90, 100, black, -1, "�uC�v�Ő�");
		dg_printf2(bb, 90, 120, black, -1, "�uV�v�ő�");
		dg_printf2(bb, 90, 140, black, -1, "�uSpase�v�ŃW�����v�I");
		dg_setfont(5, 10, "���C���I");
		dg_printf2(bb, 0, 170, black, -1, "�uZ�v�L�[�őO��");
		dg_printf2(bb, 260, 170, black, -1, "�uX�v�L�[�Ń^�C�g����");
		if (getch3('Z') && wait == 0) {
			wait++;
			torisetu2(wait);
		}
		else if (getch3('X') && wait == 0) {
			TitleProc();
		}
		if (wait > 0) {
			wait++;
			if (wait > 10) {
				wait = 0;
			}
		}
		dg_flip(gvram, bb);

	}
}

int countdown(void) {
	int f = 0;
	dg_setfont(75, 150, "���C���I");
	if (count >= 0 && count <= 59) {
		count++;
		dg_printf2(bb, 125, 15, black, -1, "3");
		dg_deletefont();
		dg_flip(gvram, bb);
	}
	if (count >= 60 && count <= 119) {
		count++;
		dg_printf2(bb, 125, 15, black, -1, "2");
		dg_deletefont();
		dg_flip(gvram, bb);
	}
	if (count >= 120 && count <= 180) {
		if (count == 180) f = 1;
		count++;
		dg_printf2(bb, 125, 15, black, -1, "1");
		dg_deletefont();
		dg_flip(gvram, bb);
	}
	return f;
}
void player(void) {
	if (y >= 120) {
		wait = 0;
	}
	y += g;
	if (y > 120) y = 120;
	if (y < 20) y = 20;
	if (getch3(VK_SPACE) && g > -9 && wait == 0) {
		g -= 9;
		wait = 1;
	}
	g++;
	if (g > 20) g = 20;
	return;
}

void tama() {
	if (getch3('Z') && wait1 == 0) {
		for (t = 0; t < 10; t++) {
			if (tflg[t] == 0) {
				tflg[t] = 1;
				tx[t] = 50;
				ty[t] = y + 15;
				te[t] = 0;
				wait1++;
				dg_circle(bb, tx[t], ty[t], 5, black);
				break;
			}
		}
	}

	if (getch3('X') && MP > 29 && wait1 == 0) {
		for (t = 0; t < 10; t++) {
			if (tflg[t] == 0) {
				MP -= 30;
				tflg[t] = 1;
				tx[t] = 50;
				ty[t] = y + 15;
				te[t] = 1;
				wait1++;
				dg_circle(bb, tx[t], ty[t], 5, red);
				break;
			}
		}
	}

	if (getch3('C') && MP > 29 && wait1 == 0) {
		for (t = 0; t < 10; t++) {
			if (tflg[t] == 0) {
				MP -= 30;
				tflg[t] = 1;
				tx[t] = 50;
				ty[t] = y + 15;
				te[t] = 2;
				wait1++;
				dg_circle(bb, tx[t], ty[t], 5, blue);
				break;
			}
		}
	}

	if (getch3('V') && MP > 29 && wait1 == 0) {
		for (t = 0; t < 10; t++) {
			if (tflg[t] == 0) {
				MP -= 30;
				tflg[t] = 1;
				tx[t] = 50;
				ty[t] = y + 15;
				te[t] = 3;
				wait1++;
				dg_circle(bb, tx[t], ty[t], 5, green);
				break;
			}
		}
	}
	if (wait1 > 0) {
		wait1++;
		if (wait1 > 10) {
			wait1 = 0;
		}
	}
}

void tamamove(void) {
	for (t = 0; t < 10; t++) {
		if (tflg[t] == 1) {
			tx[t] += 4;
			if (tx[t] > 320) { tflg[t] = 0; }
			switch (te[t]) {
			case 0:
				dg_circle(bb, tx[t], ty[t], 5, black);
				break;
			case 1:
				dg_circle(bb, tx[t], ty[t], 5, red);
				break;
			case 2:
				dg_circle(bb, tx[t], ty[t], 5, blue);
				break;
			case 3:
				dg_circle(bb, tx[t], ty[t], 5, green);
				break;
			}
		}
	}

}

void enemy(void) {
	int level = 450;
	if (levelcount >= 1000 && level > 100) { levelcount = 0; level -= 50; }
	if (waite1 == 0) {
		waite2 = rand() % level + 50;
		for (e = 0; e < 3; e++) {
			if (eflg[e] == 0) {
				ee[e] = rand() % 7;
				eflg[e] = 1;
				ex[e] = 320;
				ey[e] = 120;
				if (ee[e] >= 5) { ee[e] = 0; }
				switch (ee[e]) {
				case 0:
					dg_box(bb, ex[e], ey[e], 15, 30, 1, black);
					break;
				case 1:
					dg_box(bb, ex[e], ey[e], 15, 30, 1, green);
					break;
				case 2:
					dg_box(bb, ex[e], ey[e], 15, 30, 1, red);
					break;
				case 3:
					dg_box(bb, ex[e], ey[e], 15, 30, 1, blue);
					break;
				case 4:
					dg_circle(bb, ex[e] + 15, ey[e] + 15, 15, black);
					break;
				}
				waite1++;
				break;
			}
		}
	}
	if (waite1 > 0) {
		waite1++;
		if (waite1 > waite2) {
			waite1 = 0;
		}
	}
}

void enemymove(void) {
	for (e = 0; e < 3; e++) {
		if (eflg[e] == 1) {
			ex[e] -= 3;
			if (ex[e] < -15) eflg[e] = 0;
			switch (ee[e]) {
			case 0:
				dg_box(bb, ex[e], ey[e], 15, 30, 1, black);
				break;
			case 1:
				dg_box(bb, ex[e], ey[e], 15, 30, 1, green);
				break;
			case 2:
				dg_box(bb, ex[e], ey[e], 15, 30, 1, red);
				break;
			case 3:
				dg_box(bb, ex[e], ey[e], 15, 30, 1, blue);
				break;
			case 4:
				dg_circle(bb, ex[e] + 15, ey[e] + 15, 15, black);
				break;
			}
			//�����Ƀ_���[�W�󂯂����̏���
		}
	}
}


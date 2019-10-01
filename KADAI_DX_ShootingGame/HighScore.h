#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_


#include"SceneManeger.h"

#define SHOWRANKMAX	(5)

#define RANKINGSTARTX	(SCREEN_WIDTH*0.175f)
#define RANKINGSTARTY	(SCREEN_HEIGHT*0.2f)

enum Alphabet {
	A_A = 0,
	A_B,
	A_C,
	A_D,
	A_E,
	A_F,
	A_G,
	A_H,
	A_I,
	A_J,
	A_K,
	A_L,
	A_M,
	A_N,
	A_O,
	A_P,
	A_Q,
	A_R,
	A_S,
	A_T,
	A_U,
	A_V,
	A_W,
	A_X,
	A_Y,
	A_Z,
	A_Up,
	A_Down,
	A_Space,
	A_Black,
	A_Count,

};

void InitHS();
void UnInitHS();
void UpdateHS();
void DrawHS();

void SetRoundScore(int score);
void ScoreSorting(int turn);
SceneProc SetupHSScene(void);
#endif
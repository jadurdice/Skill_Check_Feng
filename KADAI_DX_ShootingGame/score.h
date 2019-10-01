#ifndef _SCORE_H_
#define _SCORE_H_

#define SCOREINGIDMAX	(10)
#define POWINGIDMAX		(3)
#define MISSILEINGIDMAX	(3)
	
#define SCORESTARTX	(SCREEN_WIDTH*0.1f)
#define POWSTARTX	(SCREEN_WIDTH*0.45f)
#define MISSILESTARTX	(SCREEN_WIDTH*0.65f)
#define LIVESSTARTX	(SCREEN_WIDTH*0.925f)

void InitUI();
void UninitUI();
void UpdateUI();
void DrawUI();

void AddScore(int addNum);
void ResetScore();
int GetTextTexNo();

#endif
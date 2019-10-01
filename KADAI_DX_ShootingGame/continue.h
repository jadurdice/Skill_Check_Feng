#ifndef _CONTINUE_H_
#define _CONTINUE_H_

#define STAGEX	(SCREEN_WIDTH - 580.0f)
#define	STAGEY	((SCREEN_HEIGHT - 300)*0.5f)

void InitConti();
void UninitConti();
void UpdateConti();
void DrawConti();
void SetConti();
void SetStage();
void SetComplete();
void SetCaution();
#endif
#include"Fade.h"
#include"Game.h"
#include"StageManeger.h"
#include"sprite.h"
#include"texture.h"
#include"complex"
#include"Logo.h"
#include"BackGround.h"

float fadeFactor;
float fadeInTiming;
float fadeOutTiming;
int fadeTexNo;




void InitFade() {
	
	if (GetSceneIndex() == S_Title) {
		fadeFactor = 1.0f;
	}
	else {
		fadeFactor = 0.0f;
	}

	fadeInTiming = FADEINTIME;
	fadeOutTiming = FADEOUTTIME;
	fadeTexNo =  LoadTexture("rom:/bg.tga");
}

void UpdateFade() {

	//playƒV[ƒ“‚È‚ç

	
	float swapCnt = GetSwapCnt();
	if (swapCnt >= 1.0f) { 
		if (GetSceneIndex() == S_Title) {
			StartLogo();
		}
		return;
	}
	if (swapCnt < 0.25f) {
		fadeFactor = swapCnt / 0.25f;
	}
	else if (swapCnt > 0.75f) {
		fadeFactor = sinf(DEGREE_TO_RADIAN(90.0f * (1 + ((swapCnt - fadeInTiming) / (1.0 - fadeInTiming)))));
	}

	if (swapCnt > 0.25f && swapCnt < 0.75f) {
		SwapRoomData();
		CleanBGUV();
	}



}


void DrawFade() {
	SetColor(0, 0, 0, fadeFactor * 255);
	DrawSpriteUV(-1, 0.0f, 0.0f, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

		SetColor(255, 255, 255, 255);

}

void SetFadeTime(bool isOut, float time) {
	if (isOut) {
		fadeOutTiming = time;
	}
	else {
		fadeInTiming = time;
	}
}


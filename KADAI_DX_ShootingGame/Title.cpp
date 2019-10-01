#include"Title.h"
#include"input.h"
#include"BackGround.h"
#include"Sprite.h"
#include"sound.h"
#include"Fade.h"
#include"texture.h"

int titleCnt = 0;

int presentTexNo;
int logoTexNo;
int pressTexNo;
int blinkFactor;

void InitTitle() {

	presentTexNo = TextureSetLoadFile("asset/texture/present.png", 619, 314);
	logoTexNo = TextureSetLoadFile("asset/texture/Logo.png",707, 337);
	pressTexNo = TextureSetLoadFile("asset/texture/press.png", 608, 70);

	BackInit();
	SetScrollSpeed(-0.5f);
	PlaySound(B_TITLE);

	blinkFactor = 60;
	
	SetFade(60, D3DCOLOR_RGBA(0, 0, 0, 0), false);

}
void UnInitTitle() {
	StopSound(B_TITLE);
}
void UpdateTitle() {

	BackUpdate();
	titleCnt += 1;


	if (titleCnt == 250) {
		SetFade(60, D3DCOLOR_RGBA(0, 0, 0, 255), true);
	}
	if (titleCnt == 400) {
		SetFade(30, D3DCOLOR_RGBA(255, 255, 255, 255), false);
	}
	if (titleCnt == 430) {
		SetFade(30, D3DCOLOR_RGBA(255, 255, 255, 0), false);
	}
	if (titleCnt >= 400 && Keyboard_IsTrigger(DIK_K)) {
		if (!GetFadeState()) {
			PlaySound(SE_DECIDE);
			blinkFactor = 5;
			SetScene(S_Game);
			SetTrailEnable();
		}
	}
}
void DrawTitle() {
	BackDraw();
	if (titleCnt < 360) {
		DrawSpriteCut(presentTexNo, (SCREEN_WIDTH - 620)*0.5f, (SCREEN_HEIGHT - 314)*0.5f, 0, 0, 619, 314);
	}
	else {
		DrawSpriteCut(logoTexNo, (SCREEN_WIDTH- 707)*0.5f, (SCREEN_HEIGHT*0.75f - 337)*0.5f, 0, 0, 707, 337);
		if (titleCnt / blinkFactor % 2 == 0) {
			SetColor(255, 255, 255, 0);
		}
		else {
			SetColor(255, 255, 255, 255);
		}
		DrawSpriteCut(pressTexNo, (SCREEN_WIDTH - 608)*0.5f, (SCREEN_HEIGHT*0.75f), 0, 0, 608, 70);
	}
	SetColor(255, 255, 255, 255);
}

SceneProc SetupTitleScene()
{
	SceneProc proc = {
	S_Title,
	"Title",
	InitTitle,
	UnInitTitle,
	UpdateTitle,
	DrawTitle
	};

	return proc;
};
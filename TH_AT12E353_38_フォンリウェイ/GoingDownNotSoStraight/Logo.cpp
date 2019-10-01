#include"Logo.h"
#include"sprite.h"
#include"texture.h"
#include"Game.h"
#include"complex"

unsigned int logoTexNo;
Float2 logoPos;
Float2 logoPosNext;
float alpha = 0;
float alphaFactor = 0;

void InitLogo() {
	logoTexNo = LoadTexture("rom:/logo.tga");
	logoPos = MakeFloat2(SCREEN_WIDTH*0.5f - 3 * LOGOADJUST, 0.0f);
	logoPosNext = logoPos;
}
void UninitLogo() {
	UnloadTexture(logoTexNo);
	alpha = 0;
	alphaFactor = 0.0f;
}
void UpdateLogo() {
	logoPos = GameSystem::LerpFloat2(logoPos, logoPosNext, 0.01f);
	alpha += alphaFactor;
	if (alpha > 255) {
		alpha = 255;
	}
}
void DrawLogo() {
	SetColor(255, 255, 255, alpha);
	DrawSpriteUV(logoTexNo, logoPos.x, logoPos.y, 0.0f, 0.0f, 6.0f*0.125f, 2.0f*0.125f, 6 * LOGOADJUST, 2 * LOGOADJUST);
	SetColor(255, 255, 255, 255);
	DrawSpriteUV(logoTexNo, SCREEN_WIDTH*0.5f - 3.5f*128.0f, SCREEN_HEIGHT- 0.5f*128.0f, 0.0f, 2.0f*0.125f, 7.0f*0.125f, 0.125f, 7 * 128, 128);
}

void StartLogo() {
	logoPosNext.y = SCREEN_HEIGHT * 0.1f;
	alphaFactor = 1.0f;
}
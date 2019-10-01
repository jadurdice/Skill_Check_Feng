#include"BackGround.h"
#include"texture.h"
#include"sprite.h"
#include"SenceManeger.h"
#include"system.h"
#include"Game.h"
#include"Player.h"

unsigned int bgTex;
Float2 uvVelocity;
Float2 uvNow;

void InitBG() {
	CleanBGUV();
	if (GetSceneIndex() == S_Title) {
		bgTex = LoadTexture("rom:/bgTitle.tga");
	}
	else {
		bgTex = LoadTexture("rom:/bg.tga");
	}
}
void UninitBG() {
	UnloadTexture(bgTex);
}
void UpdateBG() {
	if (GetSceneIndex() == S_Title) {
		uvVelocity = { 0.0005f,0.0f };
		uvNow = MakeFloat2(uvNow.x + uvVelocity.x, uvNow.y);
	}
	else {
		uvVelocity = GetPlayerVelocity();
		uvNow = MakeFloat2(uvNow.x + uvVelocity.x*0.00001f, uvNow.y);
	}

}
void DrawBG() {
	DrawSpriteUV(bgTex, 0.0f, 0.0f, uvNow.x, uvNow.y, 1.0f, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	
}
void CleanBGUV() {
	uvNow = { 0.0f,0.0f };
	uvVelocity = { 0.0f,0.0f };
}
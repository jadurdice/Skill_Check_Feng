#include"texture.h"
#include"Sprite.h"
#include"BackGround.h"
#include"common.h"
#include"Player.h"

int backTexNo;
int frontTexNo;
float u;

float scrollSpeed;
float newSpeed;

void BackInit() {
	if (GetSceneIndex() == S_Game) {
		backTexNo = TextureSetLoadFile("asset/texture/bg.png", 1393, 1118);
	}
	else {
		backTexNo = TextureSetLoadFile("asset/texture/bg2.png", 1363, 876);
	}

	scrollSpeed = 0.5f;
	newSpeed = 0.5f;
}
void BackUnInit() {

}
void BackUpdate(){

	u += scrollSpeed;
	scrollSpeed = GameSystem::Lerp(scrollSpeed,newSpeed,DELTATIME);

}
void BackDraw() {
	SetColor(128, 128, 128, 255);
	DrawSpriteCut(backTexNo, 0.0f, 0.0f, u, 0.0f, 1393, 1118);
	SetColor(255,255,255, 255);
}

D3DXVECTOR2 frontUV[3];

void FrontInit() {
	for (int i = 0; i < 3; i++)
	{
		frontUV[i] = { 0.0f,0.0f };
	}
	frontTexNo = TextureSetLoadFile("asset/texture/clouds.png", 256, 103);
}
void FrontUnInit() {
}
void FrontUpdate() {
	for (int i = 0; i < 3; i++)
	{
		frontUV[i] -= (i+1) * GetActionPlayer()->playerVelocity;
		frontUV[i].x += scrollSpeed / ((float)i+(0.5f));
		frontUV[i].x += GameSystem::RandFloat(0.0f, 3.0f);
		frontUV[i].y += GameSystem::RandFloat(-2.0f, 2.0f);
	}

}
void FrontDraw() {

	for (int i = 0; i < 3; i++)
	{
		SetColor(255, 255, 255, 32+ 32*i);
		float show = frontUV[i].y + 320.0f * i;
		if (show > SCREEN_HEIGHT) { show -= SCREEN_HEIGHT + 103; }
		if (show < -103) { show += SCREEN_HEIGHT; }
		DrawSpriteCut(frontTexNo, 0.0f, show, frontUV[i].x, 103, SCREEN_WIDTH, 103);
	}
	SetColor(255, 255, 255, 255);

}

void SetScrollSpeed(float speed) {
	newSpeed = speed;
}

int GetBGTexNo() {
	return backTexNo;
}

float GetScrollSpeed() {
	return scrollSpeed;
}
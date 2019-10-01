#include"Fade.h"
#include"texture.h"
#include"Sprite.h"
#include"d3dsystem.h"

#include"SceneManeger.h"

char fadeState = 0;
int fadeStartFrame = 0;
int fadeNowFrame = 0;
int fadeLength = 0;
D3DCOLOR fadeColor = 0;
D3DCOLOR fadeNextColor = 0;

unsigned int trailTexNo;
bool isTrail = false;
float upPos;
float downPos;

void InitFade() {
	SetFade(90, D3DCOLOR_RGBA(0, 0, 0, 0), false);
	fadeColor = D3DCOLOR_RGBA(0, 0, 0, 255);

	trailTexNo = TextureSetLoadFile("asset/texture/trail.png",1371,478);
}
void UnInitFade() {

}
void UpdateFade() {



	if (!(fadeState & FADE_NONE)) {

		int elapsedFrame = fadeNowFrame - fadeStartFrame;

		float e = elapsedFrame / (float)fadeLength;
		float alpha = 0;

		if (elapsedFrame >= fadeLength) {
			e = 1.0f;
		}

		if ((fadeState & FADE_OUT)) {
			alpha = e;
		}
		else {
			alpha = 1 - e;
		}

		if (fadeState & FADE_BLACK) {
			alpha = 1;
		}

		D3DXCOLOR color = fadeColor;
		D3DXCOLOR nextColor = fadeNextColor;
		color.r = GameSystem::Lerp(color.r, nextColor.r, e*0.2f);
		color.g = GameSystem::Lerp(color.g, nextColor.g, e*0.2f);
		color.b = GameSystem::Lerp(color.b, nextColor.b, e*0.2f);
		color.a = GameSystem::Lerp(color.a, nextColor.a, e*0.2f);
		fadeColor = color;


		upPos = GameSystem::Lerp((1371 * -0.5f),SCREEN_WIDTH*0.5f,alpha);
		downPos = GameSystem::Lerp((1371 * 1.5f),SCREEN_WIDTH*0.5f,alpha);

		if (elapsedFrame >= fadeLength) {
			if (GetReadyToChange() && (fadeState & FADE_OUT)) {
				JumpScene();
				return;
			}
			fadeState = FADE_NONE;

		}
	}
	fadeNowFrame++;
}
void DrawFade() {
	D3DXCOLOR color = fadeColor;
	LPDIRECT3DDEVICE9 device = GetDevice();

	FadeVertex s[] = {
	{D3DXVECTOR4(0.0f,			0.0f,			0.0f,1.0f),color},
	{D3DXVECTOR4(SCREEN_WIDTH,	0.0f,			0.0f,1.0f),color},
	{D3DXVECTOR4(0.0f,			SCREEN_HEIGHT,	0.0f,1.0f),color},
	{D3DXVECTOR4(SCREEN_WIDTH,	SCREEN_HEIGHT,	0.0f,1.0f),color}
	};

	device->SetFVF(FVF_FADE_VERTEX);
	device->SetTexture(0, NULL);
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, s, sizeof(FadeVertex));

	if (!isTrail) {return;}

	DrawSpriteRotCenter(trailTexNo, upPos,		(SCREEN_HEIGHT - 478)*0.5f, 0, 0, 1371, 478, 0, 0, 0, 1.0f, 1.0f);
	DrawSpriteRotCenter(trailTexNo, downPos,	(SCREEN_HEIGHT + 478)*0.5f, 0, 0, 1371, 478, 0, 0, 0, 1.0f, 1.0f);

}
void SetFade(int frame, D3DCOLOR color, bool isFadeOut) {
	fadeStartFrame = fadeNowFrame;
	fadeNextColor = color;
	fadeLength = frame;
	if (isFadeOut) {
		fadeState = FADE_OUT;
	}
	else {
		fadeState = FADE_IN;
	}

}
bool GetFadeState() {
	if ((fadeState & FADE_NONE) || (fadeState & FADE_BLACK)) {
		return false;
	}
	return true;
}

void SetTrailEnable() {
	isTrail = !isTrail;
}


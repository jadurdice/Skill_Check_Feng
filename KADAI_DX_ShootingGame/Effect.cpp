#include"Effect.h"
#include"Game.h"
#include"sprite.h"


class Effect
{
public:
	unsigned int texNo;
	D3DXVECTOR2 pos;
	int lifeTime;
	float scale;
	bool isEnable;
	
	bool GetIsEnable();
	void SetTexture(unsigned int inputTex);
	

private:

};


class Explosion : public Effect {
public :
	void SetPosition(D3DXVECTOR2 playPos, float playScale, unsigned int inputTexNo);
	void DrawExplosion();
	void UpdateExplosion();

};
bool Effect::GetIsEnable()
{
	return isEnable;
}

void Effect::SetTexture(unsigned int inputTex)
{
	texNo = inputTex;
}
void Explosion::SetPosition(D3DXVECTOR2 playPos, float playScale, unsigned int inputTexNo)
{
	isEnable = true;
	pos = playPos;
	scale = playScale;
	lifeTime = 64;
	SetTexture(inputTexNo);
}

void Explosion::UpdateExplosion() {
	if (isEnable) {
		lifeTime -= 1;
		scale += 0.002f;
		if (lifeTime < 0) {
			isEnable = false;
		}
	}
}
void Explosion::DrawExplosion() {
	if (!isEnable) { return; }

	float uNow;

	if (lifeTime > 32) {
		int nowFrame = ((lifeTime / 8));

		uNow = 4 - (nowFrame % 5);

	}
	else {
		uNow = 4- (lifeTime / 16);

		float fade = (float)lifeTime / (float)64.0f;

		SetColor(255,255,255,255*(((fade) * 2)));

	}

	uNow *= 0.2f * 168;

	DrawSpriteRotPlg(
		texNo,
		pos.x, pos.y,
		uNow, 0,
		33, 33,
		0,
		0.5f, 0.5f,
		scale, scale
	);


	SetColor(255, 255, 255, 255);
}


unsigned int explosionTexNo;
Explosion actExp[EXP_MAX];

void InitEffect() {
	explosionTexNo = TextureSetLoadFile("asset/texture/explosion.png", 168, 33);
}
void UninitEffect() {
	for (int i = 0; i < EXP_MAX; i++)
	{
		if (!actExp[i].GetIsEnable()) {
			continue;
		}
		actExp[i].isEnable = false;
	}
}
void UpdateEffect() {
	for (int i = 0; i < EXP_MAX; i++)
	{
		if (!actExp[i].GetIsEnable()){
			continue;
		}
		actExp[i].UpdateExplosion();
	}
}
void DrawEffect() {
	for (int i = 0; i < EXP_MAX; i++)
	{
		if (!actExp[i].GetIsEnable()) {
			continue;
		}
		actExp[i].DrawExplosion();
	}
}

void SetEffect(D3DXVECTOR2 effGenePos) {
	for (int i = 0; i < EXP_MAX; i++)
	{
		if (!actExp[i].GetIsEnable()) {
			actExp[i].SetPosition(effGenePos,2.0f,explosionTexNo);
			break;
		}

	}
}



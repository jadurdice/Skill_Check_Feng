#include"Particle.h"
#include"Game.h"
#include"sprite.h"
#include"BackGround.h"

class Particle
{
public:

	Particle();

	unsigned int texNo;
	D3DXVECTOR2 pos;
	D3DCOLOR color;
	int lifeFrame;
	int spawnFrame;
	float scale;

	bool IsEnable();
	void SetTexture(unsigned int inputTex);
private:

};
bool Particle::IsEnable()
{
	if (lifeFrame > 0) {
		return true;
	}
	return false;
}
Particle::Particle()
{
	lifeFrame = 0;
	spawnFrame = -1;
}
void Particle::SetTexture(unsigned int inputTex)
{
	texNo = inputTex;
}





class TraceP : public Particle {
public:
	void SetPosition(unsigned int tex, D3DXVECTOR2 genePos, D3DCOLOR geneColor, int geneLife, float geneScale, float geneAngle);
	void DrawTrace();
	void UpdateTrace();
private:
	float angle;
	
};

void TraceP::SetPosition(unsigned int tex, D3DXVECTOR2 genePos, D3DCOLOR geneColor, int geneLife, float geneScale, float geneAngle)
{
	spawnFrame = GameSystem::GetFrame();
	pos = genePos;
	scale = geneScale;
	color = geneColor;
	lifeFrame = geneLife;
	angle = geneAngle;
	SetTexture(tex);
}



void TraceP::UpdateTrace() {
	

		int elapsedFrame = GameSystem::GetFrame() - spawnFrame;

		float e = elapsedFrame / (float)lifeFrame;

		if (e > 1.0f) {
			e = 1.0f;
			lifeFrame = 0;
			spawnFrame = -1;
			return;
		}

		lifeFrame -= 1;
		if (lifeFrame == 0) {
			pos = { 0.0f,0.0f };
		}
		scale *= (1.0f-e);
		//scale *= sinf(acosf(1.0f - e));

		D3DXCOLOR tempColor = color;
		tempColor.a = 1.0f - e;
		color = tempColor;

}
void TraceP::DrawTrace() {

	SetColor(color);

	DrawSpriteRotCenter(
		texNo,
		pos.x, pos.y,
		0, 0,
		GetTextureWidth(texNo), GetTextureHeight(texNo),
		angle,
		0.0f, 0.0f,
		scale,
		scale);

	SetColor(0xFFFFFFFF);

}

class MuzzleP : public Particle {
public:
	void SetPosition(unsigned int tex, D3DXVECTOR2 genePos, D3DCOLOR geneColor, int geneLife, float geneScale, float geneAngle);
	void DrawMuzzle();
	void UpdateMuzzle();
private:
	float angle;

};

void MuzzleP::SetPosition(unsigned int tex, D3DXVECTOR2 genePos, D3DCOLOR geneColor, int geneLife, float geneScale, float geneAngle)
{
	spawnFrame = GameSystem::GetFrame();
	pos = genePos;
	scale = geneScale;
	color = geneColor;
	lifeFrame = geneLife;
	angle = geneAngle;
	SetTexture(tex);
}



void MuzzleP::UpdateMuzzle() {


	int elapsedFrame = GameSystem::GetFrame() - spawnFrame;

	float e = elapsedFrame / (float)lifeFrame;

	if (e > 1.0f) {
		e = 1.0f;
		lifeFrame = 0;
		spawnFrame = -1;
		return;
	}

	lifeFrame -= 1;
	//scale *= (1.0f-e);
	//scale *= sinf(acosf(1.0f - e));

	D3DXCOLOR tempColor = color;
	tempColor.a = 1.0f - e;
	tempColor.r = 1.0f - e;
	color = tempColor;

}
void MuzzleP::DrawMuzzle() {

	SetColor(color);

	DrawSpriteRotPlg(
		texNo,
		pos.x-512*0.5f, pos.y-512,
		0, 0,
		512, 512,
		angle,
		0.5f, 1.0f,
		scale,
		scale);

	SetColor(0xFFFFFFFF);

}



class DustP : public Particle {
public:

	void SetPosition(unsigned int inputTexNo, D3DXVECTOR2 playPos, float playScale);
	void DrawDust();
	void UpdateDust();

private:

	float angle;
	float random;

};

void DustP::SetPosition(unsigned int inputTexNo, D3DXVECTOR2 playPos, float playScale)
{
	random = (GameSystem::RandInt(0, 9) * 0.1f);
	pos = playPos;
	color = D3DCOLOR_RGBA(255, 128, 128, 255);
	scale = 0.0f;
	lifeFrame = 128;
	SetTexture(inputTexNo);
}

void DustP::UpdateDust()
{
	if (IsEnable()) {
		lifeFrame -= 1;
		float scroll = GetScrollSpeed();
		pos.x -= GameSystem::RandFloat(scroll - 1.0f, scroll + 1.0f);

		if (lifeFrame > 100) {
			scale = GameSystem::Lerp(scale, 0.3f, 0.2f);
		}
		else {
			scale = GameSystem::Lerp(scale, 0.0f, 0.1f);
		}

		angle += random;

	}
}

void DustP::DrawDust()
{
	SetColor(color);
	DrawSpriteRotPlg(
		texNo,
		(pos.x-(512*0.5f)), (pos.y-(512*0.5f)),
		0, 0,
		512, 512,
		angle,
		0.5f, 0.5f,
		(scale*0.5f),
		(scale*0.5f));
	SetColor(0xFFFFFFFF);
}

class LaserP :public Particle {
public:

	void SetPosition(unsigned int inputTexNo, D3DXVECTOR2 playPos, D3DCOLOR setColor, float playScale);
	void DrawLaser();
	void UpdateLaser();

};


void LaserP::SetPosition(unsigned int inputTexNo, D3DXVECTOR2 playPos, D3DCOLOR setColor, float playScale)
{
	pos = playPos;
	color = setColor;
	scale = playScale;
	lifeFrame = 10;
	spawnFrame = GameSystem::GetFrame();
	SetTexture(inputTexNo);

}

void LaserP::DrawLaser()
{
	SetColor(color);
	DrawSpriteRotPlg(
		texNo,
		(pos.x - (80 * 0.5f)), (pos.y - (80 * 0.5f)),
		0, 0,
		80, 80,
		0,
		0.5f, 0.5f,
		scale * 1.0f, scale * 1.0f);
	SetColor(0xFFFFFFFF);

}

void LaserP::UpdateLaser()
{
	int elapsedFrame = GameSystem::GetFrame() - spawnFrame;

	float e = elapsedFrame / (float)lifeFrame;

	if (e > 1.0f) {
		e = 1.0f;
		lifeFrame = 0;
		spawnFrame = -1;
		return;
	}

	lifeFrame -= 1;
	if (lifeFrame == 0) {
		pos = { 0.0f,0.0f };
	}
	scale = scale*(1.0f - e);
}


unsigned int dustTexNo[4];
unsigned int muzzleTexNo;
unsigned int traceTexNo;
unsigned int laserTexNo;
TraceP actTrace[PARTICLE_MAX];
MuzzleP actMuzzle[PARTICLE_MAX];
DustP actDust[PARTICLE_MAX];
LaserP actLaser[PARTICLE_MAX];

void InitParticle() {
	laserTexNo = TextureSetLoadFile("asset/texture/effect000.jpg",80,80);
	muzzleTexNo = TextureSetLoadFile("asset/texture/muzzle_05.png", 512, 512);
	traceTexNo = TextureSetLoadFile("asset/texture/trace_05_rotated.png", 512, 512);
	dustTexNo[0] = TextureSetLoadFile("asset/texture/smoke_01.png", 512, 512);
	dustTexNo[1] = TextureSetLoadFile("asset/texture/smoke_02.png", 512, 512);
	dustTexNo[2] = TextureSetLoadFile("asset/texture/smoke_04.png", 512, 512);
	dustTexNo[3] = TextureSetLoadFile("asset/texture/smoke_05.png", 512, 512);
}
void UninitParticle() {
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		actTrace[i].lifeFrame = 0;
		actMuzzle[i].lifeFrame = 0;
		actDust[i].lifeFrame = 0;

	}
}
void UpdateParticle() {	
	UpdateTrace();
	UpdateMuzzle();
	UpdateLaser();
	UpdateDust();
}

void DrawParticle() {

	StartParticle();
	DrawTrace();
	DrawMuzzle();
	DrawLaser();
	DrawDust();

	EndParticle();
}

void SetParticle(int genre, D3DXVECTOR2 genePos, D3DCOLOR color, int lifeFrame, float scale, float angle){
	switch (genre) {
	case P_Trace: {
		for (int i = 0; i < PARTICLE_MAX; i++) {
			if (!actTrace[i].IsEnable()) {
				actTrace[i].SetPosition(traceTexNo, genePos, color, lifeFrame, scale, angle);
				break;
			}
		}
	}break;
	case P_Muzzle: {
		for (int i = 0; i < PARTICLE_MAX; i++) {
			if (!actMuzzle[i].IsEnable()) {
				actMuzzle[i].SetPosition(muzzleTexNo, genePos, color, lifeFrame, scale, angle);
				break;
			}
		}
	}break;
	case P_Dust: {
		for (int i = 0; i < PARTICLE_MAX; i++) {
			if (!actDust[i].IsEnable()) {
				actDust[i].SetPosition(dustTexNo[GameSystem::RandInt(0,3)], genePos,scale);
				break;
			}
		}
	}break;
	case P_Laser: {
		for (int i = 0; i < PARTICLE_MAX; i++) {
			if (!actLaser[i].IsEnable()) {
				actLaser[i].SetPosition(laserTexNo, genePos,color, scale);
				break;
			}
		}
	}break;

	}

}

void UpdateTrace() {
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!actTrace[i].IsEnable()) {
			continue;
		}
		actTrace[i].UpdateTrace();
	}

}
void DrawTrace() {
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!actTrace[i].IsEnable()) {
			continue;
		}
		actTrace[i].DrawTrace();
	}

}

void UpdateMuzzle() {
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!actMuzzle[i].IsEnable()) {
			continue;
		}
		actMuzzle[i].UpdateMuzzle();
	}

}
void DrawMuzzle() {
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!actMuzzle[i].IsEnable()) {
			continue;
		}
		actMuzzle[i].DrawMuzzle();
	}

}

void UpdateDust() {
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!actDust[i].IsEnable()) {
			continue;
		}
		actDust[i].UpdateDust();
	}
}
void DrawDust() {
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!actDust[i].IsEnable()) {
			continue;
		}
		actDust[i].DrawDust();
	}
}

void UpdateLaser() {
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!actLaser[i].IsEnable()) {
			continue;
		}
		actLaser[i].UpdateLaser();
	}

}
void DrawLaser() {
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (!actLaser[i].IsEnable()) {
			continue;
		}
		actLaser[i].DrawLaser();
	}

}
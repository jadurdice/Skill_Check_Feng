#include"Game.h"
#include"Particle.h"
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include"EnemySpawner.h"
#include"PhaseManeger.h"
#include"score.h"
#include"BackGround.h"
#include"Item.h"
#include"Effect.h"
#include"continue.h"
#include"sound.h"
#include"Debug.h"
#include"Fade.h"

#include <random>

using namespace std;

namespace GameSystem
{
	static int frameCnt;

	int GetFrame() {
		return frameCnt;
	}

	bool isOutGameZone(float x, float y) {
		if (x < BORDERLEFT - 75.0f ||
			x > BORDERRIGHT + 75.0f ||
			y < BORDERUP - 75.0f ||
			y > BORDERDOWN + 75.0f) {
			return true;
		}
		return false;
	}

	float Lerp(float a, float b, float t) {
		if (t <= 0) {
			return a;
		}
		if (t >= 1) {
			return b;
		}
		return a + t * (b - a);
	}

	float RelDegree(D3DXVECTOR2 a, D3DXVECTOR2 b) {
		float radian = (float)atan2(b.y - a.y, b.x - a.x);
		return RADIAN_TO_DEGREE(radian);
	}

	std::random_device rd;
	std::default_random_engine gen = std::default_random_engine(rd());

	int RandInt(int min, int max) {
		std::uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}

	float RandFloat(float min, float max) {
		std::uniform_real_distribution<float> dis(min, max);
		return dis(gen);
	}

	static int shakeCnt = 0;
	static float shakeVelocity = 0.0f;
	D3DXVECTOR2 shakeNow;

	void ShakeStart(int frame, float force) {
		shakeCnt = frame;
		shakeVelocity = force;
	}

	void ShakeUpdate() {
		if (shakeCnt == 0) {
			return;
		}
		shakeCnt -= 1;
		int shakeAngle = RandInt(0, 359);


		shakeNow.x = shakeVelocity * cosf(DEGREE_TO_RADIAN(shakeAngle));
		shakeNow.y = shakeVelocity * sinf(DEGREE_TO_RADIAN(shakeAngle));
	}

	D3DXVECTOR2 GetShakeForce() {
		if (shakeCnt == 0) {
			return { 0.0f,0.0f };
		}
		return shakeNow;
	}


	float SqrMagnitude(float x, float y)
	{
		return (x*x + y * y);
	}

	void Normalize(float &x, float &y) {
		float magni = pow(GameSystem::SqrMagnitude(x, y), 0.5f);

		x = x / magni;
		y = y / magni;
	}



}




void GameInit() {

	FrontInit();
	BackInit();
	InitUI();
	InitParticle();
	InitPhase(GameSystem::GetFrame());
	InitEffect();
	InitPlayer();
	InitItem();
	InitConti();
	InitBullet();
	InitEnemy();
	PlaySound(B_STAGEONE);
	SetScrollSpeed(10.0f);
	SetFade(60, D3DCOLOR_RGBA(0, 0, 0, 0), false);


}
void GameUnInit() {
	UninitEnemy();
	UninitBullet();
	UnInitEnemySpawner();
	UninitEffect();
	UninitParticle();
	UninitItem();
	UninitUI();
	UninitEffect();
	StopSound(B_STAGEONE);
	StopSound(B_STAGEONE);
}
void GameUpdate() {

	GameSystem::frameCnt = GetFrame();
	GameSystem::ShakeUpdate();
	BackUpdate();
	UpdateUI();
	UpdateItem();
	UpdateConti();
	UpdateEnemySpawner();
	UpdatePlayer();

	UpdateEffect();
	UpdateEnemy();
	UpdateBullet();
	UpdateParticle();


	FrontUpdate();
	UpdatePhase();

}

void GameDraw() {
	BegineDebug();


	BackDraw();

	DrawItem();
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
	DrawEffect();

	DrawParticle();
	FrontDraw();



	DrawUI();
	DrawConti();
	DebugFont_Draw(10.0f, SCREEN_HEIGHT*0.9f, "%d", GetPhaseNow());
	DebugFont_Draw(10.0f, SCREEN_HEIGHT*0.95f, "%d", GetPhaseCnt());

	EndDebug();
}

SceneProc SetupGameScene()
{
	SceneProc proc = {
	S_Game,
	"Game",
	GameInit,
	GameUnInit,
	GameUpdate,
	GameDraw };
	return proc;
};
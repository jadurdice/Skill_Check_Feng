#include"Game.h"
#include"KeyMap.h"
#include"main.h"
#include"Player.h"
#include"StageManeger.h"
#include"PauseMenu.h"
#include"complex"
#include"Fade.h"
#include"TutorManeger.h"
#include"Enemy.h"
#include"Effect.h"
#include"BackGround.h"
#include"sound.h"

static nn::util::TinyMt gameRG;

namespace GameSystem
{
	static int frameCnt;
	static int shakeCnt = 0;

	void ShakeStart(int force) {
		StartVibration();
		shakeCnt = force;
	}
	int GetShakeForce() {
		if (GetSceneIndex() == S_Title) {
			shakeCnt = 0;
			return 0;
		}

		if (shakeCnt == 0) {
			return 0;
		}
		return RandInt(-1*shakeCnt,shakeCnt);
	}

	int GetFrame() {
		return frameCnt;
	}


	float SqrMagnitude(float x,float y)
	{
		return (x*x + y*y);
	}

	void Normalize(float &x, float &y) {
		float magni = pow(GameSystem::SqrMagnitude(x,y),0.5f);
	
		x = x / magni;
		y = y / magni;
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

	Float2 LerpFloat2(Float2 a, Float2 b, float t)
	{
		if (t <= 0) {
			return a;
		}
		if (t >= 1) {
			return b;
		}
		return MakeFloat2(
			a.x + t * (b.x - a.x),
			a.y + t * (b.y - a.y));
	}

	int RandInt(int min,int max) {
		int rand = min+((frameCnt + gameRG.GenerateRandomU32()) % max);
		return rand;
	}

}

static bool isTutor = false;

void GameInit(){
	gameRG.Initialize(GetFrame());

	if (isNowTutor()) {
		PlayBGM(B_TUTOR);
	}
	else {
		PlayBGM(B_PLAY);
	}
	SetVolumeBGM(1.0f, 0);


	InitInput();
	InitBG();
	InitPause();
	InitStageMap(S_Game);
	InitFade();
	InitPlayer(S_Game);
	InitTutor();

	InitEnemy();

}
void GameUnInit() {
	UninitStageMap();
	UninitTutor();
	UninitBG();
	UninitEnemy();
	UninitPlayer();

}
void GameUpdate() {
	GameSystem::frameCnt = GetFrame();
	if (GameSystem::shakeCnt > 0) {
		GameSystem::shakeCnt -= 1;
	}


	InputExchange();

	
	if (!GetPause()) {
		UpdateBG();
		UpdateStageMap();
		UpdateFade();
		UpdatePlayer();
		UpdateEnemy();
		UpdateEffect();
	}
	UpdatePause();
	UpdateTutor();

	UpdatePrevInputs();
}
	
void GameDraw() {
	DrawBG();
	DrawStageMap();
	DrawFade();
	DrawEnemy();
	DrawPlayer();
	DrawEffect();
	DrawPause();
	DrawTutor();

}

void SetTutor() {
	isTutor = !isTutor;
}

bool isNowTutor() {
	return isTutor;
}

void ClearGameProgress() {
	ResetPlayer();
	ResetStage();
	ResetFrame();
}

SceneProc SetupGameScene(void) {
	SceneProc proc = {
		S_Game,
		"Game",
		GameInit,
		GameUnInit,
		GameUpdate,
		GameDraw
	};
	return proc;
}
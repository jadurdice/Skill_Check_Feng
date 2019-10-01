#pragma once

#include <nn/util/util_TinyMt.h>
#include <nn/nn_BitTypes.h>
#include"SenceManeger.h"
#include"system.h"



namespace GameSystem
{
	void ShakeStart(int force);	
	int GetShakeForce();

	int GetFrame();
	float Lerp(float a, float b, float t);
	Float2 LerpFloat2(Float2 a, Float2 b, float t);

	float SqrMagnitude(float x,float y);
	void Normalize(float &x,float &y);

	int RandInt(int min, int max);

}


#define SCREEN_WIDTH	(1960)				//スクリーン幅
#define SCREEN_HEIGHT	(1080)				//スクリーン高さ

#define DRAG			(0.7f)
#define	GRV				(20.0f)
#define DELTATIME		(0.2f)

#define BORNPOS			(MakeFloat2(956.0f,614.0f))

#define DEGREE_TO_RADIAN(deg)	(((deg)*(3.14159))/180)

#define MAX(a,b)		{a>b?a:b}
#define MIN(a,b)		{a>b?b:a}

void GameInit();
void GameUnInit();
void GameUpdate();
void GameDraw();

void SetTutor();

bool isNowTutor();

void ClearGameProgress();

SceneProc SetupGameScene(void);
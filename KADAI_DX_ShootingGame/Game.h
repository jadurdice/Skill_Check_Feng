#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include"SceneManeger.h"


namespace GameSystem
{
	int GetFrame();
	bool isOutGameZone(float x, float y);
	float Lerp(float a, float b, float t);
	float RelDegree(D3DXVECTOR2 a, D3DXVECTOR2 b);

	int RandInt(int min, int max);
	float RandFloat(float min, float max);

	void ShakeStart(int frame, float force);
	void ShakeUpdate();
	D3DXVECTOR2 GetShakeForce();
	float SqrMagnitude(float x, float y);
	void Normalize(float &x, float &y);


}

#define PLR	(1<<0)
#define ENM	(1<<1)

#define BORDERLEFT	(0.0f)
#define BORDERRIGHT	(SCREEN_WIDTH-25.0f)
#define BORDERUP	(0.1f*SCREEN_HEIGHT)
#define BORDERDOWN	(SCREEN_HEIGHT-25.0f)

void GameInit();
void GameUnInit();
void GameUpdate();
void GameDraw();
SceneProc SetupGameScene();


#endif
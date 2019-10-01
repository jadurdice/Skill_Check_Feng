#include "Title.h"
#include"SenceManeger.h"
#include"Player.h"
#include"StageManeger.h"
#include"KeyMap.h"
#include"Fade.h"
#include"Logo.h"
#include"sound.h"
#include"BackGround.h"

void InitTitle()
{
	InitInput();
	InitBG();
	InitPlayer(S_Title);
	InitStageMap(S_Title);
	InitLogo();
	InitFade();
	PlayBGM(B_TITLE);
}

void UninitTitle()
{
	UninitBG();
	UninitPlayer();
	UninitStageMap();
	UninitLogo();
	StopBGM(5);
}

void UpdateTitle()
{
	InputExchange();
	UpdateBG();
	UpdatePlayer();
	UpdateStageMap();
	UpdateFade();
	UpdateLogo();
	UpdatePrevInputs();
}

void DrawTitle()
{
	DrawBG();
	DrawStageMap();
	DrawFade();
	DrawLogo();
	DrawPlayer();

}

SceneProc SetupTitleScene() {
	SceneProc proc = {
		S_Title,
		"Title",
		InitTitle,
		UninitTitle,
		UpdateTitle,
		DrawTitle,
	};
	return proc;
}
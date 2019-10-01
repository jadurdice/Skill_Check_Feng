#include"GameOver.h"
#include"Player.h"
#include"Game.h"
#include"KeyMap.h"
#include"texture.h"
#include"main.h"
#include"sprite.h"
#include"Fade.h"
#include"sound.h"

unsigned int capitalTexNo;
int goCursor;
Float2 floatingPos;
bool isCenter;
int floatingFactor;

float fadethis;
float fadeGOFactor;

void InitGO() {
	capitalTexNo = LoadTexture("rom:/logo.tga");
	InitPlayer(S_GameOver);
	floatingPos = { SCREEN_WIDTH*0.5f,SCREEN_HEIGHT*0.4f };
	PlayBGM(B_GAMEOVER);
	goCursor = -1;
}
void UninitGO() {
	UnloadTexture(capitalTexNo);
	UninitPlayer();
	ClearGameProgress();
	StopBGM(5);
	if (goCursor == 0) {
		
	}
}
void UpdateGO() {

	InputExchange();

	Float2 showPos;
	if (!isCenter) {
		if (GetActionPlayer()->GetPlayerPos().x > 0.45f*SCREEN_WIDTH &&GetActionPlayer()->GetPlayerPos().x < 0.55f*SCREEN_WIDTH) {
			isCenter = true;
		}
	}
	else {
		floatingPos = MakeFloat2(SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.5f + SCREEN_HEIGHT * 0.1f*sinf(DEGREE_TO_RADIAN(floatingFactor)));
		floatingFactor += 1;
	}

	if (goCursor == 0) {
		floatingPos.x = SCREEN_WIDTH * 0.25f + 1.5f*128.0f;
	}
	if(goCursor == 1) {
		floatingPos.x = SCREEN_WIDTH * 0.75f -  128;
	}

	showPos = GameSystem::LerpFloat2(GetActionPlayer()->GetPlayerPos(), floatingPos,DELTATIME);
	GetActionPlayer()->SetPlayerPos(showPos);
	UpdatePlayer();
	InputGO();
	UpdatePrevInputs();
}
void DrawGO() {
	DrawFade();
	DrawPlayer();
	if (isCenter) {
		SetColor(255, 255, 255, MIN(floatingFactor, 255));

		DrawSpriteUV(capitalTexNo, SCREEN_WIDTH*0.5f-3*192+64, SCREEN_HEIGHT*0.2f, 0.0f, 4.0f*0.125f, 0.125f*6.0f, 0.125f, 6 * 192, 192);

		DrawSpriteUV(capitalTexNo, SCREEN_WIDTH*0.25f, SCREEN_HEIGHT*0.7f, 0.0f, 5.0f*0.125f, 0.125f*3.0f, 0.125f, 3 * 128, 128);
		DrawSpriteUV(capitalTexNo, SCREEN_WIDTH*0.75f-2*128, SCREEN_HEIGHT*0.7f, 3.0f*0.125f, 5.0f*0.125f, 0.125f*2.0f, 0.125f, 2 * 128, 128);


		SetColor(255, 255, 255, 255);
	}
}

void StartFade() {

}

void InputGO() {


	if (Pressed(K_Left)) {
		if (goCursor == -1) {
			goCursor = 0;
		}
		else {
			goCursor == 0 ? goCursor = 1 : goCursor = 0;
		}
	}
	if (Pressed(K_Right)) {
		if (goCursor == -1) {
			goCursor = 1;
		}
		else {
			goCursor == 0 ? goCursor = 1 : goCursor = 0;
		}
	}
	if (KeyState(K_Attack)) {
		SceneChange(goCursor == 0?S_Game:S_Title);
	}
}

SceneProc SetupGameOverScene() {

	SceneProc proc = {
	S_GameOver,
	"GameOver",
	InitGO,
	UninitGO,
	UpdateGO,
	DrawGO};

	return proc;
}
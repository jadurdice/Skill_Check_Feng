#include"TutorManeger.h"
#include"StageManeger.h"
#include"Game.h"
#include"sprite.h"

unsigned int fingerTexNo;
int tutorProcess;
Float2 fingerUV;
Float2 fingerPos;
Float2 fingerOldPos;
Float2 fingerShow;

void InitTutor() {
	if (!isNowTutor()) {
		return;
	}
	tutorProcess = 0;
	fingerTexNo = GetMapTexNo();
	fingerOldPos = { -0.5f*SCREEN_WIDTH,-0.5f*SCREEN_HEIGHT };
	fingerPos = fingerOldPos;
	fingerUV = { 6.0f*0.125f, 2.0f*0.125f };
}
void UninitTutor() {
	tutorProcess = 0;
}
void UpdateTutor() {
	if (!isNowTutor()) {
		return;
	}
	fingerOldPos = GameSystem::LerpFloat2(fingerOldPos,fingerPos,DELTATIME);
	fingerShow = MakeFloat2(
		fingerOldPos.x + 30.0f*cosf(5.0f*DEGREE_TO_RADIAN(GameSystem::GetFrame())),
		fingerOldPos.y + 30.0f*sinf(5.0f*DEGREE_TO_RADIAN(GameSystem::GetFrame())));
}
void DrawTutor() {
	if (!isNowTutor()) {
		return;
	}
	DrawSpriteUV(fingerTexNo, fingerShow.x, fingerShow.y, fingerUV.x,fingerUV.y, 0.125f, 0.125f, 128.0f, 128.0f);
}
void SetTutorCnt(int value)
{
	tutorProcess = value;

	switch (tutorProcess)
	{
	case 0:
		fingerPos = MakeFloat2( -0.5f*SCREEN_WIDTH,-0.5f*SCREEN_HEIGHT );
		break;
	case 1:
		fingerPos = MakeFloat2( SCREEN_WIDTH*0.5f - 512.0f, SCREEN_HEIGHT*0.5f - 384.0f ); break;
	case 2:
		fingerPos = MakeFloat2( (0.5f*SCREEN_WIDTH + 7.0f*64.0f), (0.15f*SCREEN_HEIGHT) ); break;
	case 3:
		fingerPos = MakeFloat2( (0.5f*SCREEN_WIDTH + 7.0f*64.0f), ((0.9f*SCREEN_HEIGHT)) ); break;
	case 4:
		fingerPos = MakeFloat2( SCREEN_WIDTH*0.5f - 512.0f, SCREEN_HEIGHT*0.5f - 384.0f ); break;
	case 5:
		fingerUV = MakeFloat2( 7.0f*0.125f, 2.0f*0.125f ); break;
	case 6:
		fingerPos = MakeFloat2( -0.5f*SCREEN_WIDTH,-0.5f*SCREEN_HEIGHT );
		SetTutor(); break;
	case 7:
		fingerPos = MakeFloat2(1040.0f,SCREEN_HEIGHT*0.2f );
		break;
	}
}

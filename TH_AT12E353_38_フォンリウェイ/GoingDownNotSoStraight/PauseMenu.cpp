#include"PauseMenu.h"
#include"KeyMap.h"
#include"sprite.h"
#include"Game.h"
#include"StageManeger.h"
#include"MapBank.h"
#include"Player.h"
#include"texture.h"
#include"TutorManeger.h"
#include"complex"
#include"sound.h"

bool isPause;
float pauseFactor;
MapBluePrint nowMap[9];
Float2 mapPos;
Float2 mapOldPos;
Float2 mapSize;
Float2 mapOldSize;

int cursor;
int lastCursor;
int progress;
Float2 curPos;
Float2 curOldPos;
Float2 curSize;
Float2 curOldSize;


int placeFactor;

int selectedRoom;
int placeRoom;
int roomInPack[11];

unsigned int buttonTexNo;

void InitMap() {
	for (int i = 0; i < 9; i++)
	{
		nowMap[i] = *GetNowRoom(i);
	}

	mapSize = MakeFloat2(48.0f, 48.0f);
	mapPos = MakeFloat2(SCREEN_WIDTH - 4 * mapSize.x, mapSize.y);
	mapOldPos = mapPos;

};

void UpdateMap() {
	if (GetPlayerRoom() == 6 && isNowTutor()&& GetSwapCnt() == 1.0f) {
		if (GetActionPlayer()->GetPlayerPos().x > SCREEN_WIDTH*0.3f&&
			GetActionPlayer()->GetPlayerPos().x < SCREEN_WIDTH*0.7f) {
			mapSize = MakeFloat2(80.0f, 80.0f);
			mapPos = MakeFloat2(SCREEN_WIDTH*0.5f - 2.0f * mapSize.x, SCREEN_HEIGHT*0.2f);
			SetTutorCnt(7);
		}
		else {
			SetTutorCnt(0);
		}
	}

	mapOldPos = MakeFloat2(
		GameSystem::Lerp(mapOldPos.x, mapPos.x, DELTATIME),
		GameSystem::Lerp(mapOldPos.y, mapPos.y, DELTATIME)
	);
	mapOldSize = MakeFloat2(
		GameSystem::Lerp(mapOldSize.x, mapSize.x, DELTATIME),
		GameSystem::Lerp(mapOldSize.y, mapSize.y, DELTATIME)
	);

	for (int i = 0; i < 9; i++)
	{
		nowMap[i] = *GetNowRoom(i);
	}

}

void DrawMap() {
	//地図
	for (int i = 0; i < 9; i++)
	{
		float u, v, posX, posY;

		u = 0.0f; v = 0.0f;

		posX = i % 3 * mapOldSize.x;
		posY = i / 3 * mapOldSize.y;

		RoomUVSelect(u, v, nowMap[i].roomTag);

		SetColor(255, 255, 255, (1 + pauseFactor) * 127);

		if (GetPlayerRoom() == 6 && isNowTutor() && GetSwapCnt() == 1.0f) {
			if (GetActionPlayer()->GetPlayerPos().x > SCREEN_WIDTH*0.3f&&
				GetActionPlayer()->GetPlayerPos().x < SCREEN_WIDTH*0.7f) {
				SetColor(255, 255, 255, 255);
			}
		}


		DrawSpriteUV(GetMapTexNo(), mapOldPos.x + posX, mapOldPos.y + posY, u, v, 0.125f, 0.125f, mapOldSize.x, mapOldSize.y);
		SetColor(255, 255, 255, 255);
	}

	//プレイヤー
	int nowRoom = GetPlayerRoom();

	float posX, posY;

	posX = mapOldSize.x*(nowRoom % 3);
	posY = mapOldSize.y*(nowRoom / 3);

	SetColor(255, 255, 255, 255);
	DrawSpriteUV(GetMapTexNo(), mapOldPos.x + posX, mapOldPos.y + posY, 0.125f * 5, 0.125f * 7, 0.125f, 0.125f, mapOldSize.x, mapOldSize.y);

	//設置アニメ

	if (placeFactor <= 0) {
		return;
	}

	float temp = (200 - placeFactor) / 100.0f;

	float u, v;
	RoomUVSelect(u, v, placeRoom + 1);

	if (temp > 1.0f &&temp < 1.33f) {

		int temp = (180 + (5.4f*(placeFactor - 100)));


		posX = selectedRoom % 3 * mapOldSize.x - 0.5f* (sinf(DEGREE_TO_RADIAN(temp)) * 36.0f);
		posY = selectedRoom / 3 * mapOldSize.y - 0.5* (sinf(DEGREE_TO_RADIAN(temp)) * 36.0f);

		DrawSpriteUV(GetMapTexNo(), mapOldPos.x + posX, mapOldPos.y + posY,
			u, v,
			0.125f, 0.125f,
			256.0f + (sinf(DEGREE_TO_RADIAN(temp)) * 36.0f), 256.0f + (sinf(DEGREE_TO_RADIAN(temp)))*36.0f);

	}
	else {

		if (temp > 1.0f) {
			temp = 1.0f;
		}


		posX = selectedRoom % 3 * mapOldSize.x;
		posY = selectedRoom / 3 * mapOldSize.y;


		float w, h;
		w = 0.125f*temp;
		h = 256.0f*temp;

		DrawSpriteUV(GetMapTexNo(), mapOldPos.x + posX, mapOldPos.y + posY,
			u, v,
			w, 0.125f,
			h, 256.0f);
	}

}

void SetCursorPos(Float2 pos) {
	curPos = pos;
}

void SetCursorSize(Float2 size) {
	curSize = size;
}

void InitCursor()
{
	curSize = MakeFloat2(256.0f, 256.0f);
	curPos = MakeFloat2(-1.5f* curSize.x, SCREEN_HEIGHT*0.5f - 1.5f*curSize.y);
}

void UpdateCursor()
{

	curOldPos = MakeFloat2(
		GameSystem::Lerp(curOldPos.x, curPos.x, DELTATIME),
		GameSystem::Lerp(curOldPos.y, curPos.y, DELTATIME)
	);
	curOldSize = MakeFloat2(
		GameSystem::Lerp(curOldSize.x, curSize.x, DELTATIME),
		GameSystem::Lerp(curOldSize.y, curSize.y, DELTATIME)
	);


	if (pauseFactor < 1.0f || !isPause) {
		return;
	}

	float posX, posY;

	switch (progress) {
	case RoomSelect: {

		posX = curOldSize.x*(cursor % 3);
		posY = curOldSize.y*(cursor / 3);

		SetCursorSize(MakeFloat2(256.0f, 256.0f));
		SetCursorPos(MakeFloat2(mapOldPos.x + posX, mapOldPos.y + posY));

	}break;
	case RoomPick: {

		if (cursor < 5) {
			posX = 0.0f;
			posY = curOldSize.y*(2 * (cursor % 5));
		}
		else {
			posX = PACKSIZE * 5.0f;
			posY = curOldSize.y*(2 * ((cursor - 5) % 6));
		}


		SetCursorSize(MakeFloat2(PACKSIZE*4.0f, PACKSIZE*1.0f));
		SetCursorPos(MakeFloat2(PACKX + posX, PACKY + posY));

	}break;
	case Comfirm: {


		posX = cursor * PACKSIZE * 5.0f;
		posY = 0.0f;
		SetCursorSize(MakeFloat2(PACKSIZE*4.0f, PACKSIZE*1.0f));
		SetCursorPos(MakeFloat2(PACKX + posX, COMFIRMY));

	}break;
	}


}

void DrawCursor()
{
	int factor = GameSystem::GetFrame();

	float bump = 10.0f * (1.0f + sinf(5 * DEGREE_TO_RADIAN(factor)));

	if (progress > RoomSelect) {

		float posX, posY;

		posX = 256.0f*(selectedRoom % 3) - 0.5f*bump;
		posY = 256.0f*(selectedRoom / 3) - 0.5f*bump;

		DrawSpriteUV(GetMapTexNo(), mapOldPos.x + posX, mapOldPos.y + posY, 0.0f, 0.125f * 6, 0.125f, 0.125f, 256.0f + bump, 256.0f + bump);
	}

	DrawSpriteUV(GetMapTexNo(), curOldPos.x - 0.5f*bump, curOldPos.y - 0.5f*bump, 0.0f, 0.125f * 6, 0.125f, 0.125f, curOldSize.x + bump, curOldSize.y + bump);


}


void DrawPack() {
	SetColor(255, 255, 255, (pauseFactor) * 255);

	DrawSpriteUV(buttonTexNo, SCREEN_WIDTH*0.5f - 1.5f * mapSize.x-3*128, COMFIRMY-20.0f , 0.0f, 3.0f*0.125f, 0.125f*6.0f, 0.125f, 6 * 128, 128);

	for (int i = 0; i < 11; i++)
	{
		float u, v, posX, posY;

		if (i < 5) {
			posX = 0.0f;
			posY = i * (2.0f * PACKSIZE);
		}
		else {
			posX = 5.0f* PACKSIZE;
			posY = (i - 5) * (2.0f * PACKSIZE);
		}

		RoomUVSelect(u, v, i + 1);


		DrawSpriteUV(GetMapTexNo(), PACKX + posX, PACKY + posY, u, v, 0.125f, 0.125f, PACKSIZE, PACKSIZE);

		if (roomInPack[i] == 0) {
			SetColor(255, 70, 70, (pauseFactor) * 255);
		}

		DrawSpriteUV(GetMapTexNo(), PACKX + posX + 1.6f*PACKSIZE, PACKY + posY + 0.1f*PACKSIZE, 7.5f*0.125f, 5.5f*0.125f, 0.5f * 0.125f, 0.5f*0.125f, 0.8f*PACKSIZE, 0.8f*PACKSIZE);

		DrawSpriteUV(GetMapTexNo(), PACKX + posX + 3.0f*PACKSIZE, PACKY + posY, NUMU(roomInPack[i]), NUMV, 0.5f*0.125f, 0.5f*0.125f, PACKSIZE, PACKSIZE);

		SetColor(255, 255, 255, (pauseFactor) * 255);

	}

	float u, v;
	u = 3.0f * 0.125f;
	v = 5.5f*0.125f;
	DrawSpriteUV(GetMapTexNo(), PACKX - 0.5f*PACKSIZE, PACKY - 1.5f*PACKSIZE, u, v, 4.5f * 0.125f, 0.5f*0.125f, 9.0f*PACKSIZE, PACKSIZE);



	if (progress == Comfirm) {
		u = 0.0f;
		DrawSpriteUV(GetMapTexNo(), PACKX + PACKSIZE, COMFIRMY, u, v, 0.125f, 0.5f* 0.125f, PACKSIZE*2.0f, PACKSIZE);
		u = 0.125f;
		DrawSpriteUV(GetMapTexNo(), PACKX + PACKSIZE * 5.0f, COMFIRMY, u, v, 2.0f * 0.125f, 0.5f * 0.125f, PACKSIZE*4.0f, PACKSIZE);
	}



	SetColor(255, 255, 255, 255);

}



void InitPause() {
	isPause = false;
	buttonTexNo = LoadTexture("rom:/logo.tga");
	InitMap();
	InitCursor();
}

void UpdatePause()
{
	if (Pressed(K_Map) && placeFactor == 0) {

		if (isNowTutor()) {
			if (GetAllRoomCount() == 0) {
				return;
			}
			else {
				SetTutorCnt(1);
			}
		}

		if (!GetActionPlayer()->isCollisionToOther) {
			return;
		}

		GetRoomInPack(roomInPack);
		if (isPause) {
			SetCursorPos(MakeFloat2(CURSORDEFX, curOldPos.y));
			progress = 0;
			cursor = 0;
			PlaySE(S_CLOSE);
			if (isNowTutor()) {
				SetTutorCnt(0);
			}
			SetVolumeBGM(1.0f, 15);
		}
		else {
			PlaySE(S_OPEN);
			SetVolumeBGM(0.5f, 15);

		}


		isPause = !isPause;
		//GetRoomInPack(roomInPack);

	}


	if (placeFactor > 0) {
		placeFactor -= 1;
		if (placeFactor == 100) {
			PlaySE(S_DECIDE_);
			if (isNowTutor()) {
				SetTutorCnt(5);
			}
		}
		if (placeFactor == 0) {

			NewRoom();
			SetCursorPos(MakeFloat2(CURSORDEFX, curOldPos.y));
			progress = 0;
			cursor = 0;
			if (isNowTutor()) {
				SetTutorCnt(6);
				SetCursorPos(MakeFloat2(CURSORDEFX, curOldPos.y));
				progress = 0;
				cursor = 0;
				PlaySE(S_CLOSE);
				SetVolumeBGM(1.0f, 15);
			}
		}
	}


	UpdateCursor();
	UpdateMap();
	if (!isPause) {
		pauseFactor -= PAUSESPEED;
		if (pauseFactor <= 0.0f) {
			pauseFactor = 0.0f;
		}
		mapSize = MakeFloat2(48.0f, 48.0f);
		mapPos = MakeFloat2(SCREEN_WIDTH - 4 * mapSize.x, mapSize.y);

	}
	else {
		pauseFactor += PAUSESPEED;
		if (pauseFactor >= 1.0f) {
			pauseFactor = 1.0f;
		}
		mapSize = MakeFloat2(256.0f, 256.0f);
		mapPos = MakeFloat2(SCREEN_WIDTH*0.5f - 3 * mapSize.x, SCREEN_HEIGHT*0.5f - 1.5f*mapSize.y);

		PauseInput();
	}


}

void DrawPause()
{
	SetColor(0, 0, 0, pauseFactor * 128);
	DrawSpriteUV(-1, 0.0f, 0.0f, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	SetColor(255, 255, 255, 255);

	//マップ

	DrawMap();

	//パック
	DrawPack();

	//カーソル

	DrawCursor();


	if (GetCircleCnt() == 0) {
		SetColor(255, 255, 255, 255);
		return;
	}

	float alpha = MIN(255, 255 * 2.0f*sinf(GetCircleCnt()));
	SetColor(255, 255, 255, (int)alpha);
	DrawSpriteUV(GetMapTexNo(), SCREEN_WIDTH*0.5f - 4 * 64.0f, SCREEN_HEIGHT*0.15f, 5.0f*0.125f, 5.0f*0.125f, 2.0f*0.125f, 0.5f*0.125f, 8 * 64.0f, 2 * 64.0f);
	int floorTen, floorSingle, nowFloor;

	nowFloor = GetNowFloor();

	floorTen = nowFloor / 10;
	floorSingle = nowFloor % 10;

	DrawSpriteUV(GetMapTexNo(), SCREEN_WIDTH*0.5f - 2 * 64.0f, SCREEN_HEIGHT*0.3f, NUMU(floorTen), NUMV, 0.5f*0.125f, 0.5f*0.125f, 2 * 64.0f, 2 * 64.0f);
	DrawSpriteUV(GetMapTexNo(), SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.3f, NUMU(floorSingle), NUMV, 0.5f*0.125f, 0.5f*0.125f, 2 * 64.0f, 2 * 64.0f);

	SetColor(255, 255, 255, 255);


}

void PauseInput()
{

	if (placeFactor > 0) {
		return;
	}
	switch (progress) {
	case RoomSelect: {
		if (Pressed(K_Up)) {
			PlaySE(S_CLICK);
			if (cursor - 3 >= 0) {
				cursor -= 3;
			}
			else {
				cursor += 6;
			}

		}
		if (Pressed(K_Down)) {
			PlaySE(S_CLICK);
			if (cursor + 3 < 9) {
				cursor += 3;
			}
			else {
				cursor -= 6;
			}
		}
		if (Pressed(K_Right)) {
			PlaySE(S_CLICK);
			if (cursor % 3 != 2) {
				cursor += 1;
			}
			else {
				cursor -= 2;
			}
		}
		if (Pressed(K_Left)) {
			PlaySE(S_CLICK);
			if (cursor % 3 != 0) {
				cursor -= 1;
			}
			else {
				cursor += 2;
			}
		}
		if (Pressed(K_Attack)) {

			if (isNowTutor()) {
				if (cursor != 0) {
					PlaySE(S_WRONG);
					return;
				}
				else {
					PlaySE(S_DECIDE_);
					progress += 1;
					selectedRoom = cursor;
					cursor = 0;
					SetTutorCnt(2);
					return;
				}
			}

			if (!isHerePlacable()) {
				PlaySE(S_WRONG);
			}
			else {
				PlaySE(S_DECIDE_);
				progress += 1;
				selectedRoom = cursor;
				cursor = 0;
			}
		}
		if (Pressed(K_Jump)) {

			PlaySE(S_CANCEL);
			SetCursorPos(MakeFloat2(CURSORDEFX, curOldPos.y));
			progress = 0;
			cursor = 0;

			isPause = false;
		}

	}break;
	case RoomPick: {
		if (Pressed(K_Up)) {
			PlaySE(S_CLICK);
			if (cursor < 5) {
				if (cursor == 0) {
					cursor = 4;
				}
				else {
					cursor -= 1;
				}
			}
			else {
				if (cursor == 5) {
					cursor = 10;
				}
				else {
					cursor -= 1;
				}
			}


		}
		if (Pressed(K_Down)) {
			PlaySE(S_CLICK);
			if (cursor < 5) {
				if (cursor == 4) {
					cursor = 0;
				}
				else {
					cursor += 1;
				}
			}
			else {
				if (cursor == 10) {
					cursor = 5;
				}
				else {
					cursor += 1;
				}
			}
		}
		if (Pressed(K_Right) || Pressed(K_Left)) {
			PlaySE(S_CLICK);
			if (cursor == 10) {
				cursor = 4;
			}
			else if (cursor < 5) {
				cursor += 5;
			}
			else {
				cursor -= 5;
			}
		}

		if (Pressed(K_Attack)) {

			if (isNowTutor()) {
				if (cursor != 0) {
					PlaySE(S_WRONG);
					return;
				}
				else {
					PlaySE(S_DECIDE_);
					progress += 1;
					placeRoom = cursor;
					cursor = 0;
					SetTutorCnt(3);
					return;
				}
			}

			if (roomInPack[cursor] > 0) {
				progress += 1;
				placeRoom = cursor;
				cursor = 0;
				PlaySE(S_DECIDE_);
			}
			else {
				PlaySE(S_WRONG);
			}
		}
		if (Pressed(K_Jump)) {
			PlaySE(S_CANCEL);
			progress -= 1;
			cursor = selectedRoom;
			if (isNowTutor()) {
				SetTutorCnt(1);
			}

		}

	}break;
	case Comfirm: {
		if (Pressed(K_Right) || Pressed(K_Left)) {
			PlaySE(S_CLICK);
			cursor == 0 ? cursor += 1 : cursor -= 1;
		}

		if (Pressed(K_Attack)) {
			if (cursor == 0) {
				//部屋設置する
				PlaySE(S_STRECH);
				placeFactor = 200;
				if (isNowTutor()) {
					SetTutorCnt(4);
				}


			}
			else {

				PlaySE(S_CANCEL);
				progress -= 1;
				cursor = placeRoom;
				if (isNowTutor()) {
					SetTutorCnt(2);
				}
			}

		}
		if (Pressed(K_Jump)) {
			if (isNowTutor()) {
				SetTutorCnt(2);
			}


			PlaySE(S_CANCEL);
			progress -= 1;
			cursor = placeRoom;

		}

	}break;
	}


}

void NewRoom() {

	MapBluePrint newRoom;

	newRoom = GetRoom(placeRoom);

	int nowHaveRoom = GetAllRoomCount();

	if (isNowTutor()) {
		SetBoxInRoom(newRoom);
		SetBoxInRoom(newRoom);
	}

	
	int factor = 100,temp;
	if (nowHaveRoom <= 3) {
		SetBoxInRoom(newRoom);
	}
		do
		{
			temp = GameSystem::RandInt(0, factor - 1);
			if (temp > nowHaveRoom * 3) {
				SetBoxInRoom(newRoom);
			}
			factor /= 2;
		} while (nowHaveRoom * 3 > factor);
		
	SetRoomInStage(newRoom, selectedRoom);
	SetRoomInPack(placeRoom, -1);
	GetRoomInPack(roomInPack);

	SwapRoomData();
}

bool GetPause() {
	return isPause;
}

bool isHerePlacable() {
	if (cursor == GetPlayerRoom()) {
		return false;
	}
	if (nowMap[cursor].roomTag == R_Start) {
		return false;
	}
	if(nowMap[cursor].roomTag >= R_GoalURLD&& nowMap[cursor].roomTag<= R_GoalD) {
		return false;
	}

	if (cursor % 3 != 0) {
		//checkLeft
		if (nowMap[cursor - 1].roomTag != R_Void && (nowMap[cursor - 1].roomWay & WAYRIGHT)) {
			return true;
		}
	}
	if (cursor % 3 != 2) {
		//checkRight
		if (nowMap[cursor + 1].roomTag != R_Void && (nowMap[cursor + 1].roomWay & WAYLEFT)) {
			return true;
		}
	}
	if (cursor / 3 != 0) {
		//checkUp
		if (nowMap[cursor - 3].roomTag != R_Void && (nowMap[cursor - 3].roomWay & WAYDOWN)) {
			return true;
		}
	}
	if (cursor / 3 != 2) {
		//checkDown
		if (nowMap[cursor + 3].roomTag != R_Void && (nowMap[cursor + 3].roomWay & WAYUP)) {
			return true;
		}
	}
	return false;
}

void RoomUVSelect(float&u, float&v, int standard) {
	switch (standard) {
	case	R_Void:
		u = 4.0f;
		v = 7.0f;
		break;
	case	R_URLD:
		u = 1.0f;
		v = 6.0f;
		break;
	case	R_URL:
		u = 2.0f;
		v = 6.0f;
		break;
	case	R_URD:
		u = 3.0f;
		v = 6.0f;
		break;
	case	R_RLD:
		u = 4.0f;
		v = 6.0f;
		break;
	case	R_ULD:
		u = 5.0f;
		v = 6.0f;
		break;
	case	R_UR:
		u = 6.0f;
		v = 6.0f;
		break;
	case	R_RD:
		u = 7.0f;
		v = 6.0f;
		break;
	case	R_LD:
		u = 0.0f;
		v = 7.0f;
		break;
	case	R_UL:
		u = 1.0f;
		v = 7.0f;
		break;
	case	R_UD:
		u = 2.0f;
		v = 7.0f;
		break;
	case	R_RL:
		u = 3.0f;
		v = 7.0f;
		break;
	case	R_Start:
		u = 6.0f;
		v = 7.0f;
		break;
	case	R_GoalURLD:
		u = 7.0f;
		v = 7.0f;
		break;
	case	R_GoalRLD:
		u = 0.0f;
		v = 3.0f;
		break;
	case	R_GoalULD:
		u = 1.0f;
		v = 3.0f;
		break;
	case	R_GoalURD:
		u = 2.0f;
		v = 3.0f;
		break;
	case	R_GoalURL:
		u = 3.0f;
		v = 3.0f;
		break;
	case	R_GoalUR:
		u = 4.0f;
		v = 3.0f;
		break;
	case	R_GoalRD:
		u = 5.0f;
		v = 3.0f;
		break;
	case	R_GoalLD:
		u = 6.0f;
		v = 3.0f;
		break;
	case	R_GoalUL:
		u = 7.0f;
		v = 3.0f;
		break;
	case	R_GoalUD:
		u = 1.0f;
		v = 4.0f;
		break;
	case	R_GoalRL:
		u = 2.0f;
		v = 4.0f;
		break;
	case	R_GoalU:
		u = 3.0f;
		v = 4.0f;
		break;
	case	R_GoalR:
		u = 4.0f;
		v = 4.0f;
		break;
	case	R_GoalL:
		u = 5.0f;
		v = 4.0f;
		break;
	case	R_GoalD:
		u = 6.0f;
		v = 4.0f;
		break;

	}
	u *= 0.125f;
	v *= 0.125f;

}
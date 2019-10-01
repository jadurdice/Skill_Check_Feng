#pragma once


#define PAUSESPEED	(0.1f)

#define CURSORDEFX	(-384.0f)
#define PACKX		(0.5f*SCREEN_WIDTH + 3.0f*PACKSIZE)
#define PACKY		(0.15f*SCREEN_HEIGHT)
#define PACKSIZE	(64.0f)

#define COMFIRMY	(0.9f*SCREEN_HEIGHT)

#define NUMU(a)		(0.0625f*(a))
#define NUMV		(5.0f*0.125f)

enum PauseState {
	RoomSelect,
	RoomPick,
	Comfirm,
	Place
};

void InitMap();
void UpdateMap();
void DrawMap();

void InitCursor();
void UpdateCursor();
void DrawCursor();

void InitPause();
void UpdatePause();
void DrawPause();
void PauseInput();

void NewRoom();


bool GetPause();

bool isHerePlacable();
void RoomUVSelect(float&u, float&v, int standard);
#pragma once

#include"system.h"

//マップ
//壱ルームの大きさは30*18chunk(1chunk = 64*64)

#define MAPTEXTUREPATH ("rom:/map.tga")

#define TILE_LENGTH (64)

#define CHUNK_X_MAX (32)
#define CHUNK_Y_MAX (18)

#define MAPPOINT (MakeFloat2(-0.655f*TILE_LENGTH,-0.5f*TILE_LENGTH))

#define WAYUP		(1<<0)
#define WAYRIGHT	(1<<1)
#define WAYLEFT		(1<<2)
#define WAYDOWN		(1<<3)

typedef struct {
	int chunkData[CHUNK_Y_MAX][CHUNK_X_MAX];
	int roomTag;
	char roomWay;
}MapBluePrint;

enum roomTag {
	R_Void = 0,
	R_URLD,
	R_URL,
	R_URD,
	R_RLD,
	R_ULD,
	R_UR,
	R_RD,
	R_LD,
	R_UL,
	R_UD,
	R_RL,
	R_Start,
	R_GoalURLD,
	R_GoalRLD,
	R_GoalULD,
	R_GoalURD,
	R_GoalURL,
	R_GoalUR,
	R_GoalRD,
	R_GoalLD,
	R_GoalUL,
	R_GoalUD,
	R_GoalRL,
	R_GoalU,
	R_GoalR,
	R_GoalL,
	R_GoalD,
	R_Count
};
enum MapObj
{
	Empty,
	Block,
	OneWay,
	Swap,
	NextU,
	NextD,
	StartU,
	StartD,
	Box,
	OpenedBox,
	SpikeU,
	SpikeL,
	SpikeD,
	SpikeR,
	T_Stop,
	T_A,
	T_Up,
	T_Right,
	T_Plus,
	T_Wakaba,
	T_GL,
	T_S,
	T_G

};
class TileMap
{
public:
	   


	void SetTileTex(unsigned int tex);
	void SetTile(Float2 placePos,int mapIndex);

	Float2 GetMapTileAtPoint(Float2 point);
	int GetMapTileXAtPoint(float x);
	int GetMapTileYAtPoint(float y);
	Float2 GetMapTilePosition(int tileIndexX, int tileIndexY);
	Float2 GetMapTilePosition(Float2 tileCoords);
	int GetTile(int x, int y);
	bool IsObstacle(int x, int y);
	bool IsGround(int x, int y);
	bool IsOneWayPlatform(int x, int y);
	bool IsEmpty(int x, int y);
	bool IsSwap(int x, int y);
	bool IsSpike(int x, int y);
	void ClearRoom();
	

	TileMap();

	virtual void LoadMap(MapBluePrint mapData);
	virtual void DrawMap();

	Float2 position;

	int texNo;
	int mTiles[CHUNK_Y_MAX][CHUNK_X_MAX];
};

void BluePrintClear(MapBluePrint &dirt);
void SetBoxInRoom(MapBluePrint &set);
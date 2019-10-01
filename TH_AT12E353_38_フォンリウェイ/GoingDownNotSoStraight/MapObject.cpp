#include"MapObject.h"
#include"Game.h"
#include"texture.h"
#include"sprite.h"
#include"StageManeger.h"



MapBluePrint basicMap = {{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{3,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
} };

void TileMap::SetTileTex(unsigned int tex)
{
	texNo = tex;
}

void TileMap::SetTile(Float2 placePos, int mapIndex) {

	mTiles[(int)placePos.y][(int)placePos.x] = mapIndex;
}

Float2 TileMap::GetMapTileAtPoint(Float2 point)
{
	return MakeFloat2((int)((point.x - position.x + TILE_LENGTH / 2.0f) / (float)(TILE_LENGTH)),
		(int)((point.y - position.y + TILE_LENGTH / 2.0f) / (float)(TILE_LENGTH)));
}

int TileMap::GetMapTileXAtPoint(float x)
{
	return (int)((x - position.x + TILE_LENGTH / 2.0f) / (float)(TILE_LENGTH));
}
int TileMap::GetMapTileYAtPoint(float y)
{
	return	(int)((y - position.y + TILE_LENGTH / 2.0f) / (float)(TILE_LENGTH));
}

Float2 TileMap::GetMapTilePosition(int tileIndexX, int tileIndexY)
{
	return MakeFloat2(
		(float)(tileIndexX * TILE_LENGTH) + position.x,
		(float)(tileIndexY * TILE_LENGTH) + position.y
	);
}

Float2 TileMap::GetMapTilePosition(Float2 tileCoords)
{
	return MakeFloat2(
		(float)(tileCoords.x * TILE_LENGTH) + position.x,
		(float)(tileCoords.y * TILE_LENGTH) + position.y
	);
}

int TileMap::GetTile(int x, int y)
{
	return mTiles[y][x];
}

bool TileMap::IsObstacle(int x, int y)
{
	return  (mTiles[y][x] == Block);
}

bool TileMap::IsGround(int x, int y)
{
	return (mTiles[y][x] == OneWay || mTiles[y][x] == Block);
}

bool TileMap::IsOneWayPlatform(int x, int y)
{
	return (mTiles[y][x] == OneWay);
}

bool TileMap::IsEmpty(int x, int y)
{
	return (mTiles[y][x] == Empty);
}

bool TileMap::IsSwap(int x, int y)
{
	return (mTiles[y][x] == Swap);
}

bool TileMap::IsSpike(int x, int y)
{
	return(
		(mTiles[y][x] == SpikeU) ||
		(mTiles[y][x] == SpikeR) ||
		(mTiles[y][x] == SpikeL) ||
		(mTiles[y][x] == SpikeD)
		);
}

void TileMap::ClearRoom() {
	for (int i = 0; i < CHUNK_X_MAX; i++)
	{
		for (int j = 0; j < CHUNK_Y_MAX; j++)
		{
			mTiles[i][j] = Empty;
		}
	}
}



TileMap::TileMap() {
	LoadMap(basicMap);
	position = MAPPOINT;
}
void TileMap::LoadMap(MapBluePrint mapData)
{
	for (int i = 0; i < CHUNK_Y_MAX; i++)
	{
		for (int j = 0; j < CHUNK_X_MAX; j++)
		{
			mTiles[i][j] = mapData.chunkData[i][j];
		}
	}
}

void TileMap::DrawMap() {
	float uNow = 0, vNow = 0, type = 0;
	for (int i = 0; i < CHUNK_Y_MAX; i++)
	{
		for (int j = 0; j < CHUNK_X_MAX; j++)
		{
			uNow = mTiles[i][j] * 0.125f;
			vNow = (mTiles[i][j] / 8) * 0.125f;

			if (mTiles[i][j] == T_G) {
				uNow = 7.0f*0.125f;
				vNow = 4.0f*0.125f;
			}

			DrawSpriteUV(texNo, position.x + TILE_LENGTH * j, position.y + TILE_LENGTH * i, uNow, vNow, 0.125f, 0.125f, TILE_LENGTH, TILE_LENGTH);
		}
	}

}

void BluePrintClear(MapBluePrint &dirt) {
	MapBluePrint empty = {};
	dirt = empty;
}

void SetBoxInRoom(MapBluePrint &set) {
	for (int i = 0; i < 100; i++)
	{
		int tempX = GameSystem::RandInt(6, CHUNK_X_MAX - 6);
		int tempY = GameSystem::RandInt(6, CHUNK_Y_MAX - 6);
		if (set.chunkData[tempY][tempX] == Empty && set.chunkData[tempY + 1][tempX] == Block) {
			set.chunkData[tempY][tempX] = Box;
			break;
		}
	}
}
#include"StageManeger.h"
#include"Game.h"
#include"AABB.h"
#include"complex"
#include"sound.h"

bool AABB::isOverlap(AABB other)
{
	if (abs(center.x - other.center.x) > halfScale.x + other.halfScale.x) return false;
	if (abs(center.y - other.center.y) > halfScale.y + other.halfScale.y) return false;
	return true;
}

void AABB::SetAABB(Float2 conCenter, Float2 conHalfScale)
{
	center = conCenter;
	halfScale = conHalfScale;
}

bool MovingObject::HasGround(Float2 oldPosition, Float2 position, Float2 speed, float & groundY, bool& onOneWayPlatform)
{

	Float2 oldCenter = MakeFloat2(oldPosition.x + mAABBOffset.x, oldPosition.y + mAABBOffset.y);
	Float2 center = MakeFloat2(position.x + mAABBOffset.x, position.y + mAABBOffset.y);

	Float2 oldBottomLeft = RoundFloat(MakeFloat2(oldCenter.x - mAABB.halfScale.x + 1.0f,
		oldCenter.y - mAABB.halfScale.y + 1.0f));
	Float2 newBottomLeft = RoundFloat(MakeFloat2(center.x - mAABB.halfScale.x + 1.0f,
		center.y - mAABB.halfScale.y + 1.0f));



	int endY = GetGameMap()->GetMapTileYAtPoint(newBottomLeft.y);
	int begY = MAX(GetGameMap()->GetMapTileYAtPoint(oldBottomLeft.y) - 1, endY);
	int dist = MAX((int)abs((float)endY - (float)begY), 1);

	int tileIndexX;

	for (int tileIndexY = begY; tileIndexY >= endY; --tileIndexY)
	{
		Float2 bottomLeft =
			MakeFloat2(
				GameSystem::Lerp(newBottomLeft.x, oldBottomLeft.x, abs((float)endY - (float)tileIndexY) / dist),
				GameSystem::Lerp(newBottomLeft.y, oldBottomLeft.y, abs((float)endY - (float)tileIndexY) / dist));
		Float2 bottomRight = MakeFloat2(bottomLeft.x + mAABB.halfScale.x * 2.0f - 2.0f, bottomLeft.y);

		for (Float2 checkedTile = bottomLeft; ; checkedTile.x += TILE_LENGTH)
		{
			checkedTile.x = MIN(checkedTile.x, bottomRight.x);

			tileIndexX = GetGameMap()->GetMapTileXAtPoint(checkedTile.x);

			groundY = (float)(tileIndexY * TILE_LENGTH) + (TILE_LENGTH / 2.0f) + GetGameMap()->position.y;

			{
				if (GetGameMap()->IsSpike(tileIndexX, tileIndexY)) {
					RespawnStart();
					return false;
				}
				if (GetGameMap()->IsSwap(tileIndexX, tileIndexY + 1)) {
					return SwapDetected(GoDown);
				}
				if (GetGameMap()->IsObstacle(tileIndexX, tileIndexY + 1)) {
					onOneWayPlatform = false;
					return true;
				}
				else if (GetGameMap()->IsOneWayPlatform(tileIndexX, tileIndexY + 1) &&
					abs(checkedTile.y + groundY) >= (cOneWayPlatformThreshold + oldPos.y) - position.y) {

					onOneWayPlatform = true;
				}
				if (checkedTile.x >= bottomRight.x) {
					if (GetGameMap()->IsOneWayPlatform(tileIndexX, tileIndexY + 1) && onOneWayPlatform) {
						return true;
					}
					break;
				}
			}
		}

	}

	return false;
}
bool MovingObject::HasCeiling(Float2 oldPosition, Float2 position, float & ceilingY)
{
	Float2 oldCenter = MakeFloat2(oldPosition.x + mAABBOffset.x, oldPosition.y + mAABBOffset.y);
	Float2 center = MakeFloat2(position.x + mAABBOffset.x, position.y + mAABBOffset.y);
	ceilingY = 0.0f;

	Float2 oldTopRight = RoundFloat(MakeFloat2(
		oldCenter.x + mAABB.halfScale.x - 1.0f,
		oldCenter.y - mAABB.halfScale.y - 1.0f));
	Float2 newTopRight = RoundFloat(MakeFloat2(
		center.x + mAABB.halfScale.x - 1.0f,
		center.y - mAABB.halfScale.y - 1.0f));

	int endY = GetGameMap()->GetMapTileYAtPoint(newTopRight.y);
	int begY = MIN(GetGameMap()->GetMapTileYAtPoint(oldTopRight.y) - 1, endY);
	int dist = MAX((int)abs((float)endY - (float)begY), 1);


	int tileIndexX;

	for (int tileIndexY = begY; tileIndexY < endY; ++tileIndexY)
	{
		Float2 topRight =
			MakeFloat2(
				GameSystem::Lerp(newTopRight.x, oldTopRight.x, abs((float)endY - (float)tileIndexY) / dist),
				GameSystem::Lerp(newTopRight.y, oldTopRight.y, abs((float)endY - (float)tileIndexY) / dist));
		Float2 topLeft = MakeFloat2(topRight.x + mAABB.halfScale.x * 2.0f - 2.0f, topRight.y);

		for (Float2 checkedTile = topLeft; ; checkedTile.x += TILE_LENGTH)
		{
			checkedTile.x = MIN(checkedTile.x, topRight.x);

			tileIndexX = GetGameMap()->GetMapTileXAtPoint(checkedTile.x);
			if (GetGameMap()->IsSpike(tileIndexX, tileIndexY+1)) {
				RespawnStart();
				return false;
			}

			if (GetGameMap()->IsSwap(tileIndexX, tileIndexY)) {
				return SwapDetected(GoUp);
			}

			if (GetGameMap()->IsObstacle(tileIndexX, tileIndexY)) {
				ceilingY = (float)tileIndexY *TILE_LENGTH + TILE_LENGTH / 2.0f + GetGameMap()->position.y;
				return true;
			}
			if (checkedTile.x >= topRight.x) {
				break;
			}

		}




	}

	return false;
}
bool MovingObject::CollidesWithLeftWall(Float2 oldPosition, Float2 position, float & wallX) {

	Float2 oldCenter = MakeFloat2(oldPosition.x + mAABBOffset.x, oldPosition.y + mAABBOffset.y);
	Float2 center = MakeFloat2(position.x + mAABBOffset.x, position.y + mAABBOffset.y);

	wallX = 0.0f;

	Float2 oldBottomLeft = RoundFloat(MakeFloat2(oldCenter.x - mAABB.halfScale.x - 1.0f,
		oldCenter.y + mAABB.halfScale.y - 1.0f));
	Float2 newBottomLeft = RoundFloat(MakeFloat2(center.x - mAABB.halfScale.x - 1.0f,
		center.y + mAABB.halfScale.y - 1.0f));


	int endX = GetGameMap()->GetMapTileXAtPoint(newBottomLeft.x);
	int begX = MAX(GetGameMap()->GetMapTileXAtPoint(oldBottomLeft.x), endX);
	int dist = MAX(abs(endX - begX), 1);
	int tileIndexY;

	for (int tileIndexX = begX; tileIndexX >= endX; --tileIndexX)
	{
		{
			Float2 bottomLeft =
				MakeFloat2(
					GameSystem::Lerp(newBottomLeft.x, oldBottomLeft.x, (float)abs(endX - tileIndexX) / dist),
					GameSystem::Lerp(newBottomLeft.y, oldBottomLeft.y, (float)abs(endX - tileIndexX) / dist));
			Float2 topLeft = MakeFloat2(bottomLeft.x, bottomLeft.y - mAABB.halfScale.y * 2.0f);

			for (Float2 checkedTile = bottomLeft; ; checkedTile.y -= TILE_LENGTH)
			{
				checkedTile.y = MIN(checkedTile.y, topLeft.y);

				tileIndexY = GetGameMap()->GetMapTileYAtPoint(checkedTile.y);
				if (GetGameMap()->IsSpike(tileIndexX, tileIndexY)) {
					RespawnStart();
					return false;
				}

				if (GetGameMap()->IsSwap(tileIndexX, tileIndexY)) {
					return SwapDetected(GoLeft);
				}
				if (GetGameMap()->IsObstacle(tileIndexX, tileIndexY))
				{
					wallX = (float)tileIndexX * TILE_LENGTH + TILE_LENGTH / 2.0f + GetGameMap()->position.x;
					return true;
				}
				if (checkedTile.y <= topLeft.y)
					break;
			}
		}


	}
	return false;

}

bool MovingObject::CollidesWithRightWall(Float2 oldPosition, Float2 position, float & wallX)
{
	Float2 oldCenter = MakeFloat2(oldPosition.x + mAABBOffset.x, oldPosition.y + mAABBOffset.y);
	Float2 center = MakeFloat2(position.x + mAABBOffset.x, position.y + mAABBOffset.y);

	wallX = 0.0f;

	Float2 oldBottomRight = RoundFloat(MakeFloat2(oldCenter.x + mAABB.halfScale.x + 1.0f,
		oldCenter.y + mAABB.halfScale.y));
	Float2 newBottomRight = RoundFloat(MakeFloat2(center.x + mAABB.halfScale.x + 1.0f,
		center.y + mAABB.halfScale.y));


	int endX = GetGameMap()->GetMapTileXAtPoint(newBottomRight.x);
	int begX = MAX(GetGameMap()->GetMapTileXAtPoint(oldBottomRight.x) - 1, endX);
	int dist = MAX(abs(endX - begX), 1);
	int tileIndexY;

	for (int tileIndexX = begX; tileIndexX <= endX; ++tileIndexX)
	{
		{
			Float2 bottomRight =
				MakeFloat2(
					GameSystem::Lerp(newBottomRight.x, oldBottomRight.x, (float)abs(endX - tileIndexX) / dist),
					GameSystem::Lerp(newBottomRight.y, oldBottomRight.y, (float)abs(endX - tileIndexX) / dist));
			Float2 topRight = MakeFloat2(bottomRight.x, bottomRight.y - mAABB.halfScale.y * 2.0f);

			for (Float2 checkedTile = bottomRight; ; checkedTile.y -= TILE_LENGTH)
			{
				checkedTile.y = MIN(checkedTile.y, topRight.y);

				tileIndexY = GetGameMap()->GetMapTileYAtPoint(checkedTile.y);
				if (GetGameMap()->IsSpike(tileIndexX, tileIndexY)) {
					RespawnStart();
					return false;
				}

				if (GetGameMap()->IsSwap(tileIndexX, tileIndexY)) {
					return SwapDetected(GoRight);
				}
				if (GetGameMap()->IsObstacle(tileIndexX, tileIndexY))
				{
					wallX = (float)tileIndexX * TILE_LENGTH - TILE_LENGTH / 2.0f + GetGameMap()->position.x;
					return true;
				}
				if (checkedTile.y >= topRight.y)
					break;
			}
		}


	}
	return false;
}

Float2 MovingObject::RoundFloat(Float2 v)
{
	return MakeFloat2(round(v.x), round(v.y));
}

bool MovingObject::GetOverlap(AABB other)
{
	return mAABB.isOverlap(other);
}


void MovingObject::UpdatePhysics()
{
	//一個前のフレームのデータを保存
	oldPos = pos;
	oldSpeed = speed;

	wasOnGround = isOnGround;
	isPushedWallR = isPushesWallR;
	isPushedWallL = isPushesWallL;
	wasAtCeiling = isAtCeiling;

	if (!isCollisionToOther) {
		mAABB.center = MakeFloat2(pos.x + mAABBOffset.x, pos.y + mAABBOffset.y);
		return;
	}

	//移動
	pos = MakeFloat2(pos.x + speed.x * DELTATIME, pos.y + speed.y * DELTATIME);

	//重力
	float groundY = 0.0f, ceilingY = 0.0f;
	float rightWallX = 0.0f, leftWallX = 0.0f;

	if (speed.y >= 0.0f
		&& HasGround(oldPos, pos, speed, groundY, isOnOneWayPlatform))
	{
		pos.y = groundY - mAABB.halfScale.y;

		speed.y = 0.0f;
		isOnGround = true;
	}
	else {
		isOnGround = false;
	}

	if (speed.y <= 0.0f
		&& HasCeiling(oldPos, pos, ceilingY))
	{
		pos.y = ceilingY + mAABB.halfScale.y;
		speed.y = 0.0f;
		PlaySE(S_TOUCHCELL);
		isAtCeiling = true;
	}
	else {
		isAtCeiling = false;
	}


	if (speed.x <= 0.0f
		&& CollidesWithLeftWall(oldPos, pos, leftWallX))
	{
		if (oldPos.x + mAABB.halfScale.x - mAABBOffset.x >= leftWallX) {
			pos.x = leftWallX + mAABB.halfScale.x - mAABBOffset.x;

			isPushesWallL = true;
		}
		speed.x = MAX(speed.x, 0.0f);
	}
	else {
		isPushesWallL = false;
	}

	if (speed.x >= 0.0f
		&& CollidesWithRightWall(oldPos, pos, rightWallX))
	{
		if (oldPos.x - mAABB.halfScale.x - mAABBOffset.x <= rightWallX)
		{
			pos.x = rightWallX - mAABB.halfScale.x - mAABBOffset.x;

			isPushesWallR = true;
		}

		speed.x = MIN(speed.x, 0.0f);
	}
	else {
		isPushesWallR = false;
	}

	mAABB.center = MakeFloat2(pos.x + mAABBOffset.x, pos.y + mAABBOffset.y);



}

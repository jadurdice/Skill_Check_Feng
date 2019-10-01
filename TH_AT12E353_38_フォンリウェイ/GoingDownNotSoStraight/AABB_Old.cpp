#include"StageManeger.h"
#include"Game.h"
#include"AABB.h"
#include"complex"

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
	Float2 newBottomRight = RoundFloat(MakeFloat2(newBottomLeft.x + mAABB.halfScale.x * 2.0f - 2.0f, newBottomLeft.y));

	

	int endY = GetMap()->GetMapTileYAtPoint(newBottomLeft.y);
	int begY = MAX(GetMap()->GetMapTileYAtPoint(oldBottomLeft.y) - 1, endY);
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

			tileIndexX = GetMap()->GetMapTileXAtPoint(checkedTile.x);

			groundY = (float)(tileIndexY * TILE_LENGTH) + (TILE_LENGTH / 2.0f) + GetMap()->position.y;

			{
				if (GetMap()->IsSwap(tileIndexX, tileIndexY + 1)) {
					return SwapDetected(GoDown);
				}
				if (GetMap()->IsObstacle(tileIndexX, tileIndexY + 1)) {
					onOneWayPlatform = false;
					return true;
				}
				else if (GetMap()->IsOneWayPlatform(tileIndexX, tileIndexY + 1) &&
					abs(checkedTile.y + groundY) >= (cOneWayPlatformThreshold + mOldPosition.y) - position.y) {

					onOneWayPlatform = true;
				}
				if (checkedTile.x >= bottomRight.x) {
					if (onOneWayPlatform)
						return true;
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
	Float2 newTopLeft = RoundFloat(MakeFloat2(newTopRight.x - mAABB.halfScale.x * 2.0f + 2.0f, newTopRight.y));

	int endY = GetMap()->GetMapTileYAtPoint(newTopRight.y);
	int begY = MIN(GetMap()->GetMapTileYAtPoint(oldTopRight.y) - 1, endY);
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

			tileIndexX = GetMap()->GetMapTileXAtPoint(checkedTile.x);

			if (GetMap()->IsSwap(tileIndexX, tileIndexY)) {
				return SwapDetected(GoUp);
			}

			if (GetMap()->IsObstacle(tileIndexX, tileIndexY)) {
				ceilingY = (float)tileIndexY *TILE_LENGTH + TILE_LENGTH / 2.0f + GetMap()->position.y;
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
		oldCenter.y + mAABB.halfScale.y-1.0f));
	Float2 newBottomLeft = RoundFloat(MakeFloat2(center.x - mAABB.halfScale.x - 1.0f,
		center.y + mAABB.halfScale.y-1.0f));
	Float2 newTopLeft = RoundFloat(MakeFloat2(newBottomLeft.x, newBottomLeft.y - mAABB.halfScale.y * 2.0f));


	int endX = GetMap()->GetMapTileXAtPoint(newBottomLeft.x);
	int begX = MAX(GetMap()->GetMapTileXAtPoint(oldBottomLeft.x), endX);
	int dist = MAX((int)abs((float)endX - (float)begX), 1);
	int tileIndexY;

	for (int tileIndexX = begX; tileIndexX >= endX; --tileIndexX)
	{
		{
			Float2 bottomLeft =
				MakeFloat2(
					GameSystem::Lerp(newBottomLeft.x, oldBottomLeft.x, abs((float)endX - (float)tileIndexX) / dist),
					GameSystem::Lerp(newBottomLeft.y, oldBottomLeft.y, abs((float)endX - (float)tileIndexX) / dist));
			Float2 topLeft = MakeFloat2(bottomLeft.x, bottomLeft.y - mAABB.halfScale.y * 2.0f);

			for (Float2 checkedTile = bottomLeft; ; checkedTile.y -= TILE_LENGTH)
			{
				checkedTile.y = MIN(checkedTile.y, topLeft.y);

				tileIndexY = GetMap()->GetMapTileYAtPoint(checkedTile.y);

				if (GetMap()->IsSwap(tileIndexX, tileIndexY)) {
					return SwapDetected(GoLeft);
				}
				if (GetMap()->IsObstacle(tileIndexX, tileIndexY))
				{
					wallX = (float)tileIndexX * TILE_LENGTH + TILE_LENGTH / 2.0f + GetMap()->position.x;
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
	Float2 newTopRight = RoundFloat(MakeFloat2(newBottomRight.x, newBottomRight.y - mAABB.halfScale.y * 2.0f));


	int endX = GetMap()->GetMapTileXAtPoint(newBottomRight.x);
	int begX = MAX(GetMap()->GetMapTileXAtPoint(oldBottomRight.x) - 1, endX);
	int dist = MAX((int)abs((float)endX - (float)begX), 1);
	int tileIndexY;

	for (int tileIndexX = begX; tileIndexX <= endX; ++tileIndexX)
	{
		{
			Float2 bottomRight =
				MakeFloat2(
					GameSystem::Lerp(newBottomRight.x, oldBottomRight.x, abs((float)endX - (float)tileIndexX) / dist),
					GameSystem::Lerp(newBottomRight.y, oldBottomRight.y, abs((float)endX - (float)tileIndexX) / dist));
			Float2 topRight = MakeFloat2(bottomRight.x, bottomRight.y - mAABB.halfScale.y * 2.0f);

			for (Float2 checkedTile = bottomRight; ; checkedTile.y -= TILE_LENGTH)
			{
				checkedTile.y = MIN(checkedTile.y, topRight.y);

				tileIndexY = GetMap()->GetMapTileYAtPoint(checkedTile.y);

				if (GetMap()->IsSwap(tileIndexX, tileIndexY)) {
					return SwapDetected(GoRight);
				}
				if (GetMap()->IsObstacle(tileIndexX, tileIndexY))
				{
					wallX = (float)tileIndexX * TILE_LENGTH - TILE_LENGTH / 2.0f + GetMap()->position.x;
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
	mOldPosition = mPosition;
	mOldSpeed = mSpeed;

	mWasOnOneWayPlatform = mOnOneWayPlatform;
	mWasOnGround = mOnGround;
	mPushedRightWall = mPushesRightWall;
	mPushedLeftWall = mPushesLeftWall;
	mWasAtCeiling = mAtCeiling;

	if (!mCollisionToOther) {
		mAABB.center = MakeFloat2(mPosition.x + mAABBOffset.x, mPosition.y + mAABBOffset.y);
		return;
	}

	//移動
	mPosition = MakeFloat2(mPosition.x + mSpeed.x * DELTATIME, mPosition.y + mSpeed.y * DELTATIME);

	//重力
	float groundY = 0.0f, ceilingY = 0.0f;
	float rightWallX = 0.0f, leftWallX = 0.0f;


	if (mSpeed.y >= 0.0f
		&& HasGround(mOldPosition, mPosition, mSpeed, groundY, mOnOneWayPlatform))
	{
		mPosition.y = groundY - mAABB.halfScale.y*1.5f;


		mSpeed.y = 0.0f;
		mOnGround = true;
	}
	else {
		mOnGround = false;
	}

	if (mSpeed.y <= 0.0f
		&& HasCeiling(mOldPosition, mPosition, ceilingY))
	{
		mPosition.y = ceilingY+mAABB.halfScale.y*0.5f;
		mSpeed.y = 0.0f;
		mAtCeiling = true;
	}
	else {
		mAtCeiling = false;
	}


	if (mSpeed.x <= 0.0f
		&& CollidesWithLeftWall(mOldPosition, mPosition, leftWallX))
	{
		if (mOldPosition.x + mAABB.halfScale.x - mAABBOffset.x >= leftWallX) {
			mPosition.x = leftWallX + mAABB.halfScale.x - mAABBOffset.x;
			mPushesLeftWall = true;
		}
		mSpeed.x = MAX(mSpeed.x, 0.0f);
	}
	else {
		mPushesLeftWall = false;
	}

	if (mSpeed.x >= 0.0f
		&& CollidesWithRightWall(mOldPosition, mPosition, rightWallX))
	{
		if (mOldPosition.x - mAABB.halfScale.x - mAABBOffset.x <= rightWallX)
		{
			mPosition.x = rightWallX - mAABB.halfScale.x + mAABBOffset.x;
			mPushesRightWall = true;
		}

		mSpeed.x = MIN(mSpeed.x, 0.0f);
	}
	else {
		mPushesRightWall = false;
	}

	mAABB.center = MakeFloat2(mPosition.x + mAABBOffset.x, mPosition.y + mAABBOffset.y);



}

#pragma once

#include"system.h"


class AABB
{
public:

	Float2 center;
	Float2 halfScale;

	bool isOverlap(AABB other);
	void SetAABB(Float2 center, Float2 halfScale);

private:

};

class MovingObject
{
public:


	const float cOneWayPlatformThreshold = 57.5f;

	 Float2 oldPos;
	 Float2 pos;

	 Float2 oldSpeed;
	 Float2 speed;

	 Float2 scale;

	 AABB mAABB;
	 Float2 mAABBOffset;

	 bool isPushedWallR;
	 bool isPushesWallR;
		  
	 bool isPushedWallL;
	 bool isPushesWallL;
		  
	 bool wasOnGround;
	 bool isOnGround;
		  
	 bool wasAtCeiling;
	 bool isAtCeiling;
		  
	 bool wasOnOneWayPlatform;
	 bool isOnOneWayPlatform;
	 bool isThroughOneWay;
	 bool isCollisionToOther;


	 bool HasGround(Float2 oldPosition, Float2 position, Float2 speed,float &groundY, bool& onOneWayPlatform);
	 bool HasCeiling(Float2 oldPosition, Float2 position, float &ceilingY);
	 bool CollidesWithLeftWall(Float2 oldPosition, Float2 position, float &wallX);
	 bool CollidesWithRightWall(Float2 oldPosition, Float2 position, float &wallX);
	 Float2 RoundFloat(Float2 v);

	 bool GetOverlap(AABB other);
	 

	 void UpdatePhysics();

};


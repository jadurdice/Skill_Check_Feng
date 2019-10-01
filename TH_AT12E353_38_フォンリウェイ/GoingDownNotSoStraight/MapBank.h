#pragma once


#include"MapObject.h"

#define	  ROOM4WAYMAX	(6)
#define	  ROOM3WAYMAX	(3)
#define	  ROOM2WAYMAX	(3)

MapBluePrint GetRoom(int index);
MapBluePrint Get4WayRoom();
MapBluePrint Get3WayRoom(int index);
MapBluePrint Get2WayRoom(int index);

MapBluePrint GetStartRoom();
MapBluePrint GetGoalRoom(int location);
void GetTutorRoom(MapBluePrint room[9]);
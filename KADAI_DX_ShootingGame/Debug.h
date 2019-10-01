#ifndef DEBUG_H_
#define DEBUG_H_

#include"common.h"

#define DEBUG_CIRCOL_VERTEXNUM	(8)
#define DEBUG_CIRCOL_MAX		(4096)

#define ALLVERTEX	(DEBUG_CIRCOL_VERTEXNUM * DEBUG_CIRCOL_MAX * sizeof(DebugCircleVertex))
#define ALLINDEX	(DEBUG_CIRCOL_VERTEXNUM * 2 * DEBUG_CIRCOL_MAX * sizeof(WORD))

#define FVF_DEBUGCIRCLEVERTEX	(D3DFVF_XYZRHW| D3DFVF_DIFFUSE)

typedef struct DebugCircleVertex_tag{
	D3DXVECTOR4	pos;
	D3DCOLOR	color;
}DebugCircleVertex;

void InitDebug();
void UninitDebug();
void BegineDebug();
void EndDebug();

void DebugDrawCircleCol(float x,float y, float radius);
void DebugSetColor(D3DCOLOR color);


#endif
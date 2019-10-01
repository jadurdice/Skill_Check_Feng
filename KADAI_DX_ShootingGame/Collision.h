#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <d3dx9.h>
typedef struct CircleCol_tag {
	D3DXVECTOR2 pos;
	float radius;
	char tag;
}CircleCol;

inline bool isCircle2Circle(CircleCol* pA, CircleCol *pB)
{
	return (pA->radius + pB->radius)*(pA->radius + pB->radius) > D3DXVec2LengthSq(&(pA->pos - pB->pos));
}

#endif
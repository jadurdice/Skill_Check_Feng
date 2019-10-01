#include "Debug.h"
#include"d3dsystem.h"
#include"Collision.h"

static LPDIRECT3DVERTEXBUFFER9 glbVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 glbIndexBuffer = NULL;
CircleCol glbCircles[DEBUG_CIRCOL_MAX];
static int glbCircleCnt = 0;
D3DCOLOR glbColor = 0xFFFFFFFF;
D3DCOLOR glbColors[DEBUG_CIRCOL_MAX];
static LPDIRECT3DDEVICE9 device;

void InitDebug()
{
#if defined(_DEBUG) || defined(DEBUG)

	//頂点バッファを作る
	device = GetDevice();
	device->CreateVertexBuffer(ALLVERTEX, D3DUSAGE_WRITEONLY, FVF_DEBUGCIRCLEVERTEX, D3DPOOL_MANAGED, &glbVertexBuffer, NULL);

	//インデックスバッファを作る
	device->CreateIndexBuffer(ALLINDEX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &glbIndexBuffer, NULL);

#endif

}

void UninitDebug()
{
#if defined(_DEBUG) || defined(DEBUG)

	glbVertexBuffer->Release();
	glbIndexBuffer->Release();
#endif

}

void BegineDebug()
{
#if defined(_DEBUG) || defined(DEBUG)

	glbCircleCnt = 0;
#endif
}


void EndDebug()
{
#if defined(_DEBUG) || defined(DEBUG)

	static const float onePizza = DEGREE_TO_RADIAN(45);
	DebugCircleVertex *pV;
	glbVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	for (int i = 0; i < glbCircleCnt; i++)
	{
		int startIndex = i * DEBUG_CIRCOL_VERTEXNUM;
		for (int j = 0; j < DEBUG_CIRCOL_VERTEXNUM; j++)
		{
			pV[startIndex + j].pos.x = cosf(j*onePizza) * glbCircles[i].radius + glbCircles[i].pos.x;
			pV[startIndex + j].pos.y = sinf(j*onePizza) * glbCircles[i].radius + glbCircles[i].pos.y;
			pV[startIndex + j].pos.z = 0.0f;
			pV[startIndex + j].pos.w = 1.0f;
			pV[startIndex + j].color = glbColors[i];
		}
	}

	glbVertexBuffer->Unlock();

	WORD *pWDIndex;
	glbIndexBuffer->Lock(0, 0, (void**)&pWDIndex, D3DLOCK_DISCARD);

	for (int i = 0; i < glbCircleCnt; i++)
	{
		int startIndex = i * DEBUG_CIRCOL_VERTEXNUM * 2;
		for (int j = 0; j < DEBUG_CIRCOL_VERTEXNUM; j++)
		{
			pWDIndex[startIndex + j * 2 + 0] = i * DEBUG_CIRCOL_VERTEXNUM + j;
			pWDIndex[startIndex + j * 2 + 1] = i * DEBUG_CIRCOL_VERTEXNUM + ((j + 1) % DEBUG_CIRCOL_VERTEXNUM);
		}
	}

	glbIndexBuffer->Unlock();
	device->SetStreamSource(0, glbVertexBuffer, 0, sizeof(DebugCircleVertex));
	device->SetIndices(glbIndexBuffer);
	device->SetFVF(FVF_DEBUGCIRCLEVERTEX);
	device->SetTexture(0, NULL);
	device->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, glbCircleCnt*DEBUG_CIRCOL_VERTEXNUM, 0, glbCircleCnt * DEBUG_CIRCOL_VERTEXNUM);
#endif
}

void DebugDrawCircleCol(float x, float y, float radius)
{
#if defined(_DEBUG) || defined(DEBUG)

	glbCircles[glbCircleCnt].pos.x = x;
	glbCircles[glbCircleCnt].pos.y = y;
	glbCircles[glbCircleCnt].radius = radius;
	glbColors[glbCircleCnt] = glbColor;

	glbCircleCnt++;
#endif
}

void DebugSetColor(D3DCOLOR color)
{
#if defined(_DEBUG) || defined(DEBUG)

	glbColor = color;
#endif
}

#include "Sprite.h"
#include "Game.h"
#include "d3dsystem.h"

static D3DCOLOR glbColor = D3DCOLOR_RGBA(255, 255, 255, 255);
LPDIRECT3DVERTEXBUFFER9 glbVertexBuffer = NULL;

bool skipShake = false;

void InitSprite() {
	LPDIRECT3DDEVICE9 device = GetDevice();
	device->CreateVertexBuffer(sizeof(Vertex2d) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &glbVertexBuffer, NULL);
}

void UninitSprite() {
	if (glbVertexBuffer) {
		glbVertexBuffer->Release();
		glbVertexBuffer = NULL;
	}
}

void DrawSpriteIndex(int textureID, float dx, float dy) {
	LPDIRECT3DDEVICE9 device = GetDevice();

	//頂点データ（TriangleStrip）
	//

	int tw = GetTextureWidth(textureID);
	int th = GetTextureHeight(textureID);

	WORD index[] = {
		0,1,2,1,3,2
	};

	Vertex2d s[] = {
	{D3DXVECTOR4(dx + HOSEI		,dy + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(0,0)},
	{D3DXVECTOR4(dx + HOSEI + tw,dy + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(1,0)},
	{D3DXVECTOR4(dx + HOSEI		,dy + HOSEI + th,0.0f,1.0f),glbColor,D3DXVECTOR2(0,1)},
	{D3DXVECTOR4(dx + HOSEI + tw,dy + HOSEI + th,0.0f,1.0f),glbColor,D3DXVECTOR2(1,1)}

	};

	device->SetFVF(FVF_VERTEX2D);
	device->SetTexture(0, GetTexture(textureID));
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, s, sizeof(Vertex2d));


}

void DrawSprite(int textureID, float dx, float dy)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	//頂点データ（TriangleStrip）
	//

	int tw = GetTextureWidth(textureID);
	int th = GetTextureHeight(textureID);


	Vertex2d s[] = {
	{D3DXVECTOR4(dx + HOSEI		,dy + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(0,0)},
	{D3DXVECTOR4(dx + HOSEI + tw,dy + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(1,0)},
	{D3DXVECTOR4(dx + HOSEI		,dy + HOSEI + th,0.0f,1.0f),glbColor,D3DXVECTOR2(0,1)},
	{D3DXVECTOR4(dx + HOSEI + tw,dy + HOSEI + th,0.0f,1.0f),glbColor,D3DXVECTOR2(1,1)}

	};

	device->SetFVF(FVF_VERTEX2D);
	device->SetTexture(0, GetTexture(textureID));
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, s, sizeof(Vertex2d));


}

void DrawSpriteCut(int textureID, float dx, float dy, int cx, int cy, int cw, int ch)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	//頂点データ（TriangleStrip）
	//

	int tw = GetTextureWidth(textureID);
	int th = GetTextureHeight(textureID);

	float u0 = cx / (float)tw;
	float v0 = cy / (float)th;
	float v1 = (cy + ch) / (float)th;
	float u1 = (cx + cw) / (float)tw;

	Vertex2d s[] = {
	{D3DXVECTOR4(dx + HOSEI		,dy + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(u0,v0)},
	{D3DXVECTOR4(dx + HOSEI + cw,dy + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(u1,v0)},
	{D3DXVECTOR4(dx + HOSEI		,dy + HOSEI + ch,0.0f,1.0f),glbColor,D3DXVECTOR2(u0,v1)},
	{D3DXVECTOR4(dx + HOSEI + cw,dy + HOSEI + ch,0.0f,1.0f),glbColor,D3DXVECTOR2(u1,v1)}

	};

	device->SetFVF(FVF_VERTEX2D);
	device->SetTexture(0, GetTexture(textureID));
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, s, sizeof(Vertex2d));


}

void DrawSpriteRotScr(int textureID, float dx, float dy, int cx, int cy, int cw, int ch, float angle, float cenx, float ceny, float scalex, float scaley)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;
	float radian = DEGREE_TO_RADIAN(angle);

	D3DXMatrixIdentity(&mtxW);
	D3DXMatrixTranslation(&mtxT, -cenx, -ceny, 0.0f);
	D3DXMatrixScaling(&mtxS, scalex, scaley, 1.0f);
	D3DXMatrixTranslation(&mtxIT, cenx, ceny, 0.0f);
	D3DXMatrixRotationZ(&mtxR, radian);
	mtxW = mtxT * mtxS*  mtxR * mtxIT;


	//回転の仕方
	//①回転軸とテクスチャを原点に戻る
	//②回転する
	//③テクスチャを元の場所に指定する





	//頂点データ（TriangleStrip）
	//

	int tw = GetTextureWidth(textureID);
	int th = GetTextureHeight(textureID);

	float u0 = cx / (float)tw;
	float v0 = cy / (float)th;
	float v1 = (cy + ch) / (float)th;
	float u1 = (cx + cw) / (float)tw;

	Vertex2d s[] = {
	{D3DXVECTOR4(dx + HOSEI		,dy + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(u0,v0)},
	{D3DXVECTOR4(dx + HOSEI + cw,dy + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(u1,v0)},
	{D3DXVECTOR4(dx + HOSEI		,dy + HOSEI + ch,0.0f,1.0f),glbColor,D3DXVECTOR2(u0,v1)},
	{D3DXVECTOR4(dx + HOSEI + cw,dy + HOSEI + ch,0.0f,1.0f),glbColor,D3DXVECTOR2(u1,v1)} };

	D3DXVec4Transform(&s[0].pos, &s[0].pos, &mtxW);
	D3DXVec4Transform(&s[1].pos, &s[1].pos, &mtxW);
	D3DXVec4Transform(&s[2].pos, &s[2].pos, &mtxW);
	D3DXVec4Transform(&s[3].pos, &s[3].pos, &mtxW);



	device->SetFVF(FVF_VERTEX2D);
	device->SetTexture(0, GetTexture(textureID));
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, s, sizeof(Vertex2d));


}

void DrawSpriteRotPlg(int textureID, float dx, float dy, int cx, int cy, int cw, int ch, float angle, float axisx, float axisy, float scalex, float scaley)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	D3DXMATRIX mtxW, mtxR, mtxT, mtxS, mtxIT;
	float radian = DEGREE_TO_RADIAN(angle);

	D3DXMatrixTranslation(&mtxT, -axisx * cw, -axisy * ch, 0.0f);
	D3DXMatrixTranslation(&mtxIT, (axisx * cw + dx), (axisy * ch + dy), 0.0f);
	D3DXMatrixScaling(&mtxS, scalex, scaley, 1.0f);
	D3DXMatrixRotationZ(&mtxR, radian);
	mtxW = mtxT * mtxS*mtxR *  mtxIT;



	//回転の仕方
	//①-0.5f,-0.5fでポリゴンを作成
	//②回転する座標の分を減る
	//③回転する
	//④元の場所+dx,dyに戻る



	//回転する前


	//頂点データ（TriangleStrip）
	//

	int tw = GetTextureWidth(textureID);
	int th = GetTextureHeight(textureID);

	float u0 = cx / (float)tw;
	float v0 = cy / (float)th;
	float u1 = (cx + cw) / (float)tw;
	float v1 = (cy + ch) / (float)th;

	D3DXVECTOR2 shake = {0.0f,0.0f};
	if (GameSystem::GetShakeForce().x != 0.0f) {
		shake = GameSystem::GetShakeForce();
	}

	Vertex2d s[] = {
	{D3DXVECTOR4(shake.x + HOSEI		,shake.y + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(u0,v0)},
	{D3DXVECTOR4(shake.x + HOSEI + cw	,shake.y + HOSEI		,0.0f,1.0f),glbColor,D3DXVECTOR2(u1,v0)},
	{D3DXVECTOR4(shake.x + HOSEI		,shake.y + HOSEI + ch,0.0f,1.0f),glbColor,D3DXVECTOR2(u0,v1)},
	{D3DXVECTOR4(shake.x + HOSEI + cw	,shake.y + HOSEI + ch,0.0f,1.0f),glbColor,D3DXVECTOR2(u1,v1)} };

	D3DXVec4Transform(&s[0].pos, &s[0].pos, &mtxW);
	D3DXVec4Transform(&s[1].pos, &s[1].pos, &mtxW);
	D3DXVec4Transform(&s[2].pos, &s[2].pos, &mtxW);
	D3DXVec4Transform(&s[3].pos, &s[3].pos, &mtxW);


	device->SetFVF(FVF_VERTEX2D);
	device->SetTexture(0, GetTexture(textureID));
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, s, sizeof(Vertex2d));




}

void DrawSpriteRotCenter(int textureID, float dx, float dy, int cx, int cy, int cw, int ch, float angle, float axisx, float axisy, float scalex, float scaley)
{
	LPDIRECT3DDEVICE9 device = GetDevice();



	D3DXMATRIX mtxW, mtxR, mtxT, mtxS, mtxIT;
	float radian = DEGREE_TO_RADIAN(angle);

	D3DXMatrixTranslation(&mtxT, -axisx * cw, -axisy * ch, 0.0f);
	D3DXMatrixTranslation(&mtxIT, (axisx * cw + dx), (axisy * ch + dy), 0.0f);
	D3DXMatrixScaling(&mtxS, scalex, scaley, 1.0f);
	D3DXMatrixRotationZ(&mtxR, radian);
	mtxW = mtxT * mtxS* mtxR * mtxIT;



	//回転の仕方
	//①-0.5f,-0.5fでポリゴンを作成
	//②回転する座標の分を減る
	//③回転する
	//④元の場所+dx,dyに戻る



	//回転する前


	//頂点データ（TriangleStrip）
	//

	int tw = GetTextureWidth(textureID);
	int th = GetTextureHeight(textureID);

	float u0 = cx / (float)tw;
	float v0 = cy / (float)th;
	float v1 = (cy + ch) / (float)th;
	float u1 = (cx + cw) / (float)tw;

	float hw = cw * 0.5f * scalex;
	float hh = ch * 0.5f * scaley;


	Vertex2d s[] = {
	{D3DXVECTOR4(HOSEI	-	hw,HOSEI	-	hh,0.0f,1.0f),glbColor,D3DXVECTOR2(u0,v0)},
	{D3DXVECTOR4(HOSEI	+	hw,HOSEI	-	hh,0.0f,1.0f),glbColor,D3DXVECTOR2(u1,v0)},
	{D3DXVECTOR4(HOSEI	-	hw,HOSEI	+	hh,0.0f,1.0f),glbColor,D3DXVECTOR2(u0,v1)},
	{D3DXVECTOR4(HOSEI	+	hw,HOSEI	+	hh,0.0f,1.0f),glbColor,D3DXVECTOR2(u1,v1)} };

	D3DXVec4Transform(&s[0].pos, &s[0].pos, &mtxW);
	D3DXVec4Transform(&s[1].pos, &s[1].pos, &mtxW);
	D3DXVec4Transform(&s[2].pos, &s[2].pos, &mtxW);
	D3DXVec4Transform(&s[3].pos, &s[3].pos, &mtxW);


	device->SetFVF(FVF_VERTEX2D);
	device->SetTexture(0, GetTexture(textureID));
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, s, sizeof(Vertex2d));



}


void SetColor(int r, int g, int b, int a) {
	glbColor = D3DCOLOR_RGBA(r, g, b, a);
}

void SetColor(D3DCOLOR color)
{
	glbColor = color;
}

void StartParticle() {
	LPDIRECT3DDEVICE9 device = GetDevice();


	// レンダーステート(加算合成処理)
	// 色 = (SRC色 * SRCアルファ) + (DEST色 * (1.0)アルファ)
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// αデスティネーションカラーの指定(1.0)

}

void EndParticle() {
	LPDIRECT3DDEVICE9 device = GetDevice();

	// レンダーステート(通常ブレンド処理)
// 色 = (SRC色 * SRCアルファ) + (DEST色 * (1.0 - SRC)アルファ)
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定(1.0 - SRC)

}
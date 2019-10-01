#include <Windows.h>
#include "DirectX.h"

#pragma region グローバル変数宣言

LPDIRECT3D9 glbD3DInterface;				// DirectXインターフェース
D3DPRESENT_PARAMETERS *glbD3DPresentParam;	//描画パラメータ
LPDIRECT3DDEVICE9 glbD3DDevice;				//D3Dデバイス

D3DXVECTOR3 glbCameraPosition;				// カメラ位置
D3DXVECTOR3 glbEyePosition; 				// 注視点
D3DXVECTOR3 glbUpVector;					// カメラの向き

VERTEX glbV[6][4];							//ポリゴン頂点データ
D3DXVECTOR3 glbPolygonPosition;				//ポリゴン座標
D3DXVECTOR3 glbPolygonRotation;				//ポリゴン回転
D3DXVECTOR3 glbPolygonScale;				//ポリゴン拡大

float moveFactor;

#pragma endregion

bool InitDirectX(HWND window_handle)
{

	#pragma region インターフェース作成


	glbD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (glbD3DInterface == NULL)
	{
		// 作成失敗
		return false;
	}

	glbD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (glbD3DPresentParam == NULL)
	{
		return false;
	}
	ZeroMemory(glbD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// バックバッファの数 => 1
	glbD3DPresentParam->BackBufferCount = 1;
	// バックバッファのフォーマット => D3DFMT_UNKNOWN(フォーマットを知りません)
	glbD3DPresentParam->BackBufferFormat = D3DFMT_UNKNOWN;
	// ウィンドウモード設定 => 定数で切り替え
	glbD3DPresentParam->Windowed = true;

	// スワップエフェクト設定 => ディスプレイドライバ依存
	// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	glbD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

#pragma endregion

	#pragma region DirectDeviceの作成
	
	if (FAILED(glbD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		glbD3DPresentParam,
		&glbD3DDevice)))
	{
		return false;
	}

#pragma endregion

	#pragma region ビューポートパラメータ設定

	D3DVIEWPORT9 viewPort;

	// ビューポートの左上座標
	viewPort.X = 0;
	viewPort.Y = 0;
	// ビューポートの幅
	viewPort.Width = glbD3DPresentParam->BackBufferWidth;
	// ビューポートの高さ
	viewPort.Height = glbD3DPresentParam->BackBufferHeight;
	// ビューポート深度設定
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;

	if (FAILED(glbD3DDevice->SetViewport(&viewPort)))
	{
		return false;
	}

#pragma endregion

	#pragma region ポリゴンのローカル座標の位置設定

	D3DXCOLOR pointColor[8];

	pointColor[0] = { 0.0f,0.0f,0.0f,1.0f };
	pointColor[1] = { 0.0f,1.0f,1.0f,1.0f };
	pointColor[2] = { 1.0f,0.0f,1.0f,1.0f };
	pointColor[3] = { 1.0f,1.0f,0.0f,1.0f };
	pointColor[4] = { 1.0f,0.0f,0.0f,1.0f };
	pointColor[5] = { 0.0f,1.0f,0.0f,1.0f };
	pointColor[6] = { 0.0f,0.0f,1.0f,1.0f };
	pointColor[7] = { 1.0f,1.0f,1.0f,1.0f };

	//bottom
	glbV[0][0].color = pointColor[0];//1
	glbV[0][1].color = pointColor[1];//2
	glbV[0][2].color = pointColor[2];//3
	glbV[0][3].color = pointColor[3];//4
	glbV[0][0].position = { 1.0f,	-1.0f,	1.0f };
	glbV[0][1].position = { -1.0f,	-1.0f,	1.0f };
	glbV[0][2].position = { 1.0f,	-1.0f,	-1.0f };
	glbV[0][3].position = { -1.0f,	-1.0f,	-1.0f };

	//top
	glbV[1][0].color = pointColor[4];//5
	glbV[1][1].color = pointColor[5];//6
	glbV[1][2].color = pointColor[6];//7
	glbV[1][3].color = pointColor[7];//8
	glbV[1][0].position = { 1.0f,	1.0f,	-1.0f };
	glbV[1][1].position = { -1.0f,	1.0f,	-1.0f };
	glbV[1][2].position = { 1.0f,	1.0f,	1.0f };
	glbV[1][3].position = { -1.0f,	1.0f,	1.0f };

	//left
	glbV[2][0].color = pointColor[7];//8
	glbV[2][1].color = pointColor[5];//6
	glbV[2][2].color = pointColor[1];//2
	glbV[2][3].color = pointColor[3];//4
	glbV[2][0].position = { -1.0f,	1.0f,	1.0f };
	glbV[2][1].position = { -1.0f,	1.0f,	-1.0f };
	glbV[2][2].position = { -1.0f,	-1.0f,	1.0f };
	glbV[2][3].position = { -1.0f,	-1.0f,	-1.0f };

	//right
	glbV[3][0].color = pointColor[4];//5
	glbV[3][1].color = pointColor[6];//7
	glbV[3][2].color = pointColor[2];//3
	glbV[3][3].color = pointColor[0];//1
	glbV[3][0].position = { 1.0f,	1.0f,	-1.0f };
	glbV[3][1].position = { 1.0f,	1.0f,	1.0f };
	glbV[3][2].position = { 1.0f,	-1.0f,	-1.0f };
	glbV[3][3].position = { 1.0f,	-1.0f,	1.0f };

	//front
	glbV[4][0].color = pointColor[6];//7
	glbV[4][1].color = pointColor[7];//8
	glbV[4][2].color = pointColor[0];//1
	glbV[4][3].color = pointColor[1];//2
	glbV[4][0].position = { 1.0f,	1.0f,	1.0f };
	glbV[4][1].position = { -1.0f,	1.0f,	1.0f };
	glbV[4][2].position = { 1.0f,	-1.0f,	1.0f };
	glbV[4][3].position = { -1.0f,	-1.0f,	1.0f };

	//back
	glbV[5][0].color =pointColor[5];//6
	glbV[5][1].color =pointColor[4];//5
	glbV[5][2].color =pointColor[3];//4
	glbV[5][3].color =pointColor[2];//3
	glbV[5][0].position = { -1.0f,	1.0f,	-1.0f };
	glbV[5][1].position = { 1.0f,	1.0f,	-1.0f };
	glbV[5][2].position = { -1.0f,	-1.0f,	-1.0f };
	glbV[5][3].position = { 1.0f,	-1.0f,	-1.0f };



#pragma endregion

	#pragma region グローバル変数の初期化

	glbCameraPosition = { 0.0f, 3.0f, -10.0f };
	glbEyePosition = { 0.0f, 0.0f, 0.0f };
	glbUpVector = { 0.0f, 1.0f, 0.0f };
	glbPolygonPosition = { 0.0f,0.0f,0.0f };
	glbPolygonRotation = { 0.0f,0.0f,0.0f };
	glbPolygonScale = { 1.0f,1.0f,1.0f };

#pragma endregion

	return true;
}

void UpdateDirextX(void)
{

	#pragma region グローバル変数変動

	moveFactor += D3DXToRadian(1);

	glbPolygonRotation += {0.02f, 0.02f, 0.02f};
	glbPolygonPosition = { 3.0f*cosf(moveFactor),1.0f + 3.0f*sinf(moveFactor), 0.0f};
	glbEyePosition = glbPolygonPosition;

	#pragma endregion

	#pragma region ビュー座標変換用の行列算出 

	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView,
		&glbCameraPosition,				// カメラ座標
		&glbEyePosition,					// 注視点座標
		&glbUpVector);				// カメラの上の向きのベクトル
	glbD3DDevice->SetTransform(D3DTS_VIEW, &matView);

#pragma endregion

	#pragma region 射影座標変換用の行列算出 
	D3DXMATRIX matProjection;
	D3DVIEWPORT9 vp;
	glbD3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&matProjection,
		D3DXToRadian(45),	// 画角
		aspect,				// アスペクト比
		0.1f,				// near
		500.0f);			// far
	glbD3DDevice->SetTransform(D3DTS_PROJECTION, &matProjection);

#pragma endregion

}

void DrawDirectX()
{

	#pragma region 前のバックバッファ除去と描画開始

	glbD3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 100, 100, 100),
		1.0f,	// Zバッファの初期値
		0);		// ステンシルバッファの初期値

	glbD3DDevice->BeginScene();

	//ライティングを無効にする。
	glbD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	#pragma endregion

	#pragma region ワールド座標変換用の行列の算出 

	D3DXMATRIX matWorld, matTrans, matRot, matRotx, matRoty, matRotz, matScale;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	// 移動
	D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, 10.0f);

	// 回転

	D3DXMatrixRotationX(&matRotx, glbPolygonRotation.x);
	D3DXMatrixRotationY(&matRoty, glbPolygonRotation.y);
	D3DXMatrixRotationZ(&matRotz, glbPolygonRotation.z);

	D3DXMatrixMultiply(&matRot, &matRot, &matRoty);
	D3DXMatrixMultiply(&matRot, &matRot, &matRotx);
	D3DXMatrixMultiply(&matRot, &matRot, &matRotz);

	// 拡大
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);

	// 掛け合わせ(拡縮 * 回転 * 移動)
	matWorld *= matScale * matRot * matTrans;

	glbD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);


#pragma endregion

	#pragma region FVFとテクスチャの設定

	glbD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	glbD3DDevice->SetTexture(0, NULL);

	#pragma endregion
	
	#pragma region ポリゴンのDrawPrimitiveUP

	for (int i = 0; i < 6; i++)
	{
		glbD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, glbV[i], sizeof(VERTEX));
	}

#pragma endregion

	#pragma region 描画終了

	glbD3DDevice->EndScene();
	glbD3DDevice->Present(NULL, NULL, NULL, NULL);

#pragma endregion


}
#include <Windows.h>
#include "DirectX.h"

// グローバル変数
LPDIRECT3D9 glbD3DInterface;	// DirectXインターフェース
D3DPRESENT_PARAMETERS *glbD3DPresentParam;
LPDIRECT3DDEVICE9 glbD3DDevice;

bool InitDirectX(HWND window_handle)
{
	// インターフェース作成
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

	// DirectDeviceの作成
	if (FAILED(glbD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		glbD3DPresentParam,
		&glbD3DDevice)))
	{
		return false;
	}

	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = glbD3DPresentParam->BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = glbD3DPresentParam->BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(glbD3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void Draw()
{
	glbD3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,			// 初期化するバッファの種類
		D3DCOLOR_ARGB(255, 0, 0, 0),// フレームバッファの初期化色
		1.0f,						// Zバッファの初期値
		0);							// ステンシルバッファの初期値

	glbD3DDevice->BeginScene();

	// 三角形を描画 start
	VERTEX v[3];

	v[0].pos.x = 200.0f; v[0].pos.y = 120.0f; v[0].pos.z = 0.0f;
	v[1].pos.x = 240.0f; v[1].pos.y = 200.0f; v[1].pos.z = 0.0f;
	v[2].pos.x = 160.0f; v[2].pos.y = 200.0f; v[2].pos.z = 0.0f;

	v[0].w = v[1].w = v[2].w = 1.0f;

	v[0].color = D3DCOLOR_ARGB(255, 255, 0, 0);
	v[1].color = D3DCOLOR_ARGB(255, 255, 0, 0);
	v[2].color = D3DCOLOR_ARGB(255, 255, 0, 0);

	// 頂点構造の指定
	glbD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	glbD3DDevice->SetTexture(0, NULL);

	glbD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, v, sizeof(VERTEX));

	// 三角形を描画 end

	glbD3DDevice->EndScene();

	glbD3DDevice->Present(NULL, NULL, NULL, NULL);

}
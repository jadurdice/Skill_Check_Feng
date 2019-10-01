/*/\/\/\/\/\/\/\/\/\/\/\/\Valar_Morghulis./\/\/\/\/\/\/\/\/\/\/\/\

		FileName:	d3dsystem.cpp
		Usage:		普段使わないＤ3Ｄの機能を別として、
					動かないようにする。
		Date:


\/\/\/\/\/\/\/\/\/\/\/\/\/Valar_Dohaeris.\/\/\/\/\/\/\/\/\/\/\/\/*/

#include"common.h"

LPDIRECT3D9 D3DCInterface = NULL;
LPDIRECT3DDEVICE9 D3DCDevice = NULL;

bool D3DInit(HWND hWnd) {
	//Direct3Dインターフェースの取得
	D3DCInterface = Direct3DCreate9(D3D_SDK_VERSION);
	//取得失敗確認など
	if (D3DCInterface == NULL) {
		DebugMB("Direct3Dインターフェースの取得>>>失敗");
	}

	//Direct3Dデバイスの取得
	D3DPRESENT_PARAMETERS d3dPP = {};							//Ｄ3Ｄプレゼントパラメーターを作る
	d3dPP.BackBufferWidth = SCREEN_WIDTH;						//バックバッファの横を設定
	d3dPP.BackBufferHeight = SCREEN_HEIGHT;						//バックバッファの縦を設定
	d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;					//バックバッファの表現式を設定
	d3dPP.BackBufferCount = 1;									//バックバッファの枚数を設定
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;					//バックバッファの交換時の効果
	d3dPP.Windowed = true;										//ウィンドウモード、1→ウィンドウ　0→フルスクリーン
	d3dPP.EnableAutoDepthStencil = true;						//深度バッファ、ステンシルバッファを有効にする
	d3dPP.AutoDepthStencilFormat = D3DFMT_D16;					//デプス16ビットに設定
	d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//フルスクリーン時のヘルツ数を適応
	d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//INTERVAL1と一緒、精度が悪い
	//IMMEDIATE




	HRESULT hr = D3DCInterface->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dPP,
		&D3DCDevice);

	D3DCDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	D3DCDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	D3DCDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
/*
	D3DCDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	D3DCDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);*/
	//D3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(0,0,255,255));



	// アルファ・ブレンディングを行う
	D3DCDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//今から描画するＲＧＢ*今から描画するα✛画面のＲＧＢ*（1-今から描画するα）	※値は1～0

	// 透過処理を行う
	D3DCDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//SRC＝ソースのブレンドパラメータをαに書ける
	D3DCDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//DEST＝デスティネーション（画面）画面のＲＧＢから逆で書く（INVSRC）
	D3DCDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//	D3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);


	if (!SUCCEEDED(hr)) {
		DebugMB("Direct3Dデバイスの取得>>>失敗");
		return false;
	}

	return true;

}
void D3DUninit(void) {
	SAFE_RELEASE(D3DCInterface);
	SAFE_RELEASE(D3DCDevice);
}
LPDIRECT3DDEVICE9 GetDevice() {
	return D3DCDevice;
}
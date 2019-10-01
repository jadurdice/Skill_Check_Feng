/*/\/\/\/\/\/\/\/\/\/\/\/\Valar_Morghulis./\/\/\/\/\/\/\/\/\/\/\/\
 /\
 ||
 ||
 ||
/\/\
 ||
 Ｏ
\/\/\/\/\/\/\/\/\/\/\/\/\/Valar_Dohaeris.\/\/\/\/\/\/\/\/\/\/\/\/*/


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//ライブラリにリンク
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



#ifndef _MAIN_H_
#define _MAIN_H_

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//インクルード
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include"common.h"
#include"Player.h"
#include"Game.h"
#include"Sprite.h"
#include"texture.h"
#include"system_timer.h"
#include"debug_font.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//マグロ
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define CLASS_NAME		"GameWindow"		
#define WND_CAPTION		"Suicidal Daredevil"		//キャプション名前
#define FPS_MEASUREMENT_TIME (1.0f)

#define WND_STYLE_CUSTOM	(WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX))
											//ウィンドウスタイルのカスタマイズ
//ＸとＹとＺとＲＨＷを持つ頂点データを表す

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//プロトタイプ宣言
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool Initialize(HWND hWnd, HINSTANCE  hInstance);		//初期化関数
void Finalize(void);			//終了関数
void Update();				//ゲームループ処理関数
void Draw(void);				//ゲームループ描画関数
int GetFrame();




#endif
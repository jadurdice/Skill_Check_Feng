//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <Windows.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{

	//bgm
	B_TITLE = 0,		// BGM0
	B_STAGEONE,		// BGM0
	B_RANKING,			//ランキング
	B_BOSS1,			//ボス1
	B_BOSS2,			//ボス2

	//se_system
	SE_CAUTION,			//警告
	SE_CLEAR,
	SE_COUNTDOWN,
	SE_ENEMYSPAWN,
	SE_ITEMGET,
	SE_DECIDE,



	//se_game
	SE_BOSS1SURROUND,	//ボス1環境音
	SE_BOSS2SURROUND,	//ボス1環境音
	SE_BIGEXPLOSION,
	SE_MACHINEGUN,		//MG
	SE_DAMAGE,			//ダメージ
	SE_SHOT,		// 弾発射音
	SE_EXPLOSION,	// 爆発音
	SE_MISSILE,


	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
#endif

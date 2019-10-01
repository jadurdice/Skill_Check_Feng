//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <Windows.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{

	//bgm
	B_TITLE = 0,		// BGM0
	B_STAGEONE,		// BGM0
	B_RANKING,			//�����L���O
	B_BOSS1,			//�{�X1
	B_BOSS2,			//�{�X2

	//se_system
	SE_CAUTION,			//�x��
	SE_CLEAR,
	SE_COUNTDOWN,
	SE_ENEMYSPAWN,
	SE_ITEMGET,
	SE_DECIDE,



	//se_game
	SE_BOSS1SURROUND,	//�{�X1����
	SE_BOSS2SURROUND,	//�{�X1����
	SE_BIGEXPLOSION,
	SE_MACHINEGUN,		//MG
	SE_DAMAGE,			//�_���[�W
	SE_SHOT,		// �e���ˉ�
	SE_EXPLOSION,	// ������
	SE_MISSILE,


	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
#endif

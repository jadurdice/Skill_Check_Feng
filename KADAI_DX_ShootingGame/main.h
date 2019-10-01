/*/\/\/\/\/\/\/\/\/\/\/\/\Valar_Morghulis./\/\/\/\/\/\/\/\/\/\/\/\
 /\
 ||
 ||
 ||
/\/\
 ||
 �n
\/\/\/\/\/\/\/\/\/\/\/\/\/Valar_Dohaeris.\/\/\/\/\/\/\/\/\/\/\/\/*/


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//���C�u�����Ƀ����N
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



#ifndef _MAIN_H_
#define _MAIN_H_

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�C���N���[�h
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include"common.h"
#include"Player.h"
#include"Game.h"
#include"Sprite.h"
#include"texture.h"
#include"system_timer.h"
#include"debug_font.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�}�O��
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define CLASS_NAME		"GameWindow"		
#define WND_CAPTION		"Suicidal Daredevil"		//�L���v�V�������O
#define FPS_MEASUREMENT_TIME (1.0f)

#define WND_STYLE_CUSTOM	(WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX))
											//�E�B���h�E�X�^�C���̃J�X�^�}�C�Y
//�w�Ƃx�Ƃy�Ƃq�g�v�������_�f�[�^��\��

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�v���g�^�C�v�錾
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool Initialize(HWND hWnd, HINSTANCE  hInstance);		//�������֐�
void Finalize(void);			//�I���֐�
void Update();				//�Q�[�����[�v�����֐�
void Draw(void);				//�Q�[�����[�v�`��֐�
int GetFrame();




#endif
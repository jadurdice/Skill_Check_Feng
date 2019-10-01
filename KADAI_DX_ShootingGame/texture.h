#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include"common.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�}�O��
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define TEXTURESLOT_MAX (128)

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�\���̐錾
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef struct TextureData_tag{
	char fileName[FILENAME_MAX];
	int tWidth;
	int tHeight;
	LPDIRECT3DTEXTURE9 pTexture;
}TextureSlot;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�v���g�^�C�v�錾
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//�ǂݍ��ރe�N�X�`���t�@�C���̗\��
//const char*	fileName	�t�@�C����
//int			fileW		�t�@�C���̕�
//int			fileH		�t�@�C���̍���
//�߂�l						�\��ԍ�(ID)
int TextureSetLoadFile(
	const char* fileName,
	int fileW, int fileH);

//�t�@�C���̓ǂݍ���
//�߂�l		�ǂݍ��߂Ȃ�������
int TextureLoad(void);

//�e�N�X�`���̉���֐��i�����j
//int		textureIDs[]	����������h�c���������z��̐擪�A�h���X
//int		length			�z��̒���
void TextureDelete(int textureIDs[], int length);

//�e�N�X�`���̉���֐��i�S���j
void textureDelete(void);

//�e�N�X�`���̎擾
//int		textureID	�\��ԍ�
//�߂�l		�G���[��NULL�A���̑��̓e�N�X�`��
LPDIRECT3DTEXTURE9 GetTexture(int textureID);

//�e�N�X�`���̉�����Ԃ�
//int		textureID		�\��ԍ�
//�߂�l						�e�N�X�`���̉���
int GetTextureWidth(int textureID);

//�e�N�X�`���̍�����Ԃ�
//int		textureID		�\��ԍ�
//�߂�l		�e�N�X�`���̍���
int GetTextureHeight(int textureID);



#endif // !_TEXTURE_H_

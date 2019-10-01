#define _CRT_SECURE_NO_WARNINGS

#include<string.h>
#include"d3dsystem.h"
#include"texture.h"

TextureSlot TextureData[TEXTURESLOT_MAX] = {};

int TextureSetLoadFile(const char* fileName, int fileW, int fileH) {

	//�����t�@�C������T��	
	for (int i = 0; i < TEXTURESLOT_MAX; i++)
	{
		if (!strcmp(TextureData[i].fileName, fileName)) {
			//�����t�@�C���������݂��Ă���
			//�������`�F�b�N
			if (TextureData[i].tHeight == fileH && TextureData[i].tWidth == fileW) {
				//����������
				//DebugMB("%d�Ԗڂ̃e�N�X�`���Ƃ͓����t�@�C���Ǝv���܂��B",i);
				return i;
			}
		}
	}

	//�V�K�o�^
	for (int i = 0; i < TEXTURESLOT_MAX; i++)
	{
		//�g�p����Ă��Ȃ��ꏊ��T��
		if (TextureData[i].fileName[0] != '\0') {
			//�g���Ă���̂ŃX�L�b�v
			continue;
		}

		//�g���Ă��Ȃ��̂œo�^����
		strcpy(TextureData[i].fileName, fileName);
		TextureData[i].tWidth = fileW;
		TextureData[i].tHeight = fileH;
		return i;
	}

	//�`�F�b�N�I�������A�S���Ԃ��Ȃ���������A�g���e�N�X�`���̃T�C�Y�͏�����z���Ă���
	DebugMB("�e�N�X�`���̗e�ʃI�[�o�[");
	return -1;
}
int TextureLoad(void) {
	HRESULT hr;

	LPDIRECT3DDEVICE9 device = GetDevice();

	if (device == NULL) {
		return -1;
	}

	int errorCnt = 0;
	for (int i = 0; i < TEXTURESLOT_MAX; i++)
	{
		if (TextureData[i].fileName[0] == '\0') {
			//�t�@�C�������Ȃ��ꍇ�ǂݍ��܂Ȃ�
			continue;
		}
		if (TextureData[i].pTexture != NULL) {
			//�����ǂݍ��܂�Ă���
			continue;
		}

		//�t�@�C����ǂݍ���
		hr = D3DXCreateTextureFromFile(device,TextureData[i].fileName, &TextureData[i].pTexture);

		if (FAILED(hr)) {
			//�ǂݍ��ݎ��s�̃t�@�C�������o��
			DebugMB("%s�̓ǂݍ��݂͎��s����",TextureData[i].fileName);
			errorCnt += 1;
		}
	}
	return errorCnt;
}
void TextureDelete(int textureIDs[], int count) {
	for (int i = 0; i < count; i++)
	{
		if (TextureData[textureIDs[i]].pTexture == NULL) {
			continue;
		}
		TextureData[textureIDs[i]].pTexture->Release();
		TextureData[textureIDs[i]].pTexture = NULL;
		TextureData[textureIDs[i]].fileName[0] = '\0';
		TextureData[textureIDs[i]].tHeight = 0;
		TextureData[textureIDs[i]].tWidth = 0;
	}
}
void textureDelete(void) {
	for (int i = 0; i < TEXTURESLOT_MAX; i++)
	{
		if (TextureData[i].pTexture == NULL) {
			continue;
		}
		TextureData[i].pTexture->Release();
		TextureData[i].pTexture = NULL;
		TextureData[i].fileName[0] = '\0';
		TextureData[i].tHeight = 0;
		TextureData[i].tWidth = 0;
	}
}
LPDIRECT3DTEXTURE9 GetTexture(int textureID) {
	return TextureData[textureID].pTexture;
}
int GetTextureWidth(int textureID) {
	return TextureData[textureID].tWidth;
}
int GetTextureHeight(int textureID) {
	return TextureData[textureID].tHeight;
}
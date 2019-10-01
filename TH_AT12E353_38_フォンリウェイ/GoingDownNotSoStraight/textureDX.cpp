#define _CRT_SECURE_NO_WARNINGS

#include<string.h>
#include"d3dsystem.h"
#include"texture.h"

TextureSlot TextureData[TEXTURESLOT_MAX] = {};

int TextureSetLoadFile(const char* fileName, int fileW, int fileH) {

	//同じファイル名を探す	
	for (int i = 0; i < TEXTURESLOT_MAX; i++)
	{
		if (!strcmp(TextureData[i].fileName, fileName)) {
			//同じファイル名が存在している
			//幅高さチェック
			if (TextureData[i].tHeight == fileH && TextureData[i].tWidth == fileW) {
				//幅高さ同じ
				//DebugMB("%d番目のテクスチャとは同じファイルと思います。",i);
				return i;
			}
		}
	}

	//新規登録
	for (int i = 0; i < TEXTURESLOT_MAX; i++)
	{
		//使用されていない場所を探す
		if (TextureData[i].fileName[0] != '\0') {
			//使われているのでスキップ
			continue;
		}

		//使われていないので登録する
		strcpy(TextureData[i].fileName, fileName);
		TextureData[i].tWidth = fileW;
		TextureData[i].tHeight = fileH;
		return i;
	}

	//チェック終わったら、全部返しないだったら、使うテクスチャのサイズは上限を越えている
	DebugMB("テクスチャの容量オーバー");
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
			//ファイル名がない場合読み込まない
			continue;
		}
		if (TextureData[i].pTexture != NULL) {
			//もう読み込まれている
			continue;
		}

		//ファイルを読み込む
		hr = D3DXCreateTextureFromFile(device,TextureData[i].fileName, &TextureData[i].pTexture);

		if (FAILED(hr)) {
			//読み込み失敗のファイル名を出る
			DebugMB("%sの読み込みは失敗した",TextureData[i].fileName);
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
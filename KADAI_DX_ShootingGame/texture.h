#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include"common.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//マグロ
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define TEXTURESLOT_MAX (128)

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//構造体宣言
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef struct TextureData_tag{
	char fileName[FILENAME_MAX];
	int tWidth;
	int tHeight;
	LPDIRECT3DTEXTURE9 pTexture;
}TextureSlot;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//プロトタイプ宣言
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//読み込むテクスチャファイルの予約
//const char*	fileName	ファイル名
//int			fileW		ファイルの幅
//int			fileH		ファイルの高さ
//戻り値						予約番号(ID)
int TextureSetLoadFile(
	const char* fileName,
	int fileW, int fileH);

//ファイルの読み込み
//戻り値		読み込めなかった数
int TextureLoad(void);

//テクスチャの解放関数（部分）
//int		textureIDs[]	解放したいＩＤが入った配列の先頭アドレス
//int		length			配列の長さ
void TextureDelete(int textureIDs[], int length);

//テクスチャの解放関数（全部）
void textureDelete(void);

//テクスチャの取得
//int		textureID	予約番号
//戻り値		エラーはNULL、その他はテクスチャ
LPDIRECT3DTEXTURE9 GetTexture(int textureID);

//テクスチャの横幅を返す
//int		textureID		予約番号
//戻り値						テクスチャの横幅
int GetTextureWidth(int textureID);

//テクスチャの高さを返す
//int		textureID		予約番号
//戻り値		テクスチャの高さ
int GetTextureHeight(int textureID);



#endif // !_TEXTURE_H_

#ifndef _ITEM_H_
#define _ITEM_H_
#include"Collision.h"

#define ITEMMAX		(256)

enum ItemGenre {
	I_ScoreS = 0,
	I_ScoreM,
	I_ScoreL,
	I_Power,
	I_Missile,
	I_1UP,
	I_Count
};

class Item
{
public:
	void	SetItem(D3DXVECTOR2 setPos,int setGenre);
	void	SetTexNo(int tex);
	void	UpdateItem();
	void	DrawItem();
	void	PickUpThis();
	

	void			ItemDestroy();

	CircleCol*		GetCollision();
	bool			GetItemEnable();
	int				GetItemGenre();

private:
	bool			isEnable;

	int				genre;
	float			scale;

	unsigned int	texNo;
	D3DXVECTOR2		pos;
	CircleCol		col;


	const float defScale = 12.0f;

};



void InitItem();
void UninitItem();
void UpdateItem();
void DrawItem();

Item* GetItem(int no);

void ItemCreate(D3DXVECTOR2 ins,int genre);
void CheckItemGenre(D3DXVECTOR2 ins);
int GetGenreValue(int genre);
#endif
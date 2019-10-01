#ifndef _BULLET_H_
#define _BULLET_H_

#define BULLETMAX	(512)

#define HOMINGFORCE	(75.0f)

#define DEFMOVSPD	(2.0f)

#include"Collision.h"

enum Genre {
	B_Normal = 0,
	B_Homing,
	B_Count,
};

class Bullet
{
public:
	Bullet();

	unsigned int	bulletTexNo;
	D3DXVECTOR2		bulletPos;
	D3DXVECTOR2		bulletVelocity;

	CircleCol		bulletCol;

	char			shootBy;

	int				bulletDamege;

	float			bulletMoveSpeed;
	float			bulletAngle;

	virtual void	BulletUpdate();
	virtual void	ShootThis(float x, float y,float angle, float speed);
	virtual void	DrawBullet();
	void			BulletDestroy();
	int				GetBulletDmg();

	virtual void	MoveBullet();

	CircleCol*		GetCollision();

	bool			isEnable;
	bool			GetBulletEnable();


private:

};

class Homing : public Bullet {
	
public :

	void	BulletUpdate();
	void	ShootThis(D3DXVECTOR2 insPos, D3DXVECTOR2* target, int lifeTime, int stopTime, float speed);
	void	DrawBullet();
	   
private:

	CircleCol	searchCol;
	D3DXVECTOR2 *targetPos;
	D3DXVECTOR2 bulletOldPos;
	float		bulletSpeed;

	int		bulletLifeTime;
	int		bulletStopTime;

};

void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();

Bullet* GetBullet(int genre, int no);
D3DXVECTOR2* GetNearestBullet();
int GetBulletMax();

void BulletCreate(float insX, float insY,float angle, float speed, char shootBy);
void HomingCreate(D3DXVECTOR2 insPos, D3DXVECTOR2 * target, int lifeTime, int stopTime, float speed, char shootBy);
void WayBulletCreate(D3DXVECTOR2 insPos,D3DXVECTOR2 targetPos,int value,int degree, float speed, char shootBy);



void ClearBullet();


#endif
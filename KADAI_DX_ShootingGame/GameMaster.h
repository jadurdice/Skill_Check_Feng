#ifndef _GAMEMASTER_H_
#define _GAMEMASTER_H_

#include"Bullet.h"
#include"Enemy.h"
#include"Player.h"
#include"Item.h"
#include"Collision.h"

void checkBullet2Enemy(Bullet *a, Enemy *b);
void checkBullet2Player(Bullet *a, Player *b);
void checkEnemy2Player(Player *a, Enemy *b);
void checkHoming2Bullet(Bullet *a, Bullet *b);
void checkItem2Player(Item *a,Player *b);

#endif
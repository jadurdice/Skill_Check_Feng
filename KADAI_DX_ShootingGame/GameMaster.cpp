#include"GameMaster.h"
#include"score.h"


void checkBullet2Enemy(Bullet *a,Enemy *b) {
	if (isCircle2Circle(a->GetCollision(), b->GetCollision())) {
		b->DamegeThis(GetActionPlayer()->GetPower());

		a->BulletDestroy();
		AddScore(1);

	}
}
void checkBullet2Player(Bullet * a, Player * b)
{
	if (isCircle2Circle(a->GetCollision(), b->GetCollision())) {
		a->BulletDestroy();
		b->PlayerDestroy();

	}

	CircleCol temp = *b->GetCollision();
	temp.radius *= 3.5f;

	if (isCircle2Circle(a->GetCollision(), &temp)) {
		AddScore(1);
	}

}
void checkEnemy2Player(Player *a, Enemy *b) {
	if (isCircle2Circle(a->GetCollision(), b->GetCollision())) {
		a->PlayerDestroy();
	}
}

void checkHoming2Bullet(Bullet *a, Bullet *b) {
	if (isCircle2Circle(a->GetCollision(), b->GetCollision())) {
		b->BulletDestroy();
	}
}

void checkItem2Player(Item *a, Player *b){
	CircleCol temp = *b->GetCollision();
	temp.radius *= 3.5f;

	if (isCircle2Circle(a->GetCollision(), &temp)) {
		a->PickUpThis();
	}
}
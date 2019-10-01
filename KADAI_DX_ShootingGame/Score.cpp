#include "score.h"
#include"common.h"
#include"HighScore.h"

class Number
{
public:
	void SetThisNumber(int num);
	void SetThisPos(D3DXVECTOR2 pos);

	int GetThisNumber();
	D3DXVECTOR2 GetThisPos();
private:

	int thisNo;
	D3DXVECTOR2 noPos;

};


void Number::SetThisNumber(int num)
{
	thisNo = num;
}

void Number::SetThisPos(D3DXVECTOR2 pos)
{
	noPos = pos;
}

int Number::GetThisNumber()
{
	return thisNo;
}

D3DXVECTOR2 Number::GetThisPos()
{
	return noPos;
}


class Score
{
public:

	void InitScore(int texNo);
	void UpdateScore();
	void DrawScore();

	void SetTempScore(int addNum);
	int GetScore();
	void ResetScore();

private:

	int totalScore;
	int tempScore;
	Number slot[SCOREINGIDMAX];
	unsigned int texNo;

	int frameCnt;

};



void Score::InitScore(int setTexNo)
{
	texNo = setTexNo;
	for (int i = 0; i < SCOREINGIDMAX; i++)
	{
		slot[i].SetThisPos({SCORESTARTX+ 30.0f*i, 0.0f});
	}
}

void Score::UpdateScore()
{
	if (tempScore != 0) {
		for (int i = 0; i < 5; i++)
		{
			if (tempScore >= (pow(100, i))) {
				totalScore += (pow(100, i));
				tempScore -= (pow(100, i));
			}
		}
	}
	SetRoundScore(tempScore + totalScore);
	int passToNum = totalScore;
	for (int i = 0; i < SCOREINGIDMAX; i++)
	{
		slot[(SCOREINGIDMAX - i - 1)].SetThisNumber(passToNum % 10);
		passToNum /= 10;
		if(passToNum == 0){
			break;
		}
	}

}

void Score::DrawScore()
{

	for (int i = 0; i < SCOREINGIDMAX; i++)
	{
		float uNow, vNow;

		uNow = slot[i].GetThisNumber() % 10;
		vNow = 3;

		uNow *= 0.1f * 567;
		vNow *= 0.25f*322;	


		if (tempScore > 0) {
				SetColor(0, 255, 0, 255);
		}

		DrawSpriteRotPlg(
			texNo,
			slot[i].GetThisPos().x, slot[i].GetThisPos().y,
			uNow, vNow,
			0.1f*567, 0.25f * 322,
			0,
			0.5f, 0.5f,
			0.5f, 0.5f
		);
	}
	SetColor(255, 255, 255, 255);
}

void Score::SetTempScore(int addNum) {
	tempScore += addNum;
}

int Score::GetScore()
{
	return tempScore + totalScore;
}

void Score::ResetScore()
{
	totalScore = 0;
	tempScore = 0;
	for (int i = 0; i < SCOREINGIDMAX; i++)
	{
		slot[(SCOREINGIDMAX - i - 1)].SetThisNumber(0);
	}

}



class Power {
public:

	void InitPower(int texNo);
	void UpdatePower();
	void DrawPower();

private:

	Number slot[POWINGIDMAX];
	unsigned int texNo;
};

void Power::InitPower(int setTexNo)
{
	texNo = setTexNo;
	for (int i = 0; i < POWINGIDMAX; i++)
	{
		slot[i].SetThisPos({POWSTARTX + 30.0f*i, 0.0f });
	}
}

void Power::UpdatePower()
{
	int passToNum = GetActionPlayer()->GetRawPower();
	for (int i = 0; i < POWINGIDMAX; i++)
	{
		slot[(POWINGIDMAX - i - 1)].SetThisNumber(passToNum % 10);
		passToNum /= 10;
	}
}

void Power::DrawPower()
{
	for (int i = 0; i < POWINGIDMAX; i++)
	{
		float uNow, vNow;

		uNow = slot[i].GetThisNumber() % 10;
		vNow = 3;

		uNow *= 0.1f * 567;
		vNow *= 0.25f * 322;
	
		DrawSpriteRotPlg(
			texNo,
			slot[i].GetThisPos().x, slot[i].GetThisPos().y,
			uNow, vNow,
			0.1f * 567, 0.25f * 322,
			0,
			0.5f, 0.5f,
			0.5f, 0.5f
		);
	}
	SetColor(255, 255, 255, 255);

}

class Missile {
public:

	void InitMissile(int texNo);
	void UpdateMissile();
	void DrawMissile();

private:

	Number slot[MISSILEINGIDMAX];
	int maxMissile;
	int nowMissile;
	unsigned int texNo;
};

void Missile::InitMissile(int setTexNo)
{
	texNo = setTexNo;
	maxMissile = GetActionPlayer()->GetMissileMax();
	for (int i = 0; i < MISSILEINGIDMAX; i++)
	{
		slot[i].SetThisPos({ MISSILESTARTX + 30.0f*i, 0.0f });
	}
}

void Missile::UpdateMissile()
{
	nowMissile = GetActionPlayer()->GetMissileNow();
	maxMissile = GetActionPlayer()->GetMissileMax();

	int passToNum = nowMissile;

	for (int i = 0; i < MISSILEINGIDMAX; i++)
	{
		slot[(MISSILEINGIDMAX - i - 1)].SetThisNumber(passToNum % 10);
		passToNum /= 10;
	}
}

void Missile::DrawMissile()
{
	for (int i = 0; i < MISSILEINGIDMAX; i++)
	{
		float uNow, vNow;

		uNow = slot[i].GetThisNumber() % 10;
		vNow = 3;

		uNow *= 0.1f * 567;
		vNow *= 0.25f * 322;


		float redFactor, greenFactor, maxPercent;

		maxPercent = (float)nowMissile / (float)maxMissile;

		if (maxPercent < 0.5f) {
			redFactor = 1.0f;
			greenFactor = maxPercent * 2;
		}
		else {
			redFactor = 1.0f - ((maxPercent-0.5f)*2);
			greenFactor = 1.0f;
		}

		SetColor(255*redFactor,255*greenFactor,0,255);

		DrawSpriteRotPlg(
			texNo,
			slot[i].GetThisPos().x, slot[i].GetThisPos().y,
			uNow, vNow,
			0.1f * 567, 0.25f * 322,
			0,
			0.5f, 0.5f,
			0.5f, 0.5f
		);
	}
	SetColor(255, 255, 255, 255);

}

class UI {
private:
	Score showScore;
	Power showPower;
	Missile showMissile;
	Number life;

	int TexNo;

public:
	void Init() {
		TexNo = GetTextTexNo();
		showScore.InitScore(TexNo);
		showPower.InitPower(TexNo);
		showMissile.InitMissile(TexNo);
		life.SetThisNumber(GetActionPlayer()->GetLife() % 10);
		life.SetThisPos({ LIVESSTARTX,0.0f });
		ResetScore();
	};
	void UnInit() {
	};
	void Update() {
		showPower.UpdatePower();
		showScore.UpdateScore();
		showMissile.UpdateMissile();
		life.SetThisNumber(GetActionPlayer()->GetLife() % 10);
	};
	void Draw() {
		showPower.DrawPower();
		showScore.DrawScore();
		showMissile.DrawMissile();

		float uNow, vNow;

		uNow = life.GetThisNumber() % 10;
		vNow = 3;

		uNow *= 0.1f * 567;
		vNow *= 0.25f * 322;

		DrawSpriteRotPlg(
			TexNo,
			life.GetThisPos().x, life.GetThisPos().y,
			uNow, vNow,
			0.1f * 567, 0.25f * 322,
			0,
			0.5f, 0.5f,
			0.5f, 0.5f
		);

	};

	void AddScore(int addNum) {
		showScore.SetTempScore(addNum);
	}

	void ResetScore() {
		showScore.ResetScore();
	}
};

UI conUI;
unsigned int bgTexNo;
unsigned int textTexNo;
unsigned int imageTexNo[4];

void InitUI()
{

	textTexNo = TextureSetLoadFile("asset/texture/text.png", 567, 322);

	bgTexNo = TextureSetLoadFile("asset/texture/uibg.png", 1731, 236);
	imageTexNo[0] = TextureSetLoadFile("asset/texture/scoreUi.png", 110, 58);
	imageTexNo[1] = TextureSetLoadFile("asset/texture/powerUi.png", 116, 59);
	imageTexNo[2] = TextureSetLoadFile("asset/texture/missileUi.png", 124, 59);
	imageTexNo[3] = TextureSetLoadFile("asset/texture/livesUi.png", 200, 57);
	conUI.Init();
	
}

void UninitUI()
{
	
}

void UpdateUI()
{
	conUI.Update();
}

void DrawUI()
{
	DrawSpriteCut(bgTexNo, 0.0f, -236 + 0.1f*SCREEN_HEIGHT, 0, 0, 1731, 236);
	DrawSpriteCut(imageTexNo[0], 15.0f, 10.0f, 0, 0, 110, 58);
	DrawSpriteCut(imageTexNo[1], POWSTARTX - 112, 10.0f, 0, 0, 116, 59);
	DrawSpriteCut(imageTexNo[2], MISSILESTARTX - 120, 10.0f, 0, 0, 124, 59);
	DrawSpriteCut(imageTexNo[3], LIVESSTARTX - 200, 10.0f, 0, 0, 200, 57);
	conUI.Draw();

}

void AddScore(int addNum) {
	conUI.AddScore(addNum);
}

void ResetScore() {
	conUI.ResetScore();
}
int GetTextTexNo() {
	return textTexNo;
}
void GetScore() {
	
}
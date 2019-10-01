#define _CRT_SECURE_NO_WARNINGS
#include"HighScore.h"
#include"Fade.h"
#include"score.h"
#include"d3dsystem.h"
#include"common.h"
#include"BackGround.h"
#include"sound.h"

bool isNewRanker;
static int nowRoundScore;
unsigned int hsTextTexNo;
unsigned int hsTitleTexNo;
float rankX[5];
int newRank;
int showRecord[5];
int hsFrameCnt;

FILE* rankData;


void InitHS() {

	hsTitleTexNo = TextureSetLoadFile("asset/texture/highscore.png", 609, 167);

	if ((rankData = fopen("asset/ranking.txt", "r")) == NULL) {
		int a = 0;
		a = a;
	};

	StopSound(B_BOSS1);
	StopSound(B_BOSS2);
	StopSound(B_STAGEONE);

	for (int i = 0; i < SHOWRANKMAX; i++)
	{
		fscanf(rankData, "%d", &showRecord[i]);
		fscanf(rankData," ");
	}
	fclose(rankData);


	for (int i = 0; i < 5; i++)
	{
		rankX[i] = SCREEN_WIDTH + 70.0f*i;
	}

	SetFade(60,D3DCOLOR_RGBA(0,0,0,0),false);
	if (nowRoundScore > showRecord[4]) {
		isNewRanker = true;
		ScoreSorting(SHOWRANKMAX-1);
	}

	hsTextTexNo = GetTextTexNo();
	BackInit();
	PlaySound(B_RANKING);
}
void UnInitHS() {
	rankData = fopen("asset/ranking.txt", "w");

	for (int i = 0; i < SHOWRANKMAX; i++)
	{
		fprintf(rankData, "%d", showRecord[i]);
		fprintf(rankData, " ");
	}
	fclose(rankData);
	BackUnInit();
	StopSound(B_RANKING);
}
void UpdateHS() {
	hsFrameCnt += 1;

	for (int i = 0; i < 5; i++)
	{
		if (rankX[i] > RANKINGSTARTX) {
			rankX[i] -= 20.0f;
		}
		else {
			rankX[i] = RANKINGSTARTX;
		}
	}

	if (Keyboard_IsTrigger(DIK_K)) {
		SetTrailEnable();
		SetScene(S_Title);
	}
	BackUpdate();
}
void DrawHS() {
	BackDraw();

	DrawSpriteCut(hsTitleTexNo, (SCREEN_WIDTH - 610)*0.5f, (-25.0f), 0, 0, 609, 167);

	for (int i = 0; i < SHOWRANKMAX; i++)
	{
		float uNow, vNow;

		uNow = (i + 1);
		vNow = 3;

		uNow *= 0.1f * 567;
		vNow *= 0.25f * 322;

		if (isNewRanker && newRank == i)
		SetColor(255,255,50,255* ((hsFrameCnt/60)%2));

		DrawSpriteRotPlg(
			hsTextTexNo,
			rankX[i],
			RANKINGSTARTY + 100 * i,
			uNow, vNow,
			0.1f * 567, 0.25f * 322,
			0,
			0.5f, 0.5f,
			1.0f, 1.0f
		);

		SetColor(255, 255, 255, 255);

		int passNum = showRecord[i];

		for (int j = 9; j >= 0; j--)
		{
			int tempX = rankX[i] + 70 * 2 + 70.0f*j;
			int tempY = RANKINGSTARTY + 100 * i;

			float uNow, vNow;

			uNow = passNum % 10;
			vNow = 3;

			uNow *= 0.1f * 567;
			vNow *= 0.25f * 322;

			DrawSpriteRotPlg(
				hsTextTexNo,
				tempX, tempY,
				uNow, vNow,
				0.1f * 567, 0.25f * 322,
				0,
				0.5f, 0.5f,
				1.0f, 1.0f
			);

			passNum /= 10;
		}

	}

}

void DefaltScore() {

}

void SetRoundScore(int score) {
	nowRoundScore = score;
}

void ScoreSorting(int turn)
{
	int checkScore = showRecord[turn];
	if (nowRoundScore > checkScore)
	{
		showRecord[turn + 1] = checkScore;
		if (turn == 0)
		{
			showRecord[0] = nowRoundScore;
			newRank = 0;
			return;
		}
		else
		{
			ScoreSorting(turn - 1);
		}

	}
	else
	{
		showRecord[turn + 1] = nowRoundScore;
		newRank = turn + 1;
	}
}


SceneProc SetupHSScene(void)
{
	SceneProc proc = {
		S_GameOver,
	"HS",
	InitHS,
	UnInitHS,
	UpdateHS,
	DrawHS
	};

	return proc;
}


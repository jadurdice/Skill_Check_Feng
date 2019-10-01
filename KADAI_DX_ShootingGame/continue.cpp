#include"continue.h"
#include"score.h"
#include"input.h"
#include"texture.h"
#include"sound.h"
#include"Fade.h"
#include"Sprite.h"
#include"Bullet.h"
#include"PhaseManeger.h"

unsigned int contiTexNo;
unsigned int numberTexNo;
unsigned int countFrameTexNo;
unsigned int stage1TexNo;
unsigned int fissioncompliteTexNo;
unsigned int cautionTexNo[3];

bool isContinue;
bool isStage;
bool isComplete;
bool isCaution;
float stagePos;
float completeAlpha;
float cautionAlpha;
int stageAlpha;
int ContiCnt;
int stageCnt;
int cautionCnt;

void InitConti() {
	contiTexNo = TextureSetLoadFile("asset/texture/continue.png", 487, 136);
	stage1TexNo = TextureSetLoadFile("asset/texture/stage1.png", 580, 300);
	countFrameTexNo = TextureSetLoadFile("asset/texture/countFrame.png",189,259);
	fissioncompliteTexNo = TextureSetLoadFile("asset/texture/missioncomplete.png",595,318);
	cautionTexNo[0 ]= TextureSetLoadFile("asset/texture/caution1.png", 1280, 720);
	cautionTexNo[1] = TextureSetLoadFile("asset/texture/caution2.png", 1280, 720);
	cautionTexNo[2] = TextureSetLoadFile("asset/texture/caution3.png", 1000, 79);
	numberTexNo = GetTextTexNo();
	isContinue = false;
	isStage = true;
	isComplete = false;
	stagePos = SCREEN_WIDTH * 0.3f;
	stageAlpha = 0;
	completeAlpha = 0.0f;
}
void UninitConti() {
}
void UpdateConti() {

	if (isStage) {
		stageCnt += 1;
		if (stageCnt < 255) {
			stageAlpha += 1;
			stagePos = GameSystem::Lerp(stagePos, STAGEX, DELTATIME);
		}
		if (stageCnt > 530) {
			stageAlpha -= 4;
			stagePos = GameSystem::Lerp(stagePos, SCREEN_WIDTH, DELTATIME);
			if (stageAlpha <= 0) {
				isStage = false;
				stageCnt = 0;
			}
		}
	}

	if (isComplete) {
		if (completeAlpha < 1.0f) {
			completeAlpha += 0.01f;
			if (completeAlpha >= 1.0f) {
				completeAlpha = 1.0f;
				GameSystem::ShakeStart(5, 5.0f);
			}
		}
	}

	if (isCaution) {
		cautionCnt += 1;

		cautionAlpha = (1.0f + sinf(DEGREE_TO_RADIAN(cautionCnt*3 + 90)))*0.5f;

		if (cautionCnt > 660*3) {
			cautionCnt = 0;
			isCaution = false;
		}
	}

	if (isContinue) {
		ContiCnt += 1;

		if ((ContiCnt / 120) >= 10) {
			isContinue = false;
			SetScene(S_GameOver);
		}
		if (ContiCnt % 120 == 1) {
			StopSound(SE_COUNTDOWN);
			PlaySound(SE_COUNTDOWN);
		}

		if (Keyboard_IsTrigger(DIK_SPACE)) {
			int temp = ContiCnt / 120;
			temp = (temp + 1)*120;
			ContiCnt = temp;
		}
		if (Keyboard_IsTrigger(DIK_K)) {
			GetActionPlayer()->SetLife(3);
			GetActionPlayer()->respawnCnt = RESPAWNDEF;

			ClearBullet();
			ResetScore();
			SetConti();
		}

	}
}
void DrawConti() {
	if (isComplete) {
		SetColor(255, 255, 255, 255*completeAlpha);
		DrawSpriteRotCenter(fissioncompliteTexNo, SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.3f, 0, 0, 580, 300, 0, 0, 0, 3.0f - 2.0f*completeAlpha, 3.0f - 2.0f*completeAlpha);
	}
	if (isStage) {
		SetColor(255, 255, 255, stageAlpha);
		DrawSpriteCut(stage1TexNo, stagePos,STAGEY, 0, 0, 580, 300);
	}

	if (isCaution) {
		if (cautionCnt < 360) {
			DrawSpriteCut(cautionTexNo[0], 0, 0, 0, 0, cautionCnt * 3.5f, 720);
			DrawSpriteCut(cautionTexNo[2], 0, SCREEN_HEIGHT*0.1f, cautionCnt*3, 0, min(cautionCnt*3.5f, 1280), 40);
			DrawSpriteCut(cautionTexNo[2], 1280 - cautionCnt * 3.5f, SCREEN_HEIGHT*0.8f, -3.0f*cautionCnt, 40, min(cautionCnt*3.5f, 1280), 39);
		}
		else if (cautionCnt >= 360 && cautionCnt < 720) {
			SetColor(255, 255, 255, 255*cautionAlpha);
			DrawSpriteCut(cautionTexNo[0], 0, 0, 0, 0, 1280, 720);
			SetColor(255, 255, 255, 128*(1.0f-cautionAlpha));
			DrawSpriteCut(cautionTexNo[1], 0, 0, 0, 0, 1280, 720);
			SetColor(255, 255, 255, 255);

			DrawSpriteCut(cautionTexNo[2], 0, SCREEN_HEIGHT*0.1f, cautionCnt * 3, 0, min(cautionCnt*3.5f, 1280), 40);
			DrawSpriteCut(cautionTexNo[2], max(0, 1280 - cautionCnt * 3.5f), SCREEN_HEIGHT*0.8f, -3.0f*cautionCnt, 40, min(cautionCnt*3.5f, 1280), 39);

		}
		else {
			DrawSpriteCut(cautionTexNo[0], (cautionCnt - 720)*3.5f, 0, (cautionCnt - 720)*3.5f, 0, 1280, 720);
			DrawSpriteCut(cautionTexNo[2], (cautionCnt - 720)*3.5f, SCREEN_HEIGHT*0.1f, cautionCnt * 3, 0, min(cautionCnt*3.5f, 1280), 40);
			DrawSpriteCut(cautionTexNo[2], 0, SCREEN_HEIGHT*0.8f, -3.0f*cautionCnt, 39, 1280-((cautionCnt - 720)*3.5f), 39);
		}
	}

	if (isContinue) {
		DrawSpriteCut(contiTexNo, (SCREEN_WIDTH - 487)*0.5f, SCREEN_HEIGHT*0.15f, 0, 0, 487, 136);

		float uNow, vNow;

		uNow = 9-(ContiCnt /120);
		vNow = 3;

		uNow *= 0.1f * 567;
		vNow *= 0.25f * 322;

		float countFactor = 1.0f - ((float)(ContiCnt % 120) / (float)120);


		DrawSpriteCut(countFrameTexNo, (SCREEN_WIDTH - 189)*0.5f, (SCREEN_HEIGHT-162)*0.5f, 0, 0, 189, 259);

		SetColor(255 * countFactor, 255 * countFactor, 255 * countFactor, 255);


		DrawSpriteRotPlg(	
			numberTexNo,
			(SCREEN_WIDTH - 56*2.0f)*0.5f, (SCREEN_HEIGHT-70)*0.5f,
			uNow, vNow, 56, 81,0,0,0,2.0f,2.0f
		);


	}
	SetColor(255, 255, 255, 255);
}
void SetConti() {
	isContinue = !isContinue;
	ContiCnt = 0;
	SwitchCounting();
}

void SetComplete() {
	isComplete = true;
	PlaySound(SE_CLEAR);
}
void SetCaution() {
	cautionAlpha = 0.0f;
	cautionCnt = 0;
	isCaution = true;
}
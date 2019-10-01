#include"PhaseManeger.h"
#include"Enemy.h"
#include"Player.h"
#include"EnemySpawner.h"
#include"BackGround.h"
#include"sound.h"
#include"Fade.h"
#include"continue.h"

int frameCnt;
int phaseNow;

class PhaseManeger {
protected:
	class	Phase {
	public:
		Phase() {};
		virtual void Action() = 0;
		virtual Phase* Next() = 0;
		int startFrame;
		int stopLength;
		int totalLength;
		void SetFrame(int start, int stop, int total) {
			startFrame = start;
			stopLength = stop;
			totalLength = total;
		}
		int GetStartFrame() {
			return (startFrame);
		}
		int GetStopLength() {
			return (stopLength);
		}
		int GetLength() {
			return (totalLength);
		}
	};
	class	Phase_0 : public Phase {
	public:
		Phase_0() {
			SetFrame(frameCnt, 600, 600);
			Action();
		};
		void Action() {

		};
		Phase *Next() {
			SetTrailEnable();
			return new  PhaseManeger::Phase_1;
		}

	};
	class	Phase_1 : public Phase {
	public:
		Phase_1() {
			SetFrame(frameCnt, 500, 750);
			Action();
		};
		void Action() {

			SetScrollSpeed(3.5f);

			AttackSetting tempAttack;
			MoveSetting tempMove;

			tempAttack.no = EA_Straight;
			tempAttack.velocity = { -1.0f,0.0f };
			tempAttack.interval = 45;
			tempAttack.speed = 3.0f;

			tempAttack.hp = 10;

			tempMove.no = EM_Straight;
			tempMove.velocity = { -1.0f,1.0f };

			SetSpawner({ 0.75f*SCREEN_WIDTH,0.0f }, tempAttack, tempMove, 100);

			tempMove.velocity = { -1.0f, -1.0f };

			SetSpawner({ 0.75f*SCREEN_WIDTH,SCREEN_HEIGHT }, tempAttack, tempMove, 100);
		};
		Phase *Next() {
			return new  PhaseManeger::Phase_2;
		}
	};
	class	Phase_2 : public Phase {
	public:	Phase_2() {
		SetFrame(frameCnt, 450, 450);
		Action();
	};
			void Action() {
			};
			Phase *Next() {
				return new  PhaseManeger::Phase_3;
			}
	};
	class	Phase_3 : public Phase {
	public:
		Phase_3() {
			SetFrame(frameCnt, 500, 750);
			Action();
		};
		void Action() {

			AttackSetting tempAttack;
			MoveSetting tempMove;

			tempAttack.no = EA_Sector;
			tempAttack.targetPos = &GetActionPlayer()->GetCollision()->pos;
			tempAttack.interval = 90;
			tempAttack.value = 3;
			tempAttack.angle = 30;
			tempAttack.speed = 2.5f;
			tempAttack.hp = 20;

			tempMove.no = EM_Homing;
			tempMove.targetPos = &GetActionPlayer()->GetCollision()->pos;
			tempMove.speed = 0.05f;

			SetSpawner({ SCREEN_WIDTH,0.25f*SCREEN_HEIGHT }, tempAttack, tempMove, 100);

			SetSpawner({ SCREEN_WIDTH,0.75f*SCREEN_HEIGHT }, tempAttack, tempMove, 100);
		};
		Phase *Next() {
			return new  PhaseManeger::Phase_4;
		}
	};
	class	Phase_4 : public Phase {
	public:	Phase_4() {
		SetFrame(frameCnt, 450, 450);
		Action();
	};
			void Action() {
			};
			Phase *Next() {
				return new  PhaseManeger::Phase_5;
			}
	};
	class	Phase_5 : public Phase {
	public:
		Phase_5() {
			SetFrame(frameCnt, 500, 750);
			Action();
		};
		void Action() {

			AttackSetting tempAttack;
			MoveSetting tempMove;

			tempAttack.no = EA_Player;
			tempAttack.interval = 90;
			tempAttack.speed = 2.5f;
			tempAttack.hp = 30;

			tempMove.no = EM_Path;

			tempMove.pathPoint[0] = { 0.9f * SCREEN_WIDTH,0.5f*SCREEN_HEIGHT };
			tempMove.pathPoint[1] = { 0.75f*SCREEN_WIDTH,0.25f*SCREEN_HEIGHT };
			tempMove.pathPoint[2] = { 0.75f*SCREEN_WIDTH,0.5f*SCREEN_HEIGHT };
			tempMove.pathPoint[3] = { 0.75f*SCREEN_WIDTH,0.75f*SCREEN_HEIGHT };
			tempMove.pathPoint[4] = { 0.6f*SCREEN_WIDTH,0.75f*SCREEN_HEIGHT };
			tempMove.pathPoint[5] = { 0.6f*SCREEN_WIDTH,0.5f*SCREEN_HEIGHT };
			tempMove.pathPoint[6] = { 0.6f*SCREEN_WIDTH,0.25f*SCREEN_HEIGHT };
			tempMove.pathPoint[7] = { 0.9f*SCREEN_WIDTH,0.5f*SCREEN_HEIGHT };
			tempMove.pathPoint[8] = { SCREEN_WIDTH,0.5f*SCREEN_HEIGHT };

			tempMove.speed = 3.0f;
			tempMove.moveLength = 75;
			tempMove.lastPoint = 8;

			SetSpawner({ SCREEN_WIDTH,0.5f*SCREEN_HEIGHT }, tempAttack, tempMove, 75);

		};
		Phase *Next() {
			return new  PhaseManeger::Phase_6;
		}
	};
	class	Phase_6 : public Phase {
	public:	Phase_6() {
		SetFrame(frameCnt, 450, 450);
		Action();
	};
			void Action() {
			};
			Phase *Next() {
				return new  PhaseManeger::Phase_7;
			}
	};
	class	Phase_7 : public Phase {
	public:	Phase_7() {
		SetFrame(frameCnt, 500, 750);
		Action();
	};
			void Action() {

				AttackSetting tempAttack;
				MoveSetting tempMove;

				tempAttack.no = EA_Homing;
				tempAttack.interval = 90;
				tempAttack.speed = 1.5f;

				tempAttack.targetPos = &GetActionPlayer()->GetCollision()->pos;
				tempAttack.lifeTime = 450;
				tempAttack.stopTime = 30;
				tempAttack.value = 1;
				tempAttack.hp = 20;

				tempMove.no = EM_Straight;

				tempMove.velocity = { -1.0f,0.3f };

				tempMove.speed = 2.0f;
				tempMove.moveLength = 100;
				tempMove.lastPoint = 8;

				SetSpawner({ 0.9f*SCREEN_WIDTH,0.0f }, tempAttack, tempMove, 100);

				tempMove.velocity = { -1.0f,-0.3f };
				SetSpawner({ 0.9f*SCREEN_WIDTH,SCREEN_HEIGHT }, tempAttack, tempMove, 100);

			};
			Phase *Next() {
				return new  PhaseManeger::Phase_8;
			}
	};
	class	Phase_8 : public Phase {
	public:	Phase_8() {
		SetFrame(frameCnt, 450, 450);
		Action();
	};
			void Action() {
			};
			Phase *Next() {
				return new  PhaseManeger::Phase_9;
			}
	};
	class	Phase_9 : public Phase {
	public:	Phase_9() {
		SetFrame(frameCnt, 750, 1000);
		Action();
	};
			void Action() {

				AttackSetting tempAttack;
				MoveSetting tempMove;

				tempAttack.no = EA_Round;
				tempAttack.interval = 150;
				tempAttack.speed = 1.5f;

				tempAttack.targetPos = &GetActionPlayer()->GetCollision()->pos;
				tempAttack.value = 12;
				tempAttack.hp = 50;

				tempMove.no = EM_Straight;

				tempMove.velocity = { -1.0f,0.0f };

				tempMove.speed = 2.0f;
				tempMove.moveLength = 100;
				tempMove.lastPoint = 8;

				SetSpawner({ SCREEN_WIDTH,0.15f*SCREEN_HEIGHT }, tempAttack, tempMove, 150);

				SetSpawner({ SCREEN_WIDTH,0.75f*SCREEN_HEIGHT }, tempAttack, tempMove, 150);

			};
			Phase *Next() {
				return new  PhaseManeger::Phase_10;
			}


	};
	class	Phase_10 : public Phase {
	public:	Phase_10() {
		SetFrame(frameCnt, 300, 450);
		Action();
	};
			void Action() {
				SetScrollSpeed(0.75f);
			};
			Phase *Next() {
				return new  PhaseManeger::Phase_11;
			}
	};
	class	Phase_11 : public Phase {
	public:	Phase_11() {
		SetFrame(frameCnt, 660, 660);
		Action();
	};
			void Action() {
				SetScrollSpeed(0.75f);
				StopSound(B_STAGEONE);
				PlaySound(SE_CAUTION);
				SetCaution();
			};
			Phase *Next() {
				return new  PhaseManeger::Boss1Intro;
			}
	};

	class	Boss1Intro : public Phase {
	public:	Boss1Intro() {
		SetFrame(frameCnt, 450, 450);
		Action();
	};
			void Action() {

				AttackSetting tempAttack;
				MoveSetting tempMove;

				tempMove.no = EM_Boss1Intro;
				tempMove.speed = 0.25f;

				tempAttack.no = EA_Boss1Idle;
				tempAttack.angle = 90;

				//ボス

				PlaySound(B_BOSS1);
				InitBoss(0);
				SetBossAM(tempAttack, tempMove);

			};
			Phase *Next() {
				return new  PhaseManeger::Boss1Idle;
			}
	};
	class	Boss1Idle : public Phase {
	public:	Boss1Idle() {
		SetFrame(frameCnt, 300, 300);
		Action();
	};
			void Action() {
				AttackSetting tempAttack;
				MoveSetting tempMove;

				tempMove.no = EM_Boss1Move;
				tempMove.speed = 0.25f;

				tempAttack.angle = 90;
				tempAttack.no = EA_Boss1Idle;
				SetBossAM(tempAttack, tempMove);


			};
			Phase *Next() {

				if (GetAliveTurret()) {
					int rand = GameSystem::RandInt(0, 2);
					switch (rand) {
					case 0:	return new  PhaseManeger::Boss1Attack01; break;
					case 1:	return new  PhaseManeger::Boss1Attack02; break;
					case 2:	return new  PhaseManeger::Boss1Attack03; break;
					}
				}
				else {
					return new PhaseManeger::Boss1Outro1;
				}


			}
	};

	class	Boss1Attack01 : public Phase {
	public:	Boss1Attack01() {
		SetFrame(frameCnt, 1200, 1200);
		Action();
	};
			void Action() {
				AttackSetting tempA;

				tempA.no = EA_Boss1Attack1;
				tempA.angle = 90.0f;
				tempA.interval = 7;
				tempA.value = 0;
				tempA.speed = -2.5f;


				tempA.lifeTime = 15.0f;

				SetTurretA(tempA, 1);
				SetTurretA(tempA, 2);


				tempA.no = EA_Round;
				tempA.interval = 60;
				tempA.value = 20;
				D3DXVECTOR2* temp = &GetActionPlayer()->GetCollision()->pos;
				tempA.targetPos = temp;
				SetTurretA(tempA, 0);
				tempA.lifeTime = 90;
				SetTurretA(tempA, 3);
			};
			Phase *Next() {
				return new  PhaseManeger::Boss1Idle;
			}
	};
	class	Boss1Attack02 : public Phase {
	public:	Boss1Attack02() {
		SetFrame(frameCnt, 600, 600);
		Action();
	};
			void Action() {
				AttackSetting tempA;


				tempA.no = EA_Boss1Attack2;
				tempA.angle = 90.0f;
				tempA.interval = 60;
				tempA.value = 7;
				tempA.speed = 3.0f;

				SetTurretA(tempA, 1);
				tempA.stopTime += 15;
				SetTurretA(tempA, 2);
				tempA.stopTime += 15;
				SetTurretA(tempA, 0);
				tempA.stopTime += 15;
				SetTurretA(tempA, 3);


			};
			Phase *Next() {
				return new  PhaseManeger::Boss1Idle;
			}
	};
	class	Boss1Attack03 : public Phase {
	public:	Boss1Attack03() {
		SetFrame(frameCnt, 600, 600);
		Action();
	};
			void Action() {
				AttackSetting tempA;


				tempA.no = EA_Boss1Attack3;
				tempA.angle = 90.0f;



				tempA.interval = 11;
				tempA.value = -3;
				tempA.speed = 2.0f;

				SetTurretA(tempA, 1);
				tempA.value = 3;
				SetTurretA(tempA, 2);
				tempA.value = -5;
				SetTurretA(tempA, 0);
				tempA.value = 5;
				SetTurretA(tempA, 3);

			};
			Phase *Next() {
				return new  PhaseManeger::Boss1Idle;
			}
	};

	class	Boss1Outro1 : public Phase {
	public:	Boss1Outro1() {
		SetFrame(frameCnt, 300, 300);
		Action();
	};
			void Action() {

				AttackSetting tempAttack;
				MoveSetting tempMove;

				tempMove.no = EM_Boss1Outro;
				tempMove.speed = 0.25f;

				tempAttack.no = EA_Boss1Idle;
				tempAttack.angle = 90;

				//ボス
				StopSound(B_BOSS1);
				StopSound(SE_BOSS1SURROUND);
				SetBossAM(tempAttack, tempMove);

			};
			Phase *Next() {
				SetFade(30, D3DCOLOR_RGBA(255, 255, 255, 255), false);
				return new  PhaseManeger::Boss1Outro2;
			}
	};
	class	Boss1Outro2 : public Phase {
	public:	Boss1Outro2() {
		SetFrame(frameCnt, 60, 60);
		Action();
	};
			void Action() {
				StopSound(B_STAGEONE);
				PlaySound(SE_BIGEXPLOSION);

			};
			Phase *Next() {
				DestroyBoss(0);
				SetFade(240, D3DCOLOR_RGBA(255, 255, 255, 0), false);
				return new  PhaseManeger::Boss2Intro;
			}
	};
	class	Boss2Intro : public Phase {
	public:	Boss2Intro() {
		SetFrame(frameCnt, 60, 60);
		Action();
	};
			void Action() {
				InitBoss(1);

				MoveSetting tempMove;
				AttackSetting tempAttack;
				tempAttack.no = EA_Boss2Idle;
				tempMove.no = EM_Boss2Intro;
				tempMove.speed = 1.5f;
				tempMove.moveLength = 0;
				SetBossAM(tempAttack, tempMove);
				PlaySound(SE_BOSS2SURROUND);
				SetScrollSpeed(15.0f);

			};
			Phase *Next() {
				PlaySound(B_BOSS2);
				return new  PhaseManeger::Boss2Intro2;
			}
	};
	class	Boss2Intro2 : public Phase {
	public:	Boss2Intro2() {
		SetFrame(frameCnt, 90, 90);
		Action();
	};
			void Action() {


			};

			Phase *Next() {
				return new  PhaseManeger::Boss2Move(2);
			}
	};


	class	Boss2Move : public Phase {
	public:	Boss2Move(int nowDir) {
		preDirection = nowDir;
		SetFrame(frameCnt, 120, 120);
		Action();

	};
			int direction;
			int preDirection;

			void Action() {



				direction = GameSystem::RandInt(0, 9);

				if (direction == 0 && direction == 9) {
					direction = (preDirection + 2) % 4;
				}
				else 
				{
					if (direction > 4) {
						direction = (preDirection + 1) % 4;
					}
					else {
						preDirection == 0 ? direction = 3 : direction = preDirection - 1;
					}
				}



				MoveSetting tempMove;
				AttackSetting tempAttack;

				tempMove.no = EM_Boss2Move;

				D3DXVECTOR2 temp;
				switch (direction) {
				case 0:temp = { SCREEN_WIDTH - 300.0f		,0.5f*SCREEN_HEIGHT -300.0f}; break;
				case 1:temp = { SCREEN_WIDTH*0.5f -300.0f	,SCREEN_HEIGHT -300.0f}; break;
				case 2:temp = { -300.0f					,0.5f*SCREEN_HEIGHT -300.0f}; break;
				case 3:temp = { 0.5f*SCREEN_WIDTH	-300.0f	,-300.0f}; break;}
				tempMove.pathPoint[0] = temp;

				if (GetBoss()->hitPoint <= 3000) {
					tempMove.pathPoint[0] = {SCREEN_WIDTH*0.5f - 300.0f,SCREEN_HEIGHT*0.5f - 300.0f };
				}

				tempMove.speed = 1.5f;

				tempAttack.no = EA_Boss2Idle;

				SetBossAM(tempAttack, tempMove);

			};
			Phase *Next() {
				
				if (GetBoss()->hitPoint <= 3000) {
					return new  PhaseManeger::Boss2Center(-120);
				}

				switch (direction) {
				case 0:	return new  PhaseManeger::Boss2Right;
				case 1:	return new  PhaseManeger::Boss2Down;
				case 2:	return new  PhaseManeger::Boss2Left;
				case 3:	return new  PhaseManeger::Boss2Up;
				}

			}
	};

	class	Boss2Right : public Phase {
	public:	Boss2Right() {
		SetFrame(frameCnt, 900, 900);
		Action();
	};
			void Action() {

				MoveSetting tempMove;
				AttackSetting tempAttack;

				tempMove.no = EM_Boss2Right;
				tempMove.speed = 1.0f;
				tempAttack.no = EA_Boss2Right;


				if (GetBoss()->hitPoint > 5500) {
					tempAttack.speed = -2.5f;
					tempAttack.interval = 90;
					tempAttack.value = 4;
				}
				else {
					tempAttack.speed = -5.0f;
					tempAttack.interval = 60;
					tempAttack.value = 6;

				}

				SetBossAM(tempAttack, tempMove);

			};
			Phase *Next() {
				return new  PhaseManeger::Boss2Move(0);
			}
	};
	class	Boss2Down : public Phase {
	public:	Boss2Down() {
		SetFrame(frameCnt, 900, 900);
		Action();
	};
			void Action() {

				MoveSetting tempMove;
				AttackSetting tempAttack;

				tempMove.no = EM_Boss2Down;
				tempMove.speed = 1.0f;
				tempAttack.no = EA_Boss2Down;
				if (GetBoss()->hitPoint > 5500) {
					tempAttack.speed = -5.0f;
					tempAttack.interval = 10;
					tempAttack.lifeTime = 30;
					tempAttack.stopTime = 90;
				}
				else {
					tempAttack.speed = -5.0f;
					tempAttack.interval = 7;
					tempAttack.lifeTime = 35;
					tempAttack.stopTime = 105;

				}
				SetBossAM(tempAttack, tempMove);
			};
			Phase *Next() {
				return new  PhaseManeger::Boss2Move(1);
			}
	};
	class	Boss2Left : public Phase {
	public:	Boss2Left() {
		SetFrame(frameCnt, 900, 900);
		Action();
	};
			void Action() {

				MoveSetting tempMove;
				AttackSetting tempAttack;

				tempMove.no = EM_Boss2Left;
				tempMove.speed = 1.0f;
				tempAttack.no = EA_Boss2Left;
				if (GetBoss()->hitPoint > 5500) {
					tempAttack.speed = -5.0f;
					tempAttack.interval = 5;
					tempAttack.lifeTime = 1;
					tempAttack.stopTime = 60;
				}
				else {
					tempAttack.speed = -3.0f;
					tempAttack.interval = 5;
					tempAttack.lifeTime = 2;
					tempAttack.stopTime = 45;
				}
				SetBossAM(tempAttack, tempMove);
			};
			Phase *Next() {
				return new  PhaseManeger::Boss2Move(2);
			}
	};
	class	Boss2Up : public Phase {
	public:	Boss2Up() {
		SetFrame(frameCnt, 900, 900);
		Action();
	};
			void Action() {

				MoveSetting tempMove;
				AttackSetting tempAttack;

				tempMove.no = EM_Boss2Up;
				tempMove.speed = 1.0f;
				tempAttack.no = EA_Boss2Up;
				if (GetBoss()->hitPoint > 5500) {
					tempAttack.interval = 45;
					tempAttack.angle = 270;
					tempAttack.speed = 5.0f;

				}
				else {
					tempAttack.interval = 30;
					tempAttack.angle = 270;
					tempAttack.speed = 10.0f;

				}
				SetBossAM(tempAttack, tempMove);
			};
			Phase *Next() {
				return new  PhaseManeger::Boss2Move(3);
			}
	};
	class	Boss2Center : public Phase {
	public:	Boss2Center(int wait) {
		ClearBullet();
		SetFrame(frameCnt, 999999999, 999999999);
		Action();
		waitFrame = wait;
	};
			int waitFrame;
			void Action() {

				MoveSetting tempMove;
				AttackSetting tempAttack;

				tempMove.no = EM_Boss2Center;
				tempMove.speed = 1.0f;
				tempAttack.no = EA_Boss2Center;
				tempAttack.speed = 20.0f;
				tempAttack.brlAngle = 0.05f;
				SetBossAM(tempAttack, tempMove);
				SetFade(1, D3DCOLOR_RGBA(255, 255, 255, 0), false);
			};
			Phase *Next() {

				return new  PhaseManeger::Boss2Center(0);
			}
	};

	class	Boss2Outro : public Phase {
	public:	Boss2Outro() {
		SetFrame(frameCnt, 120, 120);
		Action();
	};
			void Action() {
				SetFade(240, D3DCOLOR_RGBA(255, 255, 255, 128), false);

				MoveSetting tempMove;
				AttackSetting tempAttack;

				tempMove.no = EM_Boss2Outro;
				tempMove.speed = 0.25f;
				tempAttack.no = EA_Boss2Idle;

				StopSound(B_BOSS2);
				StopSound(SE_BOSS2SURROUND);
				SetBossAM(tempAttack, tempMove);
			};
			Phase *Next() {

				return new  PhaseManeger::Boss2Outro2;
			}
	};
	class	Boss2Outro2 : public Phase {
	public:	Boss2Outro2() {
		SetFrame(frameCnt, 300, 300);
		Action();
	};
			void Action() {
				SetFade(10, D3DCOLOR_RGBA(0, 0, 0, 0), false);

				PlaySound(SE_BIGEXPLOSION);



				MoveSetting tempMove;
				AttackSetting tempAttack;

				tempMove.no = EM_Straight;
				tempMove.velocity = { -1.0f*GetScrollSpeed() ,0};
				tempMove.angle = -90;
				tempAttack.no = EA_Boss2Idle;

				SetBossAM(tempAttack, tempMove);
			};
			Phase *Next() {
				SetComplete();
				DestroyBoss(1);
				SetTrailEnable();

				return new  PhaseManeger::MissionComplete;
			}
	};

	class	MissionComplete : public Phase {
	public:	MissionComplete() {
		SetFrame(frameCnt, 300, 300);
		Action();
	};
			void Action() {
			};
			Phase *Next() {
				PlaySound(SE_BOSS2SURROUND);
				GetActionPlayer()->stageEnd = true;
				return new  PhaseManeger::MissionComplete;
			}
	};


	Phase *nowPhase;

public:

	void Update() {

		if (frameCnt > nowPhase->GetStartFrame() + nowPhase->GetStopLength()) {
			CleanUp();
		}

		if (frameCnt > nowPhase->GetStartFrame() + nowPhase->GetLength()) {
			nowPhase = nowPhase->Next();
			phaseNow += 1;
		}
	}

	void ForcedNext() {
		nowPhase = nowPhase->Next();
		phaseNow += 1;
	}

	void ResetPhase() {
		nowPhase = new Phase_0;
	}

	void BossOutro(int no) {
		switch (no)
		{
		case 0:	nowPhase = new Boss1Outro1; break;
		case 1: nowPhase = new Boss2Outro; break;
		}

	}
};

PhaseManeger conPhase;
bool isCounting;

void InitPhase(int frameNow) {
	frameCnt = 0;
	phaseNow = 0;
	isCounting = true;
	conPhase.ResetPhase();
}

void UpdatePhase() {

	if (!GetFadeState()) {
		if (isCounting) {
			frameCnt += 1;
		}
		conPhase.Update();
	}

}

void SwitchCounting() {
	isCounting = !isCounting;
}

void FwdPhase() {
	conPhase.ForcedNext();
}

int GetPhaseCnt() {
	return frameCnt;
}

int GetPhaseNow() {
	return phaseNow;
}

void ResetPhase() {
	conPhase.ResetPhase();
}

void ForceBossOutro(int no) {
	conPhase.BossOutro(no);
}
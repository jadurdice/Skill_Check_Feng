#ifndef _PHASEMANEGER_H_
#define _PHASEMANEGER_H_

void InitPhase(int frameNow);
void UpdatePhase();
void SwitchCounting();
void FwdPhase();
int GetPhaseCnt();
int GetPhaseNow();
void ForceBossOutro(int no);

#endif
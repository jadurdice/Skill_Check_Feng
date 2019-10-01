#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

void BackInit();
void BackUnInit();
void BackUpdate();
void BackDraw();

void FrontInit();
void FrontUnInit();
void FrontUpdate();
void FrontDraw();

void SetScrollSpeed(float speed);
int GetBGTexNo();
float GetScrollSpeed();
#endif
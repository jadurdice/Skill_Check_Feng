#pragma once

#define	HOSEI	(-0.5f)

void DrawSpriteUV(unsigned int textureID, float x, float y, float tx, float ty,float tw, float th, float width, float height);
void DrawSpriteMove(unsigned int textureID, float x, float y, float tx, float ty, float tw, float th, float width, float height, char rotFactor);
void DrawSpriteCircle(unsigned int textureID, float x, float y, float tx, float ty, float tw, float th, float width, float height);

void SetColor(int r, int g, int b, int a);
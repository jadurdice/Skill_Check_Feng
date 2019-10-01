
#include "main.h"
#include"Game.h"
#include "sprite.h"
#include"texture.h"


struct VERTEX_3D
{
	Float3 Position;
	Float4 Color;
	Float2 TexCoord;
};

Float4 glbColor = { 0.0f,0.0f,0.0f,0.0f };
static 	int shake;

void DrawSpriteUV(unsigned int textureID, float x, float y, float tx, float ty, float tw, float th, float width, float height)
{
	VERTEX_3D vertex[4];


	vertex[0].Position = MakeFloat3(SCREEN_WIDTH*-0.5f + x + HOSEI, SCREEN_HEIGHT*-0.5f + y + HOSEI, 0.0f);
	vertex[1].Position = MakeFloat3(SCREEN_WIDTH*-0.5f + x + HOSEI + width, SCREEN_HEIGHT*-0.5f + y + HOSEI, 0.0f);
	vertex[2].Position = MakeFloat3(SCREEN_WIDTH*-0.5f + x + HOSEI, SCREEN_HEIGHT*-0.5f + y + HOSEI + height, 0.0f);
	vertex[3].Position = MakeFloat3(SCREEN_WIDTH*-0.5f + x + HOSEI + width, SCREEN_HEIGHT*-0.5f + y + HOSEI + height, 0.0f);


	if ((shake = GameSystem::GetShakeForce()) != 0) {
		for (int i = 0; i < 4; i++)
		{
			vertex[i].Position.x += shake;
			vertex[i].Position.y += shake;
		}
	}

	vertex[0].Color = glbColor;
	vertex[1].Color = glbColor;
	vertex[2].Color = glbColor;
	vertex[3].Color = glbColor;

	vertex[0].TexCoord = MakeFloat2(tx, ty);
	vertex[1].TexCoord = MakeFloat2(tx + tw, ty);
	vertex[2].TexCoord = MakeFloat2(tx, ty + th);
	vertex[3].TexCoord = MakeFloat2(tx + tw, ty + th);

	SetTexture(textureID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}

void DrawSpriteMove(unsigned int textureID, float x, float y, float tx, float ty, float tw, float th, float width, float height, char rotFactor)
{
	VERTEX_3D vertex[4];

	float x0, x1, y0, y1;

	x0 = SCREEN_WIDTH * -0.5f + x + HOSEI;
	x1 = SCREEN_WIDTH * -0.5f + x + HOSEI + width;
	y0 = SCREEN_HEIGHT * -0.5f + y + HOSEI;
	y1 = SCREEN_HEIGHT * -0.5f + y + HOSEI + height;


	vertex[0].Position = MakeFloat3(x0, y0, 0.0f);
	vertex[1].Position = MakeFloat3(x1, y0, 0.0f);
	vertex[2].Position = MakeFloat3(x0, y1, 0.0f);
	vertex[3].Position = MakeFloat3(x1, y1, 0.0f);


	if ((shake = GameSystem::GetShakeForce()) != 0) {
		for (int i = 0; i < 4; i++)
		{
			vertex[i].Position.x += shake;
			vertex[i].Position.y += shake;
		}
	}


	vertex[0].Color = glbColor;
	vertex[1].Color = glbColor;
	vertex[2].Color = glbColor;
	vertex[3].Color = glbColor;

	if (rotFactor & (1 << 0)) {
		vertex[0].TexCoord = MakeFloat2(tx, ty);
		vertex[1].TexCoord = MakeFloat2(tx + tw, ty);
		vertex[2].TexCoord = MakeFloat2(tx, ty + th);
		vertex[3].TexCoord = MakeFloat2(tx + tw, ty + th);
	}
	else if(rotFactor & (1<<1)){
		vertex[0].TexCoord = MakeFloat2(tx + tw, ty);
		vertex[1].TexCoord = MakeFloat2(tx, ty);
		vertex[2].TexCoord = MakeFloat2(tx + tw, ty + th);
		vertex[3].TexCoord = MakeFloat2(tx, ty + th);
	}


	SetTexture(textureID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


}

void DrawSpriteCircle(unsigned int textureID, float x, float y, float tx, float ty, float tw, float th, float width, float height)
{
	VERTEX_3D vertex[4];

	float x0, x1, y0, y1,hh,hw;
	
	hw = width * 0.5f;
	hh = height * 0.5f;


	x0 = SCREEN_WIDTH * -0.5f + x + HOSEI -hw;
	x1 = SCREEN_WIDTH * -0.5f + x + HOSEI +hw;
	y0 = SCREEN_HEIGHT * -0.5f + y + HOSEI - hh;
	y1 = SCREEN_HEIGHT * -0.5f + y + HOSEI + hh;


	vertex[0].Position = MakeFloat3(x0, y0, 0.0f);
	vertex[1].Position = MakeFloat3(x1, y0, 0.0f);
	vertex[2].Position = MakeFloat3(x0, y1, 0.0f);
	vertex[3].Position = MakeFloat3(x1, y1, 0.0f);


	if ((shake = GameSystem::GetShakeForce()) != 0) {
		for (int i = 0; i < 4; i++)
		{
			vertex[i].Position.x += shake;
			vertex[i].Position.y += shake;
		}
	}


	vertex[0].Color = glbColor;
	vertex[1].Color = glbColor;
	vertex[2].Color = glbColor;
	vertex[3].Color = glbColor;

	vertex[0].TexCoord = MakeFloat2(tx, ty);
	vertex[1].TexCoord = MakeFloat2(tx + tw, ty);
	vertex[2].TexCoord = MakeFloat2(tx, ty + th);
	vertex[3].TexCoord = MakeFloat2(tx + tw, ty + th);


	SetTexture(textureID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->Color);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&vertex->TexCoord);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


}


void SetColor(int r, int g, int b, int a) {
	glbColor = MakeFloat4(
		(float)r / 255,
		(float)g / 255,
		(float)b / 255,
		(float)a / 255
	);
}

#include "main.h"
#include "controller.h"
#include"sound.h"
#include "texture.h"
#include"Game.h"
#include "sprite.h"
#include <nn/util/util_TinyMt.h>
#include <nn/nn_BitTypes.h>


static nn::util::TinyMt rGene;

void Init();
void Uninit();
void Update();
void Draw();

int glbFrame;

extern "C" void nnMain()
{
	Init();

    while( true )
	{
		Update();
		Draw();
	}

	Uninit();
}


void Init()
{

	InitSound();
	InitSystem();

	InitController();


	glbFrame = 0;
	rGene.Initialize(NULL);
	InitScene();

}


void Uninit()
{
	UninitScene();
	UninitController();
	UninitSystem();
	UninitSound();

}


void Update()
{
	UpdateController();
	UpdateScene();
	UpdateSound();

	glbFrame += 1;

}


void Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawScene();
	SwapBuffers();
}

int GetFrame() {
	return glbFrame;
}

void ResetFrame() {
	glbFrame = 0;
}
#include"SceneManeger.h"
#include<string.h>
#include"Title.h"
#include"Game.h"
#include"Fade.h"
#include"HighScore.h"
#include"texture.h"

// ���݂̃V�[�����ێ��p
static SceneProc glbNowScene;
static SceneProc glbNextScene;

void InitScene() {

	glbNowScene = SetupTitleScene();
	glbNowScene.Init();
}
void UninitScene() {
	// �Ō�͉�����ďI���
	if (glbNowScene.Uninit) glbNowScene.Uninit();

	glbNowScene = {};
}
void UpdateScene() {
	if (glbNowScene.Update) glbNowScene.Update();
}
void DrawScene() {
	glbNowScene.Draw();
}

void SetScene(int nextScene) {
	switch (nextScene)
	{
	case S_Title:
		glbNextScene = SetupTitleScene();
		break;
	case S_Game:
		glbNextScene = SetupGameScene();
		break;
	case S_GameOver:
		glbNextScene = SetupHSScene();
		break;
	}
	SetFade(60, D3DCOLOR_RGBA(0, 0, 0, 255), true);

}

// �V�[���̑J��
void JumpScene()
{
	// ���݂̃V�[�����������
	if (glbNowScene.Uninit) glbNowScene.Uninit();
	glbNowScene = {};

	// ���̃V�[��������Ώ���������
	glbNowScene = glbNextScene;
	glbNextScene = {};

	glbNowScene.Init();
	TextureLoad();
}

// �V�[�����̎擾
const char* GetSceneName(void)
{
	if (glbNowScene.Name) return glbNowScene.Name;
	return "Unknown";
}

int GetSceneIndex() {
	return glbNowScene.Index;
}

bool GetReadyToChange() {
	return(!(glbNextScene.Index == glbNowScene.Index));
}
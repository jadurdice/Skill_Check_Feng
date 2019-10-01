#include"SceneManeger.h"
#include<string.h>
#include"Title.h"
#include"Game.h"
#include"Fade.h"
#include"HighScore.h"
#include"texture.h"

// 現在のシーン情報保持用
static SceneProc glbNowScene;
static SceneProc glbNextScene;

void InitScene() {

	glbNowScene = SetupTitleScene();
	glbNowScene.Init();
}
void UninitScene() {
	// 最後は解放して終わる
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

// シーンの遷移
void JumpScene()
{
	// 現在のシーンを解放する
	if (glbNowScene.Uninit) glbNowScene.Uninit();
	glbNowScene = {};

	// 次のシーンがあれば初期化する
	glbNowScene = glbNextScene;
	glbNextScene = {};

	glbNowScene.Init();
	TextureLoad();
}

// シーン名の取得
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
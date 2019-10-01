#include"SenceManeger.h"
#include"Game.h"
#include"Title.h"
#include"GameOver.h"

// 現在のシーン情報保持用
static SceneProc glbNowScene;

void InitScene() {

	glbNowScene = {};

	SceneChange(S_Title);
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
void SceneChange(int nextScene) {
	switch (nextScene)
	{
	case S_Title:
		JumpScene(SetupTitleScene);
		break;
	case S_Game:
		JumpScene(SetupGameScene);
		break;
	case S_GameOver:
		JumpScene(SetupGameOverScene);
		break;
	}
}

// シーンの遷移
void JumpScene(SetupFunc Func)
{
	// 現在のシーンを解放する
	if (glbNowScene.Uninit) glbNowScene.Uninit();
	glbNowScene = {};

	// 次のシーンがあれば初期化する
	glbNowScene = Func();
	glbNowScene.Init();

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
#include"SenceManeger.h"
#include"Game.h"
#include"Title.h"
#include"GameOver.h"

// ���݂̃V�[�����ێ��p
static SceneProc glbNowScene;

void InitScene() {

	glbNowScene = {};

	SceneChange(S_Title);
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

// �V�[���̑J��
void JumpScene(SetupFunc Func)
{
	// ���݂̃V�[�����������
	if (glbNowScene.Uninit) glbNowScene.Uninit();
	glbNowScene = {};

	// ���̃V�[��������Ώ���������
	glbNowScene = Func();
	glbNowScene.Init();

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
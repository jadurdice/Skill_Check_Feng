#pragma once

enum SceneNumber
{
	S_Title,
	S_Game,
	S_GameOver,
	S_Count,
};

// 初期化用関数
typedef	void(*InitFunc)(void);
// 解放用関数
typedef	void(*UninitFunc)(void);
// 更新用関数
typedef	void(*UpdateFunc)(void);
// 描画用関数
typedef	void(*DrawFunc)(void);

// シーン処理設定用構造体
struct SceneProc
{
	int				Index;
	const char*		Name;
	InitFunc		Init;
	UninitFunc		Uninit;
	UpdateFunc		Update;
	DrawFunc		Draw;
};
// シーン遷移用の関数型

typedef SceneProc(*SetupFunc)(void);

// シーン名の取得
const char* GetSceneName(void);


void InitScene();
void UninitScene();
void UpdateScene();
void DrawScene();
void SceneChange(int nextScene);
void JumpScene(SetupFunc Func);
int GetSceneIndex();
#ifndef _SCENEMANEGER_H_
#define _SCENEMANEGER_H_

enum SceneNumber
{
	S_Title,
	S_Game,
	S_GameOver,
	S_Quit,
	S_Count
};

// �������p�֐�
typedef	void(*InitFunc)(void);
// ����p�֐�
typedef	void(*UninitFunc)(void);
// �X�V�p�֐�
typedef	void(*UpdateFunc)(void);
// �`��p�֐�
typedef	void(*DrawFunc)(void);

// �V�[�������ݒ�p�\����
struct SceneProc
{
	int				Index;
	const char*		Name;
	InitFunc		Init;
	UninitFunc		Uninit;
	UpdateFunc		Update;
	DrawFunc		Draw;
};
// �V�[���J�ڗp�̊֐��^

typedef SceneProc(*SetupFunc)(void);

// �V�[�����̎擾
const char* GetSceneName(void);


void InitScene();
void UninitScene();
void UpdateScene();
void DrawScene();

void SetScene(int nextScene);
void JumpScene();
bool GetReadyToChange();
int GetSceneIndex();
#endif

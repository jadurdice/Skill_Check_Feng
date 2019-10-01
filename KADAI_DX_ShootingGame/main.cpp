/*/\/\/\/\/\/\/\/\/\/\/\/\Valar_Morghulis./\/\/\/\/\/\/\/\/\/\/\/\
 /\
 ||
 ||
 ||
/\/\
 ||
 Ｏ
\/\/\/\/\/\/\/\/\/\/\/\/\/Valar_Dohaeris.\/\/\/\/\/\/\/\/\/\/\/\/*/

#include"main.h"
#include"d3dsystem.h"
#include"SceneManeger.h"
#include"sound.h"
#include"Debug.h"
#include"Fade.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//グローバル変数
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//フレームカウンター
static int glbFrameCnt = 0;
//FPS計測の基となるフレームカウンター
static int glbFPSBaseFrameCnt = 0;
//FPS計測の基となる時間
static double glbFPSBaseTime = 0.0f;
//フレーム固定用計測時間
static double glbStaticFrameTime = 0.0f;
//FPS	
static float glbFPS = 0.0f;


static LPDIRECT3DDEVICE9 glbPtDevice = NULL;


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//関数
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//WindowsAPIによるウィンドウクラス（新しいウィンドウ）を作る処理

	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RECT wndRect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(
		&wndRect,
		WND_STYLE_CUSTOM,
		false
	);
	int oa_WndWidth = wndRect.right - wndRect.left;
	int oa_WndHeight = wndRect.bottom - wndRect.top;

	int wndCreateX = max((GetSystemMetrics(SM_CXSCREEN) - oa_WndWidth) / 2, 0);
	int wndCreateY = max((GetSystemMetrics(SM_CYSCREEN) - oa_WndHeight) / 2, 0);

	RegisterClass(&wc);
	HWND hWnd = CreateWindow(
		CLASS_NAME,
		WND_CAPTION,
		WND_STYLE_CUSTOM,
		wndCreateX,
		wndCreateY,
		oa_WndWidth,
		oa_WndHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//ゲームループ
	MSG msg = {};
	Initialize(hWnd, hInstance);
	



	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
#ifndef BENCHMARK
			double time = SystemTimer_GetTime();
			if (time - glbStaticFrameTime < 1.0 / 60.0) {
				Sleep(0);
			}
			else {
				glbStaticFrameTime = time;
#endif // !0
				//ゲーム処理
				Update();//ゲームループ処理関数
				Draw();//描画関数
#ifndef BENCHMARK

			}
#endif // !0
		}
	}
	Finalize();//終了関数

	return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいいですか？\nセーブしてないプロセスは消えることがある。", "終了確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		else {
			return 0;
		}
		PostQuitMessage(0);
	case WM_DESTROY:
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool Initialize(HWND hWnd, HINSTANCE  hInstance) {

	if (!D3DInit(hWnd)) {
		return false;
	};

	glbPtDevice = GetDevice();
	InitSprite();
	InitSound(hWnd);


	InitDebug();
	InitFade();
	InitScene();

	



	int errorCnt = TextureLoad();

	if (errorCnt > 0) {
		DebugMB("%d件のテクスチャの読み込み失敗", errorCnt);
	};

	DebugFont_Initialize();

	Keyboard_Initialize(hInstance, hWnd);



	//FPS計測（Initの最後固定）
	//システムタイマーの初期化
	SystemTimer_Initialize();
	//システムタイマーの起動
	SystemTimer_Start();
	//FPS計測用変数郡を初期化します
	glbFrameCnt = glbFPSBaseFrameCnt = 0;
	glbFPS = 0.0f;
	glbStaticFrameTime = glbFPSBaseTime = SystemTimer_GetTime();


	return true;
}
void Finalize(void) {

	UninitScene();
	D3DUninit();
	textureDelete();
	Keyboard_Finalize();
	DebugFont_Finalize();
	UninitSprite();
	UninitSound();
	UninitDebug();
}
void Update() {

	UpdateFade();
	UpdateScene();
	
	Keyboard_Update();
	//フレームカウント(Updateの最後に固定)
	glbFrameCnt++;
	//現在のシステム時間の取得
	double time = SystemTimer_GetTime();
	//前回のFPS計測時間から既定時間経っていたらFPS計測
	if (time - glbFPSBaseTime >= FPS_MEASUREMENT_TIME) {

		//FPSを計算します(前回からの経過フレーム/経過時間)
		glbFPS = (float)((glbFrameCnt - glbFPSBaseFrameCnt) / (time - glbFPSBaseTime));

		//FPS計測の基になる変数を更新
		glbFPSBaseFrameCnt = glbFrameCnt;
		glbFPSBaseTime = time;
	}

}
void Draw(void) {

	glbPtDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(255, 0, 155, 0), 1.0f, 0);
	glbPtDevice->BeginScene();


	DrawScene();
	DrawFade();


	DebugFont_Draw(10.0f, 10.0f, "%.2f", glbFPS);
	glbPtDevice->EndScene();
	glbPtDevice->Present(NULL, NULL, NULL, NULL);
}
int GetFrame() {
	return glbFrameCnt;
}
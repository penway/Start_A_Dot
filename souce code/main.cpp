#include "Levels.h"
#include <ctime>

#pragma comment(lib, "winmm")

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID RegisterWindowClass();
HWND CreateWindowFat();


INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ PWSTR, _In_ INT nCmdShow)
{
	srand(time(0));

	// 注册窗口类
	RegisterWindowClass();
	

	// 创建窗口 显示窗口
	HWND hWnd = CreateWindowFat();
	if (!hWnd) { return -1; }
	ShowWindow(hWnd, nCmdShow);

	// 初始化 ROC Controller 并启动初始页面
	RocController::Init(hWnd);
	RocController::LoadInitalLevel(new Level_0_BeginPage);

	//PlaySound(L".\\Resources\\Musics\\main1.wav", NULL, SND_FILENAME | SND_ASYNC);
	//PlaySound(L".\\Resources\\Musics\\beat1.wav", NULL, SND_FILENAME | SND_ASYNC);
	//mciSendString(L".\\Resources\\Musics\\beat1.wav", NULL, 0, 0);

	// 建立消息循环
	MSG message = { };
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
			continue;
		}
		RocController::Update();
		RocController::BeginDraw();
		RocController::Render();
		RocController::EndDraw();
	}

	return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	case WM_KEYDOWN:
	{
		RocController::HandleKey(wParam, KEY_DOWN);
	}

	case WM_KEYUP:
	{
		RocController::HandleKey(wParam, KEY_UP);
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


VOID RegisterWindowClass()
{
	WNDCLASS windowclass = { };
	windowclass.hInstance = GetModuleHandle(NULL);
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	windowclass.hIcon = (HICON)::LoadImage(NULL, L".\\Resources\\Pictures\\x.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	RegisterClass(&windowclass);
}


HWND CreateWindowFat()
{
	RECT clientRect = { 0, 0, 1000, 750 };
	AdjustWindowRectEx(&clientRect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	HWND hWnd = CreateWindowEx(
		0,
		L"MainWindow",
		L"Start A Dot",
		WS_OVERLAPPEDWINDOW ^ DS_MODALFRAME ^ WS_MAXIMIZEBOX,
		10, 10,
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
		NULL, NULL, GetModuleHandle(NULL), 0
	);
	if (!hWnd) { MessageBox(NULL, L"窗口创建失败", L"", MB_OK); return NULL; }

	return hWnd;
}
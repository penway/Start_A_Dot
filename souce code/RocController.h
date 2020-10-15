#pragma once

#include <Windows.h>
#include "RocLevel.h"

#define KEY_UP   0
#define KEY_DOWN 1

class RocController
{
/// <summary>
/// ROC 引擎的总控制，拥有 RocStudio 资源，当前关卡指针
/// 并且处理键盘输入，接管合并 WASD和↑←↓→，并继续传递其他键盘指令给关卡处理
/// 所有的绘画都应由 RocController 进行而非直接调用 RocStudio
/// 所有的关卡加载与卸载也应该由 RocController 进行
/// </summary>

public:
	static VOID Init(HWND hWnd);                             // 初始化

	static VOID LoadInitalLevel(RocLevel* pLevel);           // 加载第一个关卡
	static VOID SwitchLevel(RocLevel* pLevel);               // 卸载且加载关卡

	static VOID BeginDraw();                                 // 开始 Studio/RenderTarget 绘画资源
	static VOID EndDraw();                                   // 结束 Studio/RenderTarget 绘画资源
	static VOID Render();                                    // 调用关卡绘画
	static VOID Update();                                    // 调用关卡更新

	static VOID HandleKey(WPARAM wParam, int keyStatus);     // 从 WindowProc 处理键盘鼠标输入信息
	static BOOL IsUp();                                      // 判断是否是按下上，接管 'w', 'W', '↑'
	static BOOL IsDown();
	static BOOL IsLeft();
	static BOOL IsRight();

	static RocStudio* GetStudio();

private:
	RocController() { }
	static RocStudio* m_pStudio;          // Studio 指针
	static RocLevel* m_pCurrentLevel;     // 当前关卡指针
	static BOOL m_isLoading;              // 是否加载指示

	static BOOL m_isUp;                   // 判断是否是按下上，接管 'w', 'W', '↑'
	static BOOL m_isDown;
	static BOOL m_isLeft;
	static BOOL m_isRight;

	static BOOL m_lastKeyUp;              // 由于 Windows 键盘输入的特殊性
	static BOOL m_lastKeyDown;            // 需要记录之前的按键来辅助判断
	static BOOL m_lastKeyLeft;
	static BOOL m_lastKeyRight;
};

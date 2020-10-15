#include "RocController.h"

RocStudio* RocController::m_pStudio;
RocLevel* RocController::m_pCurrentLevel;
BOOL RocController::m_isLoading;

BOOL RocController::m_isUp;
BOOL RocController::m_isDown;
BOOL RocController::m_isLeft;
BOOL RocController::m_isRight;
BOOL RocController::m_lastKeyUp;
BOOL RocController::m_lastKeyDown;
BOOL RocController::m_lastKeyLeft;
BOOL RocController::m_lastKeyRight;

VOID RocController::Init(HWND hWnd)
{
	m_isLoading = TRUE;
	m_pCurrentLevel = NULL;
	m_pStudio = new RocStudio();
	m_pStudio->Init(hWnd);
	m_isDown = m_isUp = m_isLeft = m_isRight = 0;
	m_lastKeyUp = m_lastKeyDown = m_lastKeyLeft = m_lastKeyRight = 0;
}

VOID RocController::LoadInitalLevel(RocLevel* pLevel)
{
	m_isLoading = TRUE;
	m_pCurrentLevel = pLevel;
	m_pCurrentLevel->Load();
	m_isLoading = FALSE;
}

VOID RocController::SwitchLevel(RocLevel* pLevel)
{
	m_isLoading = TRUE;
	m_pCurrentLevel->Unload();
	pLevel->Load();
	delete m_pCurrentLevel;
	m_pCurrentLevel = pLevel;
	m_isLoading = FALSE;
}

VOID RocController::BeginDraw()
{
	m_pStudio->BeginDraw();
}

VOID RocController::EndDraw()
{
	m_pStudio->EndDraw();
}

VOID RocController::Render()
{
	if (m_isLoading) return;
	m_pCurrentLevel->Render();
}

VOID RocController::Update()
{
	if (m_isLoading) return;
	m_pCurrentLevel->Update();
}


VOID RocController::HandleKey(WPARAM wParam, int keyStatus)
{
	switch (wParam)
	{
	case (int)'a':
	case (int)'A':
	case VK_LEFT:
		if (m_lastKeyLeft == KEY_UP && keyStatus == KEY_DOWN)
		{
			m_lastKeyLeft = KEY_DOWN;
			m_isLeft = TRUE;
		}
		if (m_lastKeyLeft == KEY_UP && keyStatus == KEY_UP)
		{
			m_lastKeyLeft = KEY_UP;
			m_isLeft = FALSE;
		}
		if (m_lastKeyLeft == KEY_DOWN && keyStatus == KEY_UP)
		{
			m_lastKeyLeft = KEY_UP;
		}
		break;
	case (int)'d':
	case (int)'D':
	case VK_RIGHT:
		if (m_lastKeyRight == KEY_UP && keyStatus == KEY_DOWN)
		{
			m_lastKeyRight = KEY_DOWN;
			m_isRight = TRUE;
		}
		if (m_lastKeyRight == KEY_UP && keyStatus == KEY_UP)
		{
			m_lastKeyRight = KEY_UP;
			m_isRight = FALSE;
		}
		if (m_lastKeyRight == KEY_DOWN && keyStatus == KEY_UP)
		{
			m_lastKeyRight = KEY_UP;
		}
		break;
	case (int)'w':
	case (int)'W':
	case VK_UP:
		if (m_lastKeyUp == KEY_UP && keyStatus == KEY_DOWN)
		{
			m_lastKeyUp = KEY_DOWN;
			m_isUp = TRUE;
		}
		if (m_lastKeyUp == KEY_UP && keyStatus == KEY_UP)
		{
			m_lastKeyUp = KEY_UP;
			m_isUp = FALSE;
		}
		if (m_lastKeyUp == KEY_DOWN && keyStatus == KEY_UP)
		{
			m_lastKeyUp = KEY_UP;
		}
		break;
	case (int)'s':
	case (int)'S':
	case VK_DOWN:
		if (m_lastKeyDown == KEY_UP && keyStatus == KEY_DOWN)
		{
			m_lastKeyDown = KEY_DOWN;
			m_isDown = TRUE;
		}
		if (m_lastKeyDown == KEY_UP && keyStatus == KEY_UP)
		{
			m_lastKeyDown = KEY_UP;
			m_isDown = FALSE;
		}
		if (m_lastKeyDown == KEY_DOWN && keyStatus == KEY_UP)
		{
			m_lastKeyDown = KEY_UP;
		}
		break;
	default:
		break;
	}
	if (keyStatus)
		m_pCurrentLevel->HandleKey(wParam);
}

BOOL RocController::IsUp()
{
	return m_isUp;
}

BOOL RocController::IsDown()
{
	return m_isDown;
}

BOOL RocController::IsLeft()
{
	return m_isLeft;
}

BOOL RocController::IsRight()
{
	return m_isRight;
}

RocStudio* RocController::GetStudio()
{
	return m_pStudio;
}

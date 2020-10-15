#pragma once

#include <Windows.h>
#include "RocLevel.h"
#include "RocSprite.h"
#include <ctime>

class Level_1_EndPage : public RocLevel
{
public:
	Level_1_EndPage(INT score)
	{
		m_score = score;
	};
	VOID Load() override;
	VOID Unload() override;
	VOID Render() override;
	VOID Update() override;
	VOID HandleKey(WPARAM wParam) override;

private:
	RocSprite* m_pGameOver = NULL;
	INT m_score;
	INT m_firstTime;
};


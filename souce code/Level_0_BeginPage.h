#pragma once

#include "Levels.h"
#include "RocSprite.h"

class Level_0_BeginPage: public RocLevel
{
public:
	VOID Load() override;
	VOID Unload() override;
	VOID Render() override;
	VOID Update() override;
	VOID HandleKey(WPARAM wParam) override;

private:
	RocSprite* m_pTitle = NULL;
	RocSprite* m_pPress = NULL;

	FLOAT m_alpha = 1.0f;
	BOOL m_loop = TRUE;
};

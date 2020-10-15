#pragma once

#include "Levels.h"
#include "RocSprite.h"

#define BARRAGE 1
#define BABEL  -1

class Level_0_ChoosePage: public RocLevel
{
public:
	VOID Load() override;
	VOID Unload() override;
	VOID Render() override;
	VOID Update() override;
	VOID HandleKey(WPARAM wParam) override;

private:
	RocSprite* m_pTitle = NULL;
	RocSprite* m_pBabelW = NULL;
	RocSprite* m_pBabelO = NULL;
	RocSprite* m_pBarrageW = NULL;
	RocSprite* m_pBarrageO = NULL;

	INT m_choice = BARRAGE;
};


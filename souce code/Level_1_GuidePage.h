#pragma once

#include <Windows.h>
#include "RocLevel.h"
#include "RocSprite.h"
#include <ctime>

class Level_1_GuidePage : public RocLevel
{
public:
	Level_1_GuidePage() { }
	~Level_1_GuidePage() { }
	VOID Load() override;
	VOID Unload() override;
	VOID Render() override;
	VOID Update() override;
	VOID HandleKey(WPARAM wParam) override;

private:
	RocSprite* m_pGuide = NULL;
};
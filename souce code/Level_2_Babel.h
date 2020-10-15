#pragma once

#include "Levels.h"
#include "RocObject.h"
#include "RocLevel.h"
#include "RocSprite.h"
#include <vector>
#include <ctime>

class Board : public RocObject
{
public:
	Board(FLOAT height);
	~Board() { };
	VOID Render() { }
	VOID RenderX(FLOAT height);
	BOOL ShouldDestroy() override;
	FLOAT GetHeight();
	FLOAT GetX1();
	FLOAT GetX2();
	INT GetRGB();

	VOID ForceSet(FLOAT height, FLOAT x1, FLOAT x2);

private:
	FLOAT m_height;
	FLOAT m_x1;
	FLOAT m_x2;

	INT rgb;
};

class Level_2_Babel: public RocLevel
{
public:
	VOID Load() override;
	VOID Unload() override;
	VOID Render() override;
	VOID Update() override;
	VOID HandleKey(WPARAM wParam) override;

private:
	FLOAT x = 0.0f;
	FLOAT xSpd = 0.0f;
	FLOAT y = 0.0f;
	FLOAT ySpd = 0.0f;
	
	INT m_startTime;
	FLOAT m_overload = 1;
	FLOAT m_height = 0;
	INT rgb;

	std::vector<Board*> boards;
};


#pragma once

#include "Levels.h"
#include "RocObject.h"
#include "RocLevel.h"
#include "RocSprite.h"
#include <vector>

class Enemy : public RocObject
{
public:
	Enemy();
	~Enemy() { };
	VOID Render() override;
	BOOL ShouldDestroy() override;
	BOOL IsIn();
	VOID SetIsIn();

private:
	BOOL isIn;
};

class Collectible : public RocObject
{
public:
	Collectible(RocSprite* pHeart);
	~Collectible() { };
	VOID Render() override;
	BOOL ShouldDestroy() override;

private:
	RocSprite* m_pHeart = NULL;
};

class Spark : public RocObject
{
public:
	Spark(RocSprite* pSpark);
	~Spark() { };
	VOID Render() override;
	BOOL ShouldDestroy() override;

private:
	RocSprite* m_pSpark = NULL;
};

class Bullet : public RocObject
{
public:
	Bullet(FLOAT x, FLOAT y, FLOAT xSpd, FLOAT ySpd);
	~Bullet() { };
	VOID Render() override;
	BOOL ShouldDestroy() override;

private:
	FLOAT r, g, b;
};


class Level_1_Barrage: public RocLevel
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

	FLOAT m_life = 100.0f;
	FLOAT m_energy = 0.0f;
	INT m_score = 0;
	BOOL m_crazyMode = FALSE;
	INT m_startCrazy = 0;
	FLOAT m_score_crazy = 0.0f;
	
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	std::vector<Collectible*> collectibles;
	Spark* sparka = NULL;

	RocSprite* m_pHeart;
	RocSprite* m_pSpark;
};


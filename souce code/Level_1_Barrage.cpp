#include "Level_1_Barrage.h"
#include "RocController.h"
#include "Level_1_EndPage.h"
#include <cmath>

VOID Level_1_Barrage::Load()
{
	PlaySound(L".\\Resources\\Musics\\beat1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	x = 500.0f;
	xSpd = 0.0f;
	y = 375.0f;
	ySpd = 0.0f;

	for (int i = 0; i < 5; ++i)
	{
		Enemy* a = new Enemy();
		enemies.emplace_back(a);
	}

	m_pHeart = new RocSprite(L".\\Resources\\Pictures\\heart.png", 50, 50);
	m_pSpark = new RocSprite(L".\\Resources\\Pictures\\spark.png", 50, 50);
}

VOID Level_1_Barrage::Unload()
{
	for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end();)
	{
		delete (*i);
		i = enemies.erase(i);
	}
	for (std::vector<Bullet*>::iterator i = bullets.begin(); i != bullets.end();)
	{
		delete (*i);
		i = bullets.erase(i);
	}
}

VOID Level_1_Barrage::Render()
{
	// 清屏
	if (!m_crazyMode)
		RocController::GetStudio()->ClearTheScreen(1.0f, 1.0f, 1.0f);
	else
		RocController::GetStudio()->ClearTheScreen(0.2f, 0.07f, 0.07f);

	// 显示增加生命道具
	for (std::vector<Collectible*>::iterator i = collectibles.begin(); i != collectibles.end(); ++i)
	{
		(*i)->Render();
	}

	// 显示能量道具
	if (sparka)
		sparka->Render();

	// 显示所有敌人
	for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		(*i)->Render();
	}

	// 显示所有子弹
	for (std::vector<Bullet*>::iterator i = bullets.begin(); i != bullets.end(); ++i)
	{
		(*i)->Render();
	}

	// 显示主角
	RocController::GetStudio()->FillCircle(0.0f, 0.0f, 0.0f, 0.8f, x, y, 20);

	// 显示生命
	if (!m_crazyMode)
	{
		RocController::GetStudio()->FillCircle(0.2f, 0.2f, 0.2f, 0.8f, 925, 683, 25);
		RocController::GetStudio()->FillSquare(1.0f, 1.0f, 1.0f, 0.8f, 925, (FLOAT)683 - m_life / 2.0f, 50);
	}
	else
	{
		RocController::GetStudio()->FillCircle(0.99f, 0.99f, 0.99f, 0.9f, 925, 683, 25);
		RocController::GetStudio()->FillSquare(0.2f, 0.07f, 0.07f, 0.8f, 925, (FLOAT)683 - m_life / 2.0f, 50);
	}
	m_pHeart->Draw(900, 660, 1.0f);

	// 显示能量
	if (!m_crazyMode)
	{
		RocController::GetStudio()->FillCircle(0.2f, 0.2f, 0.2f, 0.8f, 825, 683, 25);
		RocController::GetStudio()->FillSquare(1.0f, 1.0f, 1.0f, 0.8f, 825, (FLOAT)683 - m_energy / 2.0f, 50);
	}
	else
	{
		RocController::GetStudio()->FillCircle(0.99f, 0.99f, 0.99f, 0.9f, 825, 683, 25);
	}
	m_pSpark->Draw(800, 660, 1.0f);

	// 显示分数
	D2D1_RECT_F rect = D2D1::Rect(5, 5, 10000, 10000);
	WCHAR scoreOut[50];
	INT digits = 0, score = m_score;
	while (score > 0)
	{
		score /= 10;
		++digits;
	}
	if (score == 0) ++digits;
	swprintf_s(scoreOut, L"%d", m_score);
	RocController::GetStudio()->DrawText(scoreOut, digits, &rect);
}

VOID Level_1_Barrage::Update()
{
	// 边缘检测
	if (x > 980)
	{
		xSpd = -xSpd * 0.8;
		x = 980;
	}
	else if (x < 20)
	{
		xSpd = -xSpd * 0.8;
		x = 20;
	}
	if (y > 730)
	{
		ySpd = -ySpd * 0.8;
		y = 730;
	}
	else if (y < 20)
	{
		ySpd = -ySpd * 0.8;
		y = 20;
	}

	// 按键检测
	if (RocController::IsLeft() && xSpd > -6)
		if (xSpd < 0)
			xSpd -= 0.05f;
		else
			xSpd -= 0.1f;
	if (RocController::IsRight() && xSpd < 6)
		if (xSpd > 0)
			xSpd += 0.05f;
		else
			xSpd += 0.1f;
	if (RocController::IsUp() && ySpd > -6)
		if (ySpd < 0)
			ySpd -= 0.05f;
		else
			ySpd -= 0.1f;
	if (RocController::IsDown() && ySpd < 6)
		if (ySpd > 0)
			ySpd += 0.05f;
		else
			ySpd += 0.1f;

	xSpd -= xSpd * 0.005;
	ySpd -= ySpd * 0.005;


	// 主角碰撞检测
	for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		if ((x - (*i)->GetX()) * (x - (*i)->GetX()) + (y - (*i)->GetY()) * (y - (*i)->GetY()) < 2000)
		{
			FLOAT dX = (*i)->GetX() - x;
			FLOAT dY = (*i)->GetY() - y;
			FLOAT dD = dX * dX + dY * dY;
			if (dD < 1600)
			{
				(*i)->ChangeSpeed(-(*i)->GetVX() / 2.f + dX / 10.f, -(*i)->GetVY() / 2.f + dY / 10.f);
				xSpd = xSpd / 1.3f - dX / 25.f;
				ySpd = ySpd / 1.3f - dY / 25.f;
			}

			if(!m_crazyMode)
				m_life -= 1;
		}
	}

	// 子弹碰撞检测
	for (INT i = 0; i < enemies.size(); ++i)
		for (INT j = i + 1; j < bullets.size(); ++j)
		{
			FLOAT dX = enemies[i]->GetX() - bullets[j]->GetX();
			FLOAT dY = enemies[i]->GetY() - bullets[j]->GetY();
			FLOAT dD = dX * dX + dY * dY;
			if (dD < 450)
			{
				enemies[i]->Destroy();
				bullets[j]->Destroy();
				if (!m_crazyMode)
					m_score++;
			}
		}

	// 边缘检测
	for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		if ((*i)->IsIn())
		{
			if ((*i)->GetX() > 980)
			{
				(*i)->ChangeSpeedX(-(*i)->GetVX());
				(*i)->ChangeCoordX(980);
			}
			else if ((*i)->GetX() < 20)
			{
				(*i)->ChangeSpeedX(-(*i)->GetVX());
				(*i)->ChangeCoordX(20);
			}
			if ((*i)->GetY() > 730)
			{
				(*i)->ChangeSpeedY(-(*i)->GetVY());
				(*i)->ChangeCoordY(730);
			}
			else if ((*i)->GetY() < 20)
			{
				(*i)->ChangeSpeedY(-(*i)->GetVY());
				(*i)->ChangeCoordY(20);
			}
		}
		else if ((*i)->GetX() < 970 && (*i)->GetX() > 30 && (*i)->GetY() < 720 && (*i)->GetY() > 30)
			(*i)->SetIsIn();
	}

	// 小球互相碰撞检测
	for (INT i = 0; i < enemies.size(); ++i)
		for (INT j = i + 1; j < enemies.size(); ++j)
		{
			FLOAT dX = enemies[i]->GetX() - enemies[j]->GetX();
			FLOAT dY = enemies[i]->GetY() - enemies[j]->GetY();
			FLOAT dD = dX * dX + dY * dY;
			if (dD < 1600)
			{
				FLOAT arg1 = 2.5f, arg2 = 15.0f;

				FLOAT newIX = enemies[i]->GetVX() / arg1 + dX / arg2;
				FLOAT newIY = enemies[i]->GetVY() / arg1 + dY / arg2;

				FLOAT newJX = enemies[j]->GetVX() / arg1 - dX / arg2;
				FLOAT newJY = enemies[j]->GetVY() / arg1 - dY / arg2;

				enemies[i]->ChangeSpeed(newIX, newIY);
				enemies[j]->ChangeSpeed(newJX, newJY);
			}
		}

	// 吃生命检测
	for (std::vector<Collectible*>::iterator i = collectibles.begin(); i != collectibles.end();)
	{
		if (x - (*i)->GetX() < 50 && y - (*i)->GetY() < 50
		 && x - (*i)->GetX() > 0 && y - (*i)->GetY() > 0)
		{
			m_life = min(100, m_life + 5);
			delete (*i);
			i = collectibles.erase(i);
		}
		else
		{
			++i;
		}
	}

	// 吃能量检测
	if (sparka && x - sparka->GetX() < 50 && y - sparka->GetY() < 50
			   && x - sparka->GetX() > 0 && y - sparka->GetY() > 0)
	{
		m_energy += 33.4f;
		delete sparka;
		sparka = NULL;
	}

	// 小球销毁
	for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end();)
	{
		BOOL m = (*i)->ShouldDestroy();
		if (m)
		{
			delete (*i);
 			i = enemies.erase(i);
		}
		else
		{
			++i;
		}
	}

	// 子弹销毁
	for (std::vector<Bullet*>::iterator i = bullets.begin(); i != bullets.end();)
	{
		BOOL m = (*i)->ShouldDestroy();
		if (m)
		{
			delete (*i);
			i = bullets.erase(i);
		}
		else
		{
			++i;
		}
	}

	// 补充敌人
	INT max_enemy = 0;
	if (!m_crazyMode)
		max_enemy = min(m_score / 10 + 5, 15);
	else
		max_enemy = 100;
	for (INT i = 0; i < max_enemy - enemies.size(); ++i)
	{
		Enemy* a = new Enemy();
		enemies.emplace_back(a);
	}

	// 补充生命
	if (rand() % 500 == 1 && collectibles.size() < 2)
	{
		Collectible* c = new Collectible(m_pHeart);
		collectibles.emplace_back(c);
	}

	// 补充能量
	if (rand() % 1000 == 1 && sparka == NULL && !m_crazyMode)
	{
		sparka = new Spark(m_pSpark);
	}

	// 是否进入 crazymode
	if (m_energy >= 100 && !m_crazyMode)
	{
		PlaySound(L".\\Resources\\Musics\\crazy.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		m_crazyMode = TRUE;
		m_startCrazy = time(NULL);
	}
	
	// 是否退出 crazymode
	if (time(NULL) - m_startCrazy > 14 && m_startCrazy != 0)
	{
		PlaySound(L".\\Resources\\Musics\\beat1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		m_crazyMode = FALSE;
		m_energy = 0.0f;
		m_startCrazy = 0;

		for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end();)
		{
			delete (*i);
			i = enemies.erase(i);
		}
	}
		

	// 是否结束游戏
	if (m_life <= 0)
	{
		RocController::SwitchLevel(new Level_1_EndPage(m_score));
	}

	// 更新
	x += xSpd;
	y += ySpd;

	for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		(*i)->Update();
	}
	for (std::vector<Bullet*>::iterator i = bullets.begin(); i != bullets.end(); ++i)
	{
		(*i)->Update();
	}

	if(m_crazyMode)
	for (int i = 0; i < 12; ++i)
	{
		Bullet* b = new Bullet(x, y, xSpd + i, ySpd + i);
		bullets.emplace_back(b);
		b = new Bullet(x, y, -xSpd - i, -ySpd - i);
		bullets.emplace_back(b);
		b = new Bullet(x, y, xSpd + i, -ySpd - i);
		bullets.emplace_back(b);
		b = new Bullet(x, y, -xSpd - i, ySpd + i);
		bullets.emplace_back(b);
	}
}

VOID Level_1_Barrage::HandleKey(WPARAM wParam)
{
	switch (wParam)
	{
	case (int)'j':
	case (int)'J':
	case (int)'k':
	case (int)'K':
	case VK_LBUTTON:
	{
		if (!m_crazyMode)
		{
			Bullet* b = new Bullet(x, y, xSpd, ySpd);
			bullets.emplace_back(b);
			if (m_score > 10)
			{
				b = new Bullet(x, y, -xSpd, -ySpd);
				bullets.emplace_back(b);
			}
			if (m_score > 40)
			{
				b = new Bullet(x, y, xSpd, -ySpd);
				bullets.emplace_back(b);
				b = new Bullet(x, y, -xSpd, ySpd);
				bullets.emplace_back(b);
			}
		}
		else
		{
			for (int i = 0; i < 3; ++i)
			{
				Bullet* b = new Bullet(x, y, xSpd + i, ySpd + i);
				bullets.emplace_back(b);
				b = new Bullet(x, y, -xSpd - i, -ySpd - i);
				bullets.emplace_back(b);
				b = new Bullet(x, y, xSpd + i, -ySpd - i);
				bullets.emplace_back(b);
				b = new Bullet(x, y, -xSpd - i, ySpd + i);
				bullets.emplace_back(b);
			}
		}
	}
	default:
		break;
	}
}

Enemy::Enemy()
{
	isStatic = FALSE;
	isIn = FALSE;
	mustDestroy = FALSE;

	switch (rand() % 4)
	{
	case 0:  // 上
	{
		x = rand() % 1000;
		y = -30;
		if (rand() % 2)
			xSpd = (rand() % 200) / 100;
		else
			xSpd = -(rand() % 200) / 100;
		ySpd = (rand() % 300) / 100 + 2;

		break;
	}
	case 1:  // 下
	{
		x = rand() % 1000;
		y = 780;
		if (rand() % 2)
			xSpd = (rand() % 200) / 100;
		else
			xSpd = -(rand() % 200) / 100;
		ySpd = -(rand() % 300) / 100 - 2;

		break;
	}
	case 2:  // 左
	{
		x = -30;
		y = rand() % 750;
		if (rand() % 2)
			ySpd = (rand() % 200) / 100;
		else
			ySpd = -(rand() % 200) / 100;
		xSpd = (rand() % 300) / 100 + 2;

		break;
	}
	case 3:  // 右
	{
		x = 1030;
		y = rand() % 750;
		if (rand() % 2)
			ySpd = (rand() % 200) / 100;
		else
			ySpd = -(rand() % 200) / 100;
		xSpd = -(rand() % 300) / 100 - 2;

		break;
	}
	}
}

VOID Enemy::Render()
{
	RocController::GetStudio()->FillCircle(0.8f, 0.1f, 0.1f, 0.8f, x, y, 20);
}

BOOL Enemy::ShouldDestroy()
{
	return (x >= 1040 || x <= -40 || y > 790 || y < -40 || mustDestroy);
}

BOOL Enemy::IsIn()
{
	return isIn;
}

VOID Enemy::SetIsIn()
{
	isIn = TRUE;
}

Bullet::Bullet(FLOAT cx, FLOAT cy, FLOAT cxSpd, FLOAT cySpd)
{
	isStatic = FALSE;

	x = cx;
	y = cy;
	FLOAT argM = sqrt(cxSpd * cxSpd + cySpd * cySpd);
	xSpd = cxSpd / argM * 4;
	ySpd = cySpd / argM * 4;

	switch (rand() % 5)
	{
	case 0:
		r = 1.0f; g = 0.847f; b = 0.129f;
		break;
	case 1:
		r = 1.0f; g = 0.145f; b = 0.463f;
		break;
	case 2:
		r = 0.988f; g = 0.086f; b = 0.925f;
		break;
	case 3:
		r = 0.161f; g = 0.463f; b = 1.0f;
		break;
	case 4:
		r = 0.161f; g = 0.467f; b = 1.0f;
		break;
	default:
		r = 0.2f; g = 0.2f; b = 0.2f;
		break;
	}
}

VOID Bullet::Render()
{
	RocController::GetStudio()->FillCircle(r, g, b, 1.0f, x, y, 4);
}

BOOL Bullet::ShouldDestroy()
{
	return (x >= 1040 || x <= -40 || y > 790 || y < -40 || mustDestroy);
}

Collectible::Collectible(RocSprite* pHeart)
{
	m_pHeart = pHeart;

	x = rand() % 750 + 100;
	y = rand() % 500 + 100;

	isStatic = TRUE;
}

VOID Collectible::Render()
{
	m_pHeart->Draw(x, y, 0.8f);
}

BOOL Collectible::ShouldDestroy()
{
	return mustDestroy;
}

Spark::Spark(RocSprite* pSpark)
{
	m_pSpark = pSpark;

	x = rand() % 750 + 100;
	y = rand() % 500 + 100;

	isStatic = TRUE;
}

VOID Spark::Render()
{
	m_pSpark->Draw(x, y, 1.0f);
}

BOOL Spark::ShouldDestroy()
{
	return mustDestroy;
}

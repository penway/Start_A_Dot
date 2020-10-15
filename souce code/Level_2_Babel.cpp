#include "Level_2_Babel.h"

VOID Level_2_Babel::Load()
{
	PlaySound(L".\\Resources\\Musics\\beat2.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	x = 500;
	y = 1;
	xSpd = 0;
	ySpd = 10;
	rgb = 0x1F1F1F;

	m_height = 0;
	m_overload = 1;

	for (INT i = 0; i < 4; ++i)
	{
		Board* b = new Board(m_height);
		b->ForceSet(450 + i * 100, 200, 800);
		boards.emplace_back(b);
	}

	m_startTime = time(0);
}

VOID Level_2_Babel::Unload()
{
	
}

VOID Level_2_Babel::Render()
{
	RocController::GetStudio()->ClearTheScreen(0.071f, 0.071f, 0.071f);
	RocController::GetStudio()->FillCircle(rgb, 1.0f, x, 750 - (y - m_height), 20);

	for (std::vector<Board*>::iterator i = boards.begin(); i != boards.end(); ++i)
	{
		(*i)->RenderX(m_height);
	}

	RocController::GetStudio()->FillRectangle(1.0f, 1.0f, 1.0f, 1.0f, 0, 0, 250, 780);
	RocController::GetStudio()->FillRectangle(1.0f, 1.0f, 1.0f, 1.0f, 750, 0, 400, 780);


	// ÏÔÊ¾·ÖÊý
	D2D1_RECT_F rect = D2D1::Rect(5, 5, 10000, 10000);
	WCHAR scoreOut[50];
	INT digits = 0, score = m_height;
	while (score > 0)
	{
		score /= 10;
		++digits;
	}
	if (score == 0) ++digits;
	swprintf_s(scoreOut, L"%d", (INT)m_height);
	RocController::GetStudio()->DrawText(scoreOut, digits, &rect);
}

VOID Level_2_Babel::Update()
{
	m_overload = max(min((FLOAT)(time(NULL) - m_startTime) / 10.f, 3.f), 1.f);
	m_height += m_overload;

	x += xSpd;
	y += ySpd;
	ySpd -= 0.1 * m_overload;

	if (x < 250)
		x = 750;
	if (x > 750)
		x = 250;

	if (RocController::IsLeft() && xSpd > -3)
		if (xSpd < 0)
			xSpd -= 0.3f;
		else
			xSpd -= 0.3f;
	if (RocController::IsRight() && xSpd < 3)
		if (xSpd > 0)
			xSpd += 0.3f;
		else
			xSpd += 0.3f;

	if (xSpd > 0)
		xSpd -= 0.1;
	else if (xSpd < 0)
		xSpd += 0.1;

	for (std::vector<Board*>::iterator i = boards.begin(); i != boards.end();)
	{
		if ((*i)->GetHeight() < m_height - 400)
		{
			(*i)->Destroy();
			delete (*i);
			i = boards.erase(i);
		}
		else
		{
			++i;
		}
	}

	BOOL hasHigh = FALSE;
	for (std::vector<Board*>::iterator i = boards.begin(); i != boards.end(); ++i)
	{
		if ((*i)->GetHeight() - m_height > 780)
			hasHigh = TRUE;
	}
	if (!hasHigh)
	{
		Board* b = new Board(m_height + m_overload * 50);
		boards.emplace_back(b);
	}

	for (std::vector<Board*>::iterator i = boards.begin(); i != boards.end(); ++i)
	{
		if (y - (*i)->GetHeight() <= 5 - m_overload && y - (*i)->GetHeight() >= -3 + m_overload && x > (*i)->GetX1() && x < (*i)->GetX2() && ySpd < 0)
		{
			ySpd = 6 * m_overload;
			rgb = (*i)->GetRGB();
		}
	}

	if (y < m_height - 400)
	{
		RocController::SwitchLevel(new Level_1_EndPage(m_height));
	}
}

VOID Level_2_Babel::HandleKey(WPARAM wParam)
{
	return VOID();
}

Board::Board(FLOAT height)
{
	isStatic = TRUE;

	m_x1 = rand() % 350 + 300;
	m_x2 = rand() % 120 + m_x1 + 50;

	m_height = height + 800;

	switch (rand() % 5)
	{
	case 0:
		rgb = 0xFFD821;
		break;
	case 1:
		rgb = 0xFF2576;
		break;
	case 2:
		rgb = 0xFC16EC;
		break;
	case 3:
		rgb = 0x2976FF;
		break;
	case 4:
		rgb = 0x16F48A;
		break;
	}
}

VOID Board::RenderX(FLOAT height)
{
	FLOAT y = 780 - (m_height - height);
	RocController::GetStudio()->DrawLine(m_x1, y, m_x2, y, rgb, 1.0f, 10);
}

BOOL Board::ShouldDestroy()
{
	return mustDestroy;
}

FLOAT Board::GetHeight()
{
	return m_height;
}

FLOAT Board::GetX1()
{
	return m_x1;
}

FLOAT Board::GetX2()
{
	return m_x2;
}

INT Board::GetRGB()
{
	return rgb;
}

VOID Board::ForceSet(FLOAT height, FLOAT x1, FLOAT x2)
{
	m_height = height;
	m_x1 = x1;
	m_x2 = x2;
}

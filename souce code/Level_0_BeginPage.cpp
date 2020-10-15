#include "Level_0_BeginPage.h"
#include "RocController.h"

VOID Level_0_BeginPage::Load()
{
	PlaySound(L".\\Resources\\Musics\\main1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	m_pTitle = new RocSprite(L".\\Resources\\Pictures\\title.png", 800, 300);
	m_pPress = new RocSprite(L".\\Resources\\Pictures\\press.png", 416, 78);
	m_alpha = 1.0;
	m_loop = TRUE;
}

VOID Level_0_BeginPage::Unload()
{
	
}

VOID Level_0_BeginPage::Render()
{
	RocController::GetStudio()->ClearTheScreen(1.0f, 1.0f, 1.0f);
	m_pTitle->Draw(95, 100, 1.0f);
	m_pPress->Draw(280, 480, m_alpha);
}

VOID Level_0_BeginPage::Update()
{
	if (m_loop)
		m_alpha -= 0.01;
	else
		m_alpha += 0.01;
	if (m_alpha <= 0.1)
		m_loop = FALSE;
	if (m_alpha >= 1.1)
		m_loop = TRUE;
}

VOID Level_0_BeginPage::HandleKey(WPARAM wParam)
{
	RocController::SwitchLevel(new Level_0_ChoosePage);
}

#include "Level_1_EndPage.h"
#include "Level_0_BeginPage.h"

VOID Level_1_EndPage::Load()
{
    PlaySound(L".\\Resources\\Musics\\high1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    m_pGameOver = new RocSprite(L".\\Resources\\Pictures\\gameover.png", 800, 300);
    m_firstTime = time(0);
}

VOID Level_1_EndPage::Unload()
{

}

VOID Level_1_EndPage::Render()
{
    RocController::GetStudio()->ClearTheScreen(1.0f, 1.0f, 1.0f);
    m_pGameOver->Draw(100, 100, 1.f);

    D2D1_RECT_F rect = D2D1::Rect(390, 500, 10000, 10000);
    WCHAR scoreOut[50];
    INT digits = 0, score = m_score;
    while (score > 0)
    {
        score /= 10;
        digits++;
    }
    swprintf_s(scoreOut, L"Your Score is %d", m_score);
    RocController::GetStudio()->DrawText(scoreOut, 15 + digits, &rect);
}

VOID Level_1_EndPage::Update()
{
    
}

VOID Level_1_EndPage::HandleKey(WPARAM wParam)
{
    if(time(0) - m_firstTime > 1)
        RocController::SwitchLevel(new Level_0_BeginPage);
}

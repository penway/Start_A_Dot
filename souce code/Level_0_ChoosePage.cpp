#include "Level_0_ChoosePage.h"

VOID Level_0_ChoosePage::Load()
{
    m_pTitle = new RocSprite(L".\\Resources\\Pictures\\title.png", 800, 300);
    m_pBabelO = new RocSprite(L".\\Resources\\Pictures\\babelO.png", 152, 114);
    m_pBabelW = new RocSprite(L".\\Resources\\Pictures\\babelW.png", 152, 114);
    m_pBarrageO = new RocSprite(L".\\Resources\\Pictures\\barrageO.png", 152, 114);
    m_pBarrageW = new RocSprite(L".\\Resources\\Pictures\\barrageW.png", 152, 114);
}

VOID Level_0_ChoosePage::Unload()
{
    delete m_pTitle;
    delete m_pBabelO;
    delete m_pBabelW;
    delete m_pBarrageO;
    delete m_pBarrageW;
}

VOID Level_0_ChoosePage::Render()
{
    RocSprite* babel;
    RocSprite* barrage;
    if (m_choice == BARRAGE)
    {
        babel = m_pBabelW;
        barrage = m_pBarrageO;
    }
    else
    {
        babel = m_pBabelO;
        barrage = m_pBarrageW;
    }

    RocController::GetStudio()->ClearTheScreen(1.0f, 1.0f, 1.0f);
    m_pTitle->Draw(95, 100, 1.0f);
    babel->Draw(590, 480, 1.0f);
    barrage->Draw(240, 480, 1.0f);
}

VOID Level_0_ChoosePage::Update()
{
    return VOID();
}

VOID Level_0_ChoosePage::HandleKey(WPARAM wParam)
{
    switch (wParam)
    {
    case (int)'A':
    case (int)'a':
    case (int)'D':
    case (int)'d':
    case VK_LEFT:
    case VK_RIGHT:
        m_choice *= -1;
        break;

    case (int)'J':
    case (int)'j':
    case (int)'K':
    case (int)'k':
    case (int)'L':
    case (int)'l':
    case VK_RETURN:
        if (m_choice == BARRAGE)
        {
            RocController::SwitchLevel(new Level_1_GuidePage);
        }
        else
        {
            RocController::SwitchLevel(new Level_2_Babel);
        }
        break;
    default:
        break;
    }
}

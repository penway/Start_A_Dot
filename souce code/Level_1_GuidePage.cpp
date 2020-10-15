#include "Level_1_GuidePage.h"
#include "Level_1_Barrage.h"

VOID Level_1_GuidePage::Load()
{
    m_pGuide = new RocSprite(L".\\Resources\\Pictures\\guide0.png", 1000, 750);
}

VOID Level_1_GuidePage::Unload()
{
    delete m_pGuide;
}

VOID Level_1_GuidePage::Render()
{
    RocController::GetStudio()->ClearTheScreen(1.0f, 1.0f, 1.0f);
    m_pGuide->Draw(0, 0, 1.f);
}

VOID Level_1_GuidePage::Update()
{

}

VOID Level_1_GuidePage::HandleKey(WPARAM wParam)
{
    RocController::SwitchLevel(new Level_1_Barrage);
}
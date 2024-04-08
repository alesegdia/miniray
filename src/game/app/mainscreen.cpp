#include "game/app/mainscreen.h"

#include "glrayfw/render/renderer.h"

#include "game/physics/contactlistener.h"
#include "game/app/gamescreen.h"

#include "game/app/persistentdata.h"

void MainScreen::Setup(const std::vector<std::string>& args)
{
    engine()->Reset(new ContactListener());
    PlayerPersistentData::GetInstance().GetRunPersistentData().ResetFloor();
}

void MainScreen::Update(uint32_t delta)
{
    engine()->renderer()->Update();
}

void MainScreen::Render()
{
    engine()->cam()->position(cml::vector3f(0, 0, 0));

    engine()->renderer()->RenderBegin();
    {
        uint32_t time = SDL_GetTicks();
        float r = sinf((float(time)) / 10);
        float g = sinf((float(time)) / 40);
        float b = sinf((float(time)) / 40);
        engine()->renderer()->SetPlayerHealth(0.0f);
        engine()->renderer()->renderText("Miniray", -0.5, 0, cml::vector4f(r, 1, b, 1), 2, 2);

        r = sinf((float(time)) / 20);
        g = sinf((float(time)) / 20);
        b = sinf((float(time)) / 20);

        engine()->renderer()->renderText("Press space to start game", -0.8, -0.5, cml::vector4f(r, g, b, 1), 1, 1);

    }
    engine()->renderer()->RenderFinish();
}

void MainScreen::Cleanup()
{
}

void MainScreen::HandleEvent(SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
            SetNextScreen(std::make_shared<GameScreen>());
            break;
        }
        break;
    }
}












void NextFloorScreen::Setup(const std::vector<std::string>& args)
{
    engine()->Reset(new ContactListener());
    PlayerPersistentData::GetInstance().GetRunPersistentData().IncreaseFloor();
}

void NextFloorScreen::Update(uint32_t delta)
{
    engine()->renderer()->Update();
}

void NextFloorScreen::Render()
{
    engine()->cam()->position(cml::vector3f(0, 0, 0));
    engine()->renderer()->RenderBegin();

    uint32_t time = SDL_GetTicks();
    float r = sinf((float(time)) / 10);
    float g = sinf((float(time)) / 40);
    float b = sinf((float(time)) / 40);
    engine()->renderer()->SetPlayerHealth(0.0f);
    std::string txt = "NEXT FLOOR: " + std::to_string(PlayerPersistentData::GetInstance().GetRunPersistentData().GetCurrentFloor() + 1);
    engine()->renderer()->renderText(txt.c_str(), -0.8, 0, cml::vector4f(r, 1, b, 1), 2, 2);

    r = sinf((float(time)) / 20);
    g = sinf((float(time)) / 20);
    b = sinf((float(time)) / 20);

    engine()->renderer()->renderText("Press space to continue", -0.8, -0.5, cml::vector4f(r, g, b, 1), 1, 1);

    engine()->renderer()->RenderFinish();

}

void NextFloorScreen::Cleanup()
{
}

void NextFloorScreen::HandleEvent(SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
            SetNextScreen(std::make_shared<GameScreen>());
            break;
        }
        break;
    }
}






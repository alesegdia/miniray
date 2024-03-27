#include "app.h"
#include "mainscreen.h"
#include "game/render/assets.h"


App::App(int w, int h) : SDLGLApp(w, h) {}

App::~App() {}

void App::SetScreen(std::shared_ptr<Screen> newScreen)
{
    if (m_currentScreen != nullptr)
    {
        m_currentScreen->Cleanup();
    }
    m_currentScreen = newScreen;
    m_currentScreen->SetEngine(engine());
    m_currentScreen->Setup(GetArgs());
}

void App::Setup(const std::vector<std::string>& args)
{
    Assets::GetInstance().Prepare(GL());
    SetScreen(std::make_shared<MainScreen>());
}

void App::Update(uint32_t delta)
{
    if (m_currentScreen->GetNextScreen() != nullptr)
    {
        SetScreen(m_currentScreen->GetNextScreen());
    }
    else
    {
        m_currentScreen->Update(delta);
    }
}

void App::Render()
{
    m_currentScreen->Render();
}

void App::Cleanup()
{
    m_currentScreen->Cleanup();
    Assets::GetInstance().Clean();
}

void App::HandleEvent(SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            Stop();
        break;
    }

    m_currentScreen->HandleEvent(event);
}

void App::PostUpdate()
{
    if (!m_currentScreen->DoesRequestExit())
    {
        m_currentScreen->PostUpdate();
    }
}

void App::PreUpdate(uint32_t delta)
{
    if (!m_currentScreen->DoesRequestExit())
    {
        m_currentScreen->PreUpdate(delta);
    }
}

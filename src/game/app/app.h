#pragma once

#include <memory>
#include <vector>
#include <SDL.h>

#include <glrayfw/app/sdlglapp.h>

class Screen;

class App : public SDLGLApp
{
public:
    App(int w, int h);
    virtual ~App();

private:
    void SetScreen(std::shared_ptr<Screen> newScreen);
    void Setup(const std::vector<std::string>& args) override;
    void Update(uint32_t delta) override;
    void Render() override;
    void Cleanup() override;
    void HandleEvent(SDL_Event& event) override;
    void PostUpdate() override;
    void PreUpdate(uint32_t delta) override;

    std::shared_ptr<Screen> m_currentScreen = nullptr;
};

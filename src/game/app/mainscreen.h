#pragma once

#include "screen.h"


class MainScreen : public Screen
{
public:
    void Setup(const std::vector<std::string>& args) override;

    void Update(uint32_t delta) override;

    void Render() override;

    void Cleanup() override;

    void HandleEvent(SDL_Event& event) override;
};


class NextFloorScreen : public Screen
{
public:
    void Setup(const std::vector<std::string>& args) override;

    void Update(uint32_t delta) override;

    void Render() override;

    void Cleanup() override;

    void HandleEvent(SDL_Event& event) override;
};

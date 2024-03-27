

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "glrayfw/app/engine.h"


class Screen
{
public:
	virtual ~Screen() {}
	virtual void Update(uint32_t delta) = 0;

	virtual void Render() = 0;

	virtual void Setup(const std::vector<std::string>& args) = 0;

	virtual void Cleanup() = 0;

	virtual void HandleEvent(SDL_Event& event) = 0;

	virtual void PostUpdate() final
	{
		engine()->PostUpdate();
	}

	virtual void PreUpdate(uint32_t delta) final
	{
		engine()->PreUpdate(delta);
	}

	bool DoesRequestExit()
	{
		return m_requestsExit;
	}

	void SetEngine(const std::shared_ptr<Engine>& engine)
	{
		m_engine = engine;
	}

	std::shared_ptr<Screen> GetNextScreen()
	{
		return m_nextScreen;
	}

protected:
	void RequestExit()
	{
		m_requestsExit = true;
	}

	const std::shared_ptr<Engine>& engine()
	{
		return m_engine;
	}

	void SetNextScreen(std::shared_ptr<Screen> scr)
	{
		m_nextScreen = scr;
	}

private:
	bool m_requestsExit = false;
	std::shared_ptr<Engine> m_engine;
	std::shared_ptr<Screen> m_nextScreen = nullptr;

};




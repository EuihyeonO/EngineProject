#pragma once
#include "BaseHeader.h"
#include <iostream>

class Engine
{
public:
	static void PlayEngine(HINSTANCE hInstance, int nCmdShow);

	void EngineStart(HINSTANCE hInstance, int nCmdShow);
	void EngineLoop();
	void EngineEnd();

	Engine(const Engine& _Other) = delete;
	Engine(Engine&& _Other) noexcept = delete;
	Engine& operator=(const Engine& _Other) = delete;
	Engine& operator=(Engine&& _Other) noexcept = delete;

protected:

private:
	void Update();
	void Render();

	static Engine* GetInstance()
	{
		static Engine Instance;
		return &Instance;
	}

	Engine();
	~Engine();

	static bool isEngineOn;
};


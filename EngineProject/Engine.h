#pragma once
#include "BaseHeader.h"
#include "EngineLevelManager.h"

#include <iostream>

class Engine
{
public:
	template<typename LevelManagerType, typename = std::enable_if_t<std::is_base_of_v<EngineLevelManager, LevelManagerType>>>
	static void PlayEngine(HINSTANCE hInstance, int nCmdShow)
	{
		//혹시나 main함수 말고 다른데서 호출하면 안된다
		if (isEngineOn == true)
		{
			std::cerr << "Why do you call \"PlayEngine\"?" << std::endl;
			return;
		}

		isEngineOn = true;

		std::locale::global(std::locale("korean"));

		std::shared_ptr<LevelManagerType> NewLevelManager = std::make_shared<LevelManagerType>();
		LevelManager = NewLevelManager;

		GetInstance()->EngineStart(hInstance, nCmdShow);
		GetInstance()->EngineLoop();
		GetInstance()->EngineEnd();
	}

	static void PlayEngine(HINSTANCE hInstance, int nCmdShow);

	void EngineStart(HINSTANCE hInstance, int nCmdShow);
	void EngineLoop();
	void EngineEnd();

	Engine(const Engine& _Other) = delete;
	Engine(Engine&& _Other) noexcept = delete;
	Engine& operator=(const Engine& _Other) = delete;
	Engine& operator=(Engine&& _Other) noexcept = delete;

	static std::pair<float, float> GetViewPortSize()
	{
		return ViewPortSize;
	}

protected:

private:
	void Update();
	void Render();
	void Loop();

	void CreateEngineGUI();

	static Engine* GetInstance()
	{
		static Engine Instance;
		return &Instance;
	}

	Engine();
	~Engine();

	static bool isEngineOn;
	static std::pair<float, float> ViewPortSize;
	static std::shared_ptr<EngineLevelManager> LevelManager;
};


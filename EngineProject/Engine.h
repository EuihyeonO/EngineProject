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
			EngineDebug::LogErrorMsg(L"PlayEngine을 임의로 호출하지 마세요.");
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

	void EngineStart(HINSTANCE hInstance, int nCmdShow);
	void EngineLoop();
	void EngineEnd();

	Engine& operator=(const Engine& _Other) = delete;
	Engine& operator=(Engine&& _Other) noexcept = delete;

protected:

private:
	static Engine* GetInstance()
	{
		static Engine Instance;
		return &Instance;
	}

	Engine();
	~Engine();

	Engine(const Engine& _Other) = delete;
	Engine(Engine&& _Other) noexcept = delete;

private:
	void Update();
	void Render();
	void Loop();

	void CreateEngineGUI();

	static bool isEngineOn;
	static std::shared_ptr<EngineLevelManager> LevelManager;
};


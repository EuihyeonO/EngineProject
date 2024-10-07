#pragma once
#include "EngineObjectBase.h"
#include "EngineLevel.h"

#include <memory>
#include <unordered_map>
#include <string_view>
#include <iostream>

class EngineLevelManager : public EngineObjectBase
{
	friend class Engine;
public:
	EngineLevelManager();
	~EngineLevelManager();

	EngineLevelManager(const EngineLevelManager& _Other) = delete;
	EngineLevelManager(EngineLevelManager&& _Other) noexcept = delete;
	EngineLevelManager& operator=(const EngineLevelManager& _Other) = delete;
	EngineLevelManager& operator=(EngineLevelManager&& _Other) noexcept = delete;

	template<typename LevelType, typename = std::enable_if_t<std::is_base_of_v<EngineLevel, LevelType>>>
	std::shared_ptr<LevelType> CreateLevel(std::string_view _LevelName)
	{
		if (Levels.find(_LevelName.data()) != Levels.end())
		{
			std::string LevelMame = _LevelName.data();
			EngineDebug::LogErrorMsg(L"생성하고자 하는 레벨이 이미 존재합니다.");
			return nullptr;
		}

		std::shared_ptr<LevelType> NewLevel = std::make_shared<LevelType>();
		NewLevel->Init();

		Levels[_LevelName.data()] = NewLevel;

		return NewLevel;
	}

	void LevelChange(std::string_view _NextLevelName);

	virtual void Start() override final;
	virtual void Update(float _DeltaTime) override final;

protected:

private:
	void Init() override final{}
	void End() override final { OnEnd(); }
	void OnCreated() override final {}
	void OnDestroyed() override final
	{
		CurrentLevel = nullptr;
	}
	
	void Destroy() override final
	{
		for (const std::pair< std::string, std::shared_ptr<EngineLevel>> Level : Levels)
		{
			Level.second->Destroy();
		}

		Levels.clear();
		OnDestroyed();
	}

	void Render() override final
	{
		if (CurrentLevel != nullptr)
		{
			CurrentLevel->RenderSetting();
			CurrentLevel->Render();
		}
	}

	std::shared_ptr<EngineLevel> CurrentLevel = nullptr;
	std::unordered_map<std::string, std::shared_ptr<EngineLevel>> Levels;
};


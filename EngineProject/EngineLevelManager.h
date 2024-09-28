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
		NewLevel->OnCreated();

		Levels[_LevelName.data()] = NewLevel;

		return NewLevel;
	}

	void LevelChange(std::string_view _NextLevelName)
	{
		std::unordered_map<std::string, std::shared_ptr<EngineLevel>>::iterator FindIter = Levels.find(_NextLevelName.data());

		if (FindIter == Levels.end())
		{
			std::string NextLevelName = _NextLevelName.data();
			EngineDebug::LogErrorMsg(L"변경하고자 하는 레벨이 생성되지 않은 레벨입니다. NextLevel : " + EngineString::StringToWString(NextLevelName));

			return;
		}

		if (FindIter->second == CurrentLevel)
		{
			std::string NextLevelName = _NextLevelName.data();
			EngineDebug::LogErrorMsg(L"변경하고자 하는 레벨이 현재 레벨과 동일합니다. Level : " + EngineString::StringToWString(NextLevelName));
			return;
		}

		if (CurrentLevel != nullptr)
		{
			CurrentLevel->SetActivate(false);
		}

		CurrentLevel = FindIter->second;
		CurrentLevel->SetActivate(true);
	}

	virtual void Start() override final;
	virtual void Update() override final;

protected:

private:

	virtual void End() override final{}
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


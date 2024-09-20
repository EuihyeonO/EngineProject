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
	void CreateLevel(std::string_view _LevelName)
	{
		if (Levels.find(_LevelName.data()) != Levels.end())
		{
			std::string LevelMame = _LevelName.data();
			std::cerr << "Error : Level(LevelName : " + LevelMame + ") is already created." << std::endl;
			return;
		}

		std::shared_ptr<LevelType> NewLevel = std::make_shared<LevelType>();
		NewLevel->OnCreated();

		Levels[_LevelName.data()] = NewLevel;
	}

	void LevelChange(std::string_view _NextLevelName)
	{
		std::unordered_map<std::string, std::shared_ptr<EngineLevel>>::iterator FindIter = Levels.find(_NextLevelName.data());

		if (FindIter == Levels.end())
		{
			std::string NextLevelName = _NextLevelName.data();
			std::cerr << "Level that you try to change is not been created. tried LevelName is " + NextLevelName << std::endl;

			return;
		}

		if (FindIter->second == CurrentLevel)
		{
			std::string NextLevelName = _NextLevelName.data();
			std::cerr << "Level that you try to change is same currentlevel. tried LevelName is " + NextLevelName << std::endl;

			return;
		}

		if (CurrentLevel != nullptr)
		{
			CurrentLevel->End();
		}

		CurrentLevel = FindIter->second;
		CurrentLevel->Start();
	}

protected:

private:
	void LevelUpdate();
	void OnCreated() override final {}

	std::shared_ptr<EngineLevel> CurrentLevel = nullptr;
	std::unordered_map<std::string, std::shared_ptr<EngineLevel>> Levels;
};


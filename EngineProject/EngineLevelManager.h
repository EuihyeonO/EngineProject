#pragma once
#include "EngineObjectBase.h"
#include "EngineLevel.h"

#include <memory>
#include <unordered_map>
#include <string_view>
#include <iostream>

class EngineLevelManager : public EngineObjectBase
{

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

	void Update() override final;
protected:

private:
	void OnCreated() override final {}

	std::unordered_map<std::string, std::shared_ptr<EngineLevel>> Levels;
};


#include "EngineLevelManager.h"

EngineLevelManager::EngineLevelManager()
{
}

EngineLevelManager::~EngineLevelManager()
{
}

void EngineLevelManager::Start()
{
	OnStart();
}

void EngineLevelManager::Update()
{
	OnUpdate();
	
	if (CurrentLevel != nullptr)
	{
		CurrentLevel->Update();
	}
}

void EngineLevelManager::LevelChange(std::string_view _NextLevelName)
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

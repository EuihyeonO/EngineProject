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
		EngineDebug::LogErrorMsg(L"�����ϰ��� �ϴ� ������ �������� ���� �����Դϴ�. NextLevel : " + EngineString::StringToWString(NextLevelName));

		return;
	}

	if (FindIter->second == CurrentLevel)
	{
		std::string NextLevelName = _NextLevelName.data();
		EngineDebug::LogErrorMsg(L"�����ϰ��� �ϴ� ������ ���� ������ �����մϴ�. Level : " + EngineString::StringToWString(NextLevelName));
		return;
	}

	if (CurrentLevel != nullptr)
	{
		CurrentLevel->SetActivate(false);
	}

	CurrentLevel = FindIter->second;
	CurrentLevel->SetActivate(true);
}

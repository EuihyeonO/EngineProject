#include "EngineLevelManager.h"

EngineLevelManager::EngineLevelManager()
{
}

EngineLevelManager::~EngineLevelManager()
{
}

void EngineLevelManager::Update()
{
	for (const std::pair<std::string, std::shared_ptr<EngineLevel>>& Level : Levels)
	{
		Level.second->Update();
	}
}
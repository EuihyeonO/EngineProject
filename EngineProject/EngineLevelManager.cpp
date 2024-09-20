#include "EngineLevelManager.h"

EngineLevelManager::EngineLevelManager()
{
}

EngineLevelManager::~EngineLevelManager()
{
}

void EngineLevelManager::LevelUpdate()
{
	CurrentLevel->Update();
	CurrentLevel->ActorUpdate();
}

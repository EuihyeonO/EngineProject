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

#include "ContentLevelManager.h"
#include "TestLevel.h"

ContentLevelManager::ContentLevelManager()
{
}

ContentLevelManager::~ContentLevelManager()
{
}

void ContentLevelManager::Start()
{
	CreateLevel<TestLevel>("TestLevel");

	LevelChange("TestLevel");
}

void ContentLevelManager::Update()
{
}

void ContentLevelManager::End()
{
}

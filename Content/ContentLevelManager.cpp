#include "ContentLevelManager.h"
#include "TestLevel.h"
#include "EngineLoader.h"
#include "EngineDirectX.h"

ContentLevelManager::ContentLevelManager()
{
}

ContentLevelManager::~ContentLevelManager()
{
}

void ContentLevelManager::Start()
{
	EngineLoader::LoadAllShader();
	EngineLoader::LoadAllSampler();

	EngineLoader::LoadAllBlendState();
	EngineLoader::LoadAllRasterizer();
	EngineLoader::LoadAllDepthStencil();

	EngineLoader::LoadAllFile(ExtensionType::FBX);
	
	CreateLevel<TestLevel>("TestLevel");
	LevelChange("TestLevel");
}

void ContentLevelManager::Update()
{
}

void ContentLevelManager::End()
{
}

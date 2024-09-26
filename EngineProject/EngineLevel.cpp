#include "EngineLevel.h"
#include "EngineActor.h"
#include "EngineDirectX.h"

EngineLevel::EngineLevel()
{
}

EngineLevel::~EngineLevel()
{
}

void EngineLevel::Start()
{
	OnStart();
}

void EngineLevel::End()
{
	OnEnd();
}

void EngineLevel::Update()
{
	OnUpdate();

	for (const std::pair<std::string, std::shared_ptr<EngineActor>> Actor : Actors)
	{
		Actor.second->Update();
	}
}

#include "EngineResourceManager.h"

void EngineLevel::RenderSetting()
{
	//EngineDirectX::GetInstance()->SetMainViewport();
	//EngineDirectX::GetInstance()->ClearMainRenderTarget();
	//EngineDirectX::GetInstance()->SetRenderTarget(EngineDirectX::GetMainRTV(), EngineResourceManager::FindDepthStencil("BaseDepthStencil").DSV);
	//EngineDirectX::GetInstance()->SetDepthStencilState(EngineResourceManager::FindDepthStencil("BaseDepthStencil").DSState);
	//EngineDirectX::GetInstance()->SetRasterizerState(EngineResourceManager::FindRasterizerState("Solid"));
}

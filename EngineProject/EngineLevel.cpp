#include "EngineLevel.h"
#include "EngineActor.h"
#include "EngineDirectX.h"

EngineLevel::EngineLevel()
{
}

EngineLevel::~EngineLevel()
{
}

void EngineLevel::ActorUpdate()
{
	for (const std::pair<std::string, std::shared_ptr<EngineActor>> Actor : Actors)
	{
		Actor.second->Update();
		Actor.second->ComponentUpdate();
	}
}
#include "EngineResourceManager.h"

void EngineLevel::RenderSetting()
{
	EngineDirectX::GetInstance()->SetMainViewport();
	EngineDirectX::GetInstance()->ClearMainRenderTarget();
	EngineDirectX::GetInstance()->SetRenderTarget(EngineDirectX::GetMainRTV(), nullptr);
	EngineDirectX::GetInstance()->SetDepthStencilState(EngineResourceManager::FindDepthStencil("BaseDepthStencil").DSState);
	EngineDirectX::GetInstance()->SetRasterizerState(EngineResourceManager::FindRasterizerState("Solid"));
}

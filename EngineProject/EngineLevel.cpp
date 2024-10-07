#include "EngineLevel.h"
#include "EngineActor.h"
#include "EngineDirectX.h"
#include "EngineRenderTarget.h"
#include "EngineResourceManager.h"

EngineLevel::EngineLevel()
{
}

EngineLevel::~EngineLevel()
{
}

void EngineLevel::Init()
{
	OnCreated();
}

void EngineLevel::Start()
{
	LevelRenderTarget = EngineRenderTarget::CreateRenderTarget("LevelRenderTarget", (UINT)EngineDirectX::GetMainViewPortSize().first, (UINT)EngineDirectX::GetMainViewPortSize().second);
	LevelRenderTarget->CreateRTV();
	LevelRenderTarget->CreateSRV();
	LevelRenderTarget->CreateDepthStencil();

	OnStart();
}

void EngineLevel::End()
{
	OnEnd();
}

void EngineLevel::Update(float _DeltaTime)
{
	OnUpdate(_DeltaTime);

	for (const std::pair<std::string, std::shared_ptr<EngineActor>> Actor : Actors)
	{
		Actor.second->Update(_DeltaTime);
	}
}

void EngineLevel::RenderSetting()
{
	LevelRenderTarget->Clear();
	EngineDirectX::SetRenderTarget(LevelRenderTarget->GetRTV(), LevelRenderTarget->GetDSV());

	EngineDirectX::GetInstance()->SetMainViewport();
	EngineDirectX::GetInstance()->SetDepthStencilState(EngineResourceManager::FindDSState("basedsstate"));
	//EngineDirectX::GetInstance()->SetRasterizerState(EngineResourceManager::FindRasterizerState("Solid"));
}

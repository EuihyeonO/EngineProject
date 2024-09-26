#include "EngineActor.h"
#include "EngineComponent.h"

void EngineActor::Start()
{
	OnStart();
}

void EngineActor::End()
{
	OnEnd();
}

EngineActor::EngineActor()
{
}

EngineActor::~EngineActor()
{
}

void EngineActor::Destroy()
{
	for (std::pair<std::string, std::shared_ptr<EngineComponent>> Component : Components)
	{
		Component.second->Destroy();
	}

	OnDestroyed();
	Components.clear();
}

void EngineActor::Update()
{
	OnUpdate();

	for (const std::pair<std::string, std::shared_ptr<EngineComponent>> Component : Components)
	{
		Component.second->Update();
	}
}


#include "EngineComponent.h"

EngineComponent::EngineComponent()
{
}

EngineComponent::~EngineComponent()
{
}

void EngineComponent::Destroy()
{
}

void EngineComponent::Render()
{
}

void EngineComponent::Start()
{
}

void EngineComponent::Update(float _DeltaTime)
{
}

void EngineComponent::End()
{
}

void EngineComponent::ComponentUpdate(float _DeltaTime)
{
	for (const std::pair<std::string, std::shared_ptr<EngineComponent>> Component : Components)
	{
		Component.second->Update(_DeltaTime);
	}
}

void EngineComponent::ComponentRender()
{
}

void EngineComponent::ComponentDestroy()
{
	for (std::pair<std::string, std::shared_ptr<EngineComponent>> Component : Components)
	{
		Component.second->Destroy();
	}

	Components.clear();
}

#include "StaticComponent.h"

StaticComponent::StaticComponent()
{
}

StaticComponent::~StaticComponent()
{
}

void StaticComponent::Destroy()
{
	OnDestroyed();
	//
	EngineComponent::Destroy();
}

void StaticComponent::Start()
{
	EngineComponent::Start();
	//
	OnStart();
}

void StaticComponent::Update(float _DeltaTime)
{
	EngineComponent::Update(_DeltaTime);
	//
	OnUpdate(_DeltaTime);
}

void StaticComponent::Render()
{
	EngineComponent::Render();
	//
	OnRender();
}

void StaticComponent::End()
{
	OnEnd();
	//
	EngineComponent::End();
}

void StaticComponent::ComponentUpdate(float _DeltaTime)
{
	EngineComponent::ComponentUpdate(_DeltaTime);
}

void StaticComponent::ComponentRender()
{
	EngineComponent::ComponentRender();
}

void StaticComponent::ComponentDestroy()
{
	EngineComponent::ComponentDestroy();
}

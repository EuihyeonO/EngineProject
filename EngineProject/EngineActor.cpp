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

void EngineActor::Update(float _DeltaTime)
{
	OnUpdate(_DeltaTime);

	for (const std::pair<std::string, std::shared_ptr<EngineComponent>> Component : Components)
	{
		Component.second->Update(_DeltaTime);
	}
}

void EngineActor::Render()
{
	for (const std::pair<std::string, std::shared_ptr<EngineComponent>>& RenderComp : RenderComponents)
	{
		RenderComp.second->Render();
	}
}

std::shared_ptr<EngineComponent> EngineActor::GetComponent(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (Components.find(UpperName) == Components.end())
	{
		return nullptr;
	}

	return Components[UpperName];
}


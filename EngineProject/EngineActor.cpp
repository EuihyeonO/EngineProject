#include "EngineActor.h"
#include "EngineComponent.h"

EngineActor::EngineActor()
{
}

EngineActor::~EngineActor()
{
}

void EngineActor::Init()
{
	SetObjectType(EObjectType::Actor);
}

void EngineActor::Start()
{
}

void EngineActor::End()
{
}

void EngineActor::Destroy()
{
}

void EngineActor::Update(float _DeltaTime)
{
}

void EngineActor::Render()
{
}

void EngineActor::ComponentUpdate(float _DeltaTime)
{
	for (const std::pair<std::string, std::shared_ptr<EngineComponent>> Component : Components)
	{
		Component.second->Update(_DeltaTime);
	}
}

void EngineActor::ComponentRender()
{
	for (const std::pair<std::string, std::shared_ptr<EngineComponent>>& RenderComp : RenderComponents)
	{
		RenderComp.second->Render();
	}
}

void EngineActor::ComponentDestroy()
{
	for (std::pair<std::string, std::shared_ptr<EngineComponent>> Component : Components)
	{
		Component.second->Destroy();
	}

	Components.clear();
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


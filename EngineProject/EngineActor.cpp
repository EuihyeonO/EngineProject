#include "EngineActor.h"
#include "EngineComponent.h"

EngineActor::EngineActor()
{
}

EngineActor::~EngineActor()
{
}

void EngineActor::ComponentUpdate()
{
	for (const std::pair<std::string, std::shared_ptr<EngineComponent>> Component : Components)
	{
		Component.second->Update();
	}
}


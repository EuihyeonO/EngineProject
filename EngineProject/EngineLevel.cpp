#include "EngineLevel.h"
#include "EngineActor.h"
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

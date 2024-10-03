#include "StaticActor.h"

StaticActor::StaticActor()
{
}

StaticActor::~StaticActor()
{
}

void StaticActor::Start()
{
	EngineActor::Start();
	//
	OnStart();
}

void StaticActor::Update(float _DeltaTime)
{
	EngineActor::Update(_DeltaTime);
	//
	OnUpdate(_DeltaTime);
	ComponentUpdate(_DeltaTime);
}

void StaticActor::Render()
{
	EngineActor::Render();
	//
	OnRender();
	ComponentRender();
}

void StaticActor::End()
{
	OnEnd();
	//
	EngineActor::End();
}

void StaticActor::Destroy()
{
	ComponentDestroy();
	OnDestroyed();
	//
	EngineActor::Destroy();
}

void StaticActor::ComponentUpdate(float _DeltaTime)
{
	EngineActor::ComponentUpdate(_DeltaTime);
}

void StaticActor::ComponentRender()
{
	EngineActor::ComponentRender();
}

void StaticActor::ComponentDestroy()
{
	EngineActor::ComponentDestroy();
}

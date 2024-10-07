#include "DynamicActor.h"

DynamicActor::DynamicActor()
{
}

DynamicActor::~DynamicActor()
{
}

void DynamicActor::Init()
{
	EngineActor::Init();
	CreateTransformComponent();
	OnCreated();
}

void DynamicActor::Start()
{
	EngineActor::Start();
	OnStart();
}

void DynamicActor::Update(float _DeltaTime)
{
	EngineActor::Update(_DeltaTime);
	//
	OnUpdate(_DeltaTime);
	ComponentUpdate(_DeltaTime);
}

void DynamicActor::Render()
{
	EngineActor::Render();
	//
	OnRender();
	ComponentRender();
}

void DynamicActor::End()
{
	OnEnd();
	//
	EngineActor::End();
}

void DynamicActor::Destroy()
{
	ComponentDestroy();
	OnDestroyed();
	//
	EngineActor::Destroy();
}

void DynamicActor::ComponentUpdate(float _DeltaTime)
{
	EngineActor::ComponentUpdate(_DeltaTime);
}

void DynamicActor::ComponentRender()
{
	EngineActor::ComponentRender();
}

void DynamicActor::ComponentDestroy()
{
	EngineActor::ComponentDestroy();
}

void DynamicActor::CreateTransformComponent()
{
	if (Transform != nullptr)
	{
		EngineDebug::LogErrorMsg(L"트랜스폼 컴포넌트가 이미 생성되어 있습니다.");
		return;
	}

	Transform = std::make_shared<TransformComponent>();
	Transform->SetOwner(shared_from_this());
	
	Transform->OnCreated();
	Transform->SetActivate(true);
}

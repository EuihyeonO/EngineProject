#include "EngineDebug.h"
#include "DynamicComponent.h"

DynamicComponent::DynamicComponent()
{
}

DynamicComponent::~DynamicComponent()
{
}

void DynamicComponent::Destroy()
{
	OnDestroyed();
	//
	EngineComponent::Destroy();
}

void DynamicComponent::Start()
{
	EngineComponent::Start();
	CreateTransformComponent();
	OnStart();
}

void DynamicComponent::Update(float _DeltaTime)
{
	EngineComponent::Update(_DeltaTime);
	//
	OnUpdate(_DeltaTime);
}

void DynamicComponent::Render()
{
	EngineComponent::Render();
	//
	OnRender();
}

void DynamicComponent::End()
{
	OnEnd();
	//
	EngineComponent::End();
}

void DynamicComponent::ComponentUpdate(float _DeltaTime)
{
	EngineComponent::ComponentUpdate(_DeltaTime);
}

void DynamicComponent::ComponentRender()
{
	EngineComponent::ComponentRender();
}

void DynamicComponent::ComponentDestroy()
{
	EngineComponent::ComponentDestroy();
}

void DynamicComponent::CreateTransformComponent()
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

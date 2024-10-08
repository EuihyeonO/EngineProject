#include "EngineDebug.h"
#include "DynamicComponent.h"
#include "DynamicActor.h"

DynamicComponent::DynamicComponent()
{
}

DynamicComponent::~DynamicComponent()
{
}

void DynamicComponent::Init()
{
	EngineComponent::Init();
	CreateTransformComponent();
	
	std::shared_ptr<EngineObjectBase> Owner = GetOwner();

	if (Owner->hasTransform() == true)
	{
		if (Owner->GetObjectType() == EObjectType::Actor)
		{
			Transform->SetParent(&(std::dynamic_pointer_cast<DynamicActor>(Owner)->GetTransformComponent()->GetTransform()));
		}
		else if (GetOwner()->GetObjectType() == EObjectType::Component)
		{
			Transform->SetParent(&(std::dynamic_pointer_cast<DynamicComponent>(Owner)->GetTransformComponent()->GetTransform()));
		}
	}

	OnCreated();
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
	//
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
		EngineDebug::LogErrorMsg(L"Ʈ������ ������Ʈ�� �̹� �����Ǿ� �ֽ��ϴ�.");
		return;
	}

	Transform = std::make_shared<TransformComponent>();
	Transform->SetOwner(shared_from_this());

	Transform->OnCreated();
	Transform->SetActivate(true);

	SetHasTransform(true);
}

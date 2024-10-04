#pragma once
#include "EngineComponent.h"
#include "TransformComponent.h"
#include "ObjectHeader.h"

class DynamicComponent : public EngineComponent
{
public:
	DynamicComponent();
	~DynamicComponent();

	DynamicComponent(const DynamicComponent& _Other) = delete;
	DynamicComponent(DynamicComponent&& _Other) noexcept = delete;
	DynamicComponent& operator=(const DynamicComponent& _Other) = delete;
	DynamicComponent& operator=(DynamicComponent&& _Other) noexcept = delete;

	//트랜스폼 컴포넌트는 만들 수 없습니다. 다이나믹 컴포넌트는 기본적으로 트랜스폼을 소유하고 있습니다.
	template<Not_Trans_Render_Component CompType>
	std::shared_ptr<CompType> CreateComponent(std::string_view _CompName)
	{
		std::string UpperName = EngineString::ToUpperReturn(_CompName.data());

		if (Components.find(UpperName) != Components.end())
		{
			EngineDebug::LogErrorMsg(L"생성하고자 하는 Component의 이름이 이미 존재합니다.");
			return nullptr;
		}

		std::shared_ptr<CompType> NewComp = std::make_shared<CompType>();
		NewComp->SetOwner(shared_from_this());

		if constexpr (std::is_base_of_v<DynamicComponent, CompType> == true)
		{
			NewComp->SetParent(&(Transform->GetTransform()));
		}

		NewComp->OnCreated();
		NewComp->SetActivate(true);

		Components[UpperName] = NewComp;

		return NewComp;
	}
	
	void SetParent(STransform* _Parent)
	{
		Transform->SetParent(_Parent);
	}

	void Destroy() override final;
protected:

private:
	void Start() override final;
	void Update(float _DeltaTime) override final;
	void Render() override final;
	void End() override final;

	void ComponentUpdate(float _DeltaTime) override;
	void ComponentRender() override;
	void ComponentDestroy() override;

	void CreateTransformComponent();

	std::shared_ptr<TransformComponent> Transform;
};


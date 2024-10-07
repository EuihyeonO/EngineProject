#pragma once
#include "ObjectHeader.h"
#include "EngineComponent.h"

class StaticComponent : public EngineComponent
{

public:

	StaticComponent();
	~StaticComponent();

	StaticComponent(const StaticComponent& _Other) = delete;
	StaticComponent(StaticComponent&& _Other) noexcept = delete;
	StaticComponent& operator=(const StaticComponent& _Other) = delete;
	StaticComponent& operator=(StaticComponent&& _Other) noexcept = delete;

public:
	//Ʈ������ ������Ʈ�� ������ ������Ʈ�� ������ �� �����ϴ�.
	//Ʈ������ ������Ʈ�� DynamicComponent�� �⺻���� ���ԵǾ� ������, ������ ������Ʈ�� Actor���� ���� �����մϴ�.
	template<Not_Trans_Render_Component CompType>
	std::shared_ptr<CompType> CreateComponent(std::string_view _CompName)
	{
		std::string UpperName = EngineString::ToUpperReturn(_CompName.data());

		if (Components.find(UpperName) != Components.end())
		{
			EngineDebug::LogErrorMsg(L"�����ϰ��� �ϴ� Component�� �̸��� �̹� �����մϴ�.");
			return nullptr;
		}

		std::shared_ptr<CompType> NewComp = std::make_shared<CompType>();
		NewComp->SetOwner(shared_from_this());

		NewComp->Init();
		NewComp->SetActivate(true);

		Components[UpperName] = NewComp;

		return NewComp;
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

};


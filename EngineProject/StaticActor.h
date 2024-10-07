#pragma once

#include "ObjectHeader.h"
#include "EngineActor.h"

class StaticActor : public EngineActor
{
	friend class EngineLevel;

public:

	StaticActor();
	~StaticActor();

	StaticActor(const StaticActor& _Other) = delete;
	StaticActor(StaticActor&& _Other) noexcept = delete;
	StaticActor& operator=(const StaticActor& _Other) = delete;
	StaticActor& operator=(StaticActor&& _Other) noexcept = delete;

public:
	//트랜스폼 컴포넌트는 만들 수 없습니다. 다이나믹 컴포넌트는 기본적으로 트랜스폼을 소유하고 있습니다.
	template<Not_Trans_Component CompType>
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

		NewComp->Init();
		NewComp->SetActivate(true);

		Components[UpperName] = NewComp;

		if constexpr (std::is_base_of_v<class EngineRenderBase, CompType> == true)
		{
			RenderComponents[UpperName] = NewComp;
		}

		return NewComp;
	}

	void Destroy() override final;

protected:

private:
	void Start() override final;
	void Update(float _DeltaTime) override final;
	void Render() override final;
	void End() override final;

	void ComponentUpdate(float _DeltaTime) override final;
	void ComponentRender() override final;
	void ComponentDestroy() override final;
};


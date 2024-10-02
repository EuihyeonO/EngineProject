#pragma once
#include "EngineObjectBase.h"
#include "EngineString.h"
#include "EngineComponent.h"
#include "EngineDebug.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class EngineActor : public EngineObjectBase
{
	friend class EngineLevel;
public:
	EngineActor();
	~EngineActor();

	EngineActor(const EngineActor& _Other) = delete;
	EngineActor(EngineActor&& _Other) noexcept = delete;
	EngineActor& operator=(const EngineActor& _Other) = delete;
	EngineActor& operator=(EngineActor&& _Other) noexcept = delete;

public:
	template<typename CompType, typename = std::enable_if_t<std::is_base_of_v<class EngineComponent, CompType>>>
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

		NewComp->OnCreated();
		NewComp->SetActivate(true);

		Components[UpperName] = NewComp;

		if (std::is_base_of_v<class EngineRenderBase, CompType> == true)
		{
			RenderComponents[UpperName] = NewComp;
		}

		return NewComp;
	}

	std::shared_ptr<EngineComponent> GetComponent(std::string_view _Name);

	void Start() override final;
	void Update(float _DeltaTime) override final;
	void Render() override final;
	void End() override final;
	void Destroy() override final;

protected:

private:
	std::unordered_map<std::string, std::shared_ptr<EngineComponent>> Components;
	std::unordered_map<std::string, std::shared_ptr<EngineComponent>> RenderComponents;
};


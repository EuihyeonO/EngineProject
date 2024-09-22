#pragma once
#include "EngineObjectBase.h"
#include "EngineString.h"
#include "EngineLevel.h"

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

	template<typename CompType, typename = std::enable_if_t<std::is_base_of_v<class EngineComponent, CompType>>>
	std::shared_ptr<CompType> CreateComponent(std::string_view _CompName)
	{
		std::string UpperName = EngineString::ToUpperReturn(_CompName.data());

		if (Components.find(UpperName) != Components.end())
		{
			std::string CompName = CompName.data();
			std::cerr << "Error : Component(ComponentName : " + CompName + ") is already created." << std::endl;
			return nullptr;
		}

		std::shared_ptr<CompType> NewComp = std::make_shared<CompType>();
		NewComp->SetOwner(shared_from_this());

		NewComp->OnCreated();
		NewComp->SetActivate(true);

		//Å×½ºÆ®
		std::shared_ptr<EngineLevel> OwnerLevel = std::dynamic_pointer_cast<EngineLevel>(GetOwner());
		OwnerLevel->AddRenderComps(NewComp);

		Components[UpperName] = NewComp;

		return NewComp;
	}

	std::shared_ptr<class EngineComponent> GetComponent(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (Components.find(UpperName) == Components.end())
		{
			return nullptr;
		}

		return Components[UpperName];
	}

protected:

private:
	void ComponentUpdate();

	std::unordered_map<std::string, std::shared_ptr<class EngineComponent>> Components;
};


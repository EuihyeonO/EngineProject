#pragma once
#include "EngineObjectBase.h"

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

	template<typename CompType, typename = std::enable_if_t<std::is_base_of_v<EngineComponent, CompType>>>
	std::shared_ptr<CompType> CreateComponent(std::string_view _CompName)
	{
		if (Components.find(_CompName.data()) != Components.end())
		{
			std::string CompName = CompName.data();
			std::cerr << "Error : Component(ComponentName : " + CompName + ") is already created." << std::endl;
			return nullptr;
		}

		std::shared_ptr<CompType> NewComp = std::make_shared<CompType>();
		NewComp->OnCreated();
		NewComp->SetActivate(true);

		Components[_CompName.data()] = NewComp;

		return NewComp;
	}

protected:

private:
	void ComponentUpdate();

	std::unordered_map<std::string, std::shared_ptr<class EngineComponent>> Components;
};


#pragma once
#include "EngineObjectBase.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>

class EngineLevel : public EngineObjectBase
{
	friend class EngineLevelManager;
public:

	EngineLevel();
	~EngineLevel();

	EngineLevel(const EngineLevel& _Other) = delete;
	EngineLevel(EngineLevel&& _Other) noexcept = delete;
	EngineLevel& operator=(const EngineLevel& _Other) = delete;
	EngineLevel& operator=(EngineLevel&& _Other) noexcept = delete;
	
	template<typename ActorType, typename = std::enable_if_t<std::is_base_of_v<EngineActor, ActorType>>>
	void CreateActor(std::string_view _ActorName)
	{
		if (Actors.find(_ActorName.data()) != Actors.end())
		{
			std::string ActorName = _ActorName.data();
			std::cerr << "Error : Actor(ActorName : " + ActorName + ") is already created." << std::endl;
			return;
		}

		std::shared_ptr<ActorType> NewActor = std::make_shared<ActorType>();
		NewActor->OnCreated();

		Actors[_ActorName.data()] = NewActor;
	}


protected:

private:
	void ActorUpdate();

	std::unordered_map<std::string, std::shared_ptr<class EngineActor>> Actors;
};


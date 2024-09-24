#pragma once
#include "EngineObjectBase.h"
#include "EngineActor.h"

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
	std::shared_ptr<ActorType> CreateActor(std::string_view _ActorName)
	{
		if (Actors.find(_ActorName.data()) != Actors.end())
		{
			std::string ActorName = _ActorName.data();
			std::cerr << "Error : Actor(ActorName : " + ActorName + ") is already created." << std::endl;
			return nullptr;
		}

		std::shared_ptr<ActorType> NewActor = std::make_shared<ActorType>();
		NewActor->SetOwner(shared_from_this());

		NewActor->OnCreated();
		NewActor->SetActivate(true);

		Actors[_ActorName.data()] = NewActor;

		return NewActor;
	}

	//테스트
	void AddRenderComps(std::shared_ptr<class SkeletalMeshComponent> _Comp)
	{
		RenderComps.push_back(_Comp);
	}

	//테스트
	std::vector<std::shared_ptr<class SkeletalMeshComponent>> RenderComps;

protected:

private:
	void Destroy() override final
	{
		for (const std::pair<std::string, std::shared_ptr<EngineActor>> Actor : Actors)
		{
			Actor.second->Destroy();
		}

		OnDestroyed();
		Actors.clear();
	}

	void Render() override final
	{
		for (const std::pair<std::string, std::shared_ptr<EngineActor>> Actor : Actors)
		{
			Actor.second->Render();
		}
	}

	void ActorUpdate();
	std::unordered_map<std::string, std::shared_ptr<EngineActor>> Actors;
};


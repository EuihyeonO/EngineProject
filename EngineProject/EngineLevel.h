#pragma once
#include "EngineObjectBase.h"
#include "EngineActor.h"
#include "EngineRenderTarget.h"

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
	
public:

	template<typename ActorType, typename = std::enable_if_t<std::is_base_of_v<EngineActor, ActorType>>>
	std::shared_ptr<ActorType> CreateActor(std::string_view _ActorName)
	{
		if (Actors.find(_ActorName.data()) != Actors.end())
		{
			std::string ActorName = _ActorName.data();
			EngineDebug::LogErrorMsg(L"생성하고자 하는 Actor의 이름이 이미 존재합니다.");
			return nullptr;
		}

		std::shared_ptr<ActorType> NewActor = std::make_shared<ActorType>();
		NewActor->SetOwner(shared_from_this());

		NewActor->OnCreated();
		NewActor->SetActivate(true);

		Actors[_ActorName.data()] = NewActor;

		return NewActor;
	}

	std::shared_ptr<class EngineRenderTarget> GetRenderTarget()
	{
		return LevelRenderTarget;
	}

	void Start() override final;
	void Update() override final;
	void End() override final;

protected:

private:
	void Destroy() override final
	{
		for (const std::pair<std::string, std::shared_ptr<EngineActor>> Actor : Actors)
		{
			Actor.second->Destroy();
		}

		Actors.clear();

		LevelRenderTarget->Destroy();
		LevelRenderTarget = nullptr;

		OnDestroyed();
	}

	void Render() override final
	{
		RenderSetting();

		for (const std::pair<std::string, std::shared_ptr<EngineActor>> Actor : Actors)
		{
			Actor.second->Render();
		}
	}

	void RenderSetting();

	std::unordered_map<std::string, std::shared_ptr<EngineActor>> Actors;

	std::shared_ptr<class EngineRenderTarget> LevelRenderTarget;
};


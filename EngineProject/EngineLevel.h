#pragma once
#include "EngineActor.h"
#include "CameraActor.h"
#include "EngineObjectBase.h"
#include "EngineRenderTarget.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>

template<typename T>
concept CommonActor = std::is_base_of_v<EngineActor, T> && !std::derived_from<T, CameraActor>;

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

	//CameraActor는 이 방식으로는 만들 수 없습니다. CameraActor를 만들고자 한다면 CreateCameraActor 함수를 사용해주세요.
	template<CommonActor ActorType>
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

	std::shared_ptr<CameraActor> CreateCameraActor(uint16_t _Order)
	{
		if (CameraActors.find(_Order) != CameraActors.end())
		{
			EngineDebug::LogErrorMsg(L"생성하고자 하는 CameraActor의 Order이 이미 존재합니다. Order : " + _Order);
			return nullptr;
		}

		std::shared_ptr<CameraActor> NewCameraActor = std::make_shared<CameraActor>();
		NewCameraActor->SetOwner(shared_from_this());

		NewCameraActor->OnCreated();
		NewCameraActor->SetActivate(true);

		CameraActors[_Order] = NewCameraActor;

		return NewCameraActor;
	}

	std::shared_ptr<class EngineRenderTarget> GetRenderTarget()
	{
		return LevelRenderTarget;
	}

	void Start() override final;
	void Update(float _DeltaTime) override final;
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
	std::unordered_map<uint16_t, std::shared_ptr<CameraActor>> CameraActors;

	std::shared_ptr<class EngineRenderTarget> LevelRenderTarget;
};


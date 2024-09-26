#pragma once
#include "EngineObjectBase.h"

class EngineComponent : public EngineObjectBase
{
	friend class EngineActor;
public:

	EngineComponent();
	~EngineComponent();

	EngineComponent(const EngineComponent& _Other) = delete;
	EngineComponent(EngineComponent&& _Other) noexcept = delete;
	EngineComponent& operator=(const EngineComponent& _Other) = delete;
	EngineComponent& operator=(EngineComponent&& _Other) noexcept = delete;

	void Destroy() override final
	{
		OnDestroyed();
	}

	void Render() override final 
	{
		OnRender();
	}

	void Start() override final
	{
		OnStart();
	}

	void Update() override final
	{
		OnUpdate();
	}

	void End() override final
	{
		OnEnd();
	}

protected:

private:

};


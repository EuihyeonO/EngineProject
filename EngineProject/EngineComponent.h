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

protected:

private:

};


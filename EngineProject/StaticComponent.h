#pragma once
#include "EngineComponent.h"

class StaticComponent //: public EngineComponent
{

public:

	StaticComponent();
	~StaticComponent();

	StaticComponent(const StaticComponent& _Other) = delete;
	StaticComponent(StaticComponent&& _Other) noexcept = delete;
	StaticComponent& operator=(const StaticComponent& _Other) = delete;
	StaticComponent& operator=(StaticComponent&& _Other) noexcept = delete;

protected:

private:

};


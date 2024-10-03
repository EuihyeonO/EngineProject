#pragma once
#include "EngineActor.h"

class StaticActor : public EngineActor
{

public:

	StaticActor();
	~StaticActor();

	StaticActor(const StaticActor& _Other) = delete;
	StaticActor(StaticActor&& _Other) noexcept = delete;
	StaticActor& operator=(const StaticActor& _Other) = delete;
	StaticActor& operator=(StaticActor&& _Other) noexcept = delete;

	void Destroy() override final;

protected:

private:
	void Start() override final;
	void Update(float _DeltaTime) override final;
	void Render() override final;
	void End() override final;

	void ComponentUpdate(float _DeltaTime) override final;
	void ComponentRender() override final;
	void ComponentDestroy() override final;
};


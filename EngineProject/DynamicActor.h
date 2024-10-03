#pragma once
#include "EngineActor.h"

class DynamicActor : public EngineActor
{

public:
	DynamicActor();
	~DynamicActor();

	DynamicActor(const DynamicActor& _Other) = delete;
	DynamicActor(DynamicActor&& _Other) noexcept = delete;
	DynamicActor& operator=(const DynamicActor& _Other) = delete;
	DynamicActor& operator=(DynamicActor&& _Other) noexcept = delete;

	void Destroy() override final;
	
	std::shared_ptr<TransformComponent> GetTransformComponent()
	{
		return Transform;
	}
	
protected:

private:
	void Start() override final;
	void Update(float _DeltaTime) override final;
	void Render() override final;
	void End() override final;

	void ComponentUpdate(float _DeltaTime) override final;
	void ComponentRender() override final;
	void ComponentDestroy() override final;

	void CreateTransformComponent();

	std::shared_ptr<TransformComponent> Transform;
};


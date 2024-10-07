#pragma once

#include "EngineObjectBase.h"
#include "EngineRenderBase.h"

#include <unordered_map>
#include <string>

class EngineComponent : public EngineObjectBase
{
	friend class DynamicActor;
	friend class StaticActor;
	friend class EngineActor;
public:

	EngineComponent();
	~EngineComponent();

	EngineComponent(const EngineComponent& _Other) = delete;
	EngineComponent(EngineComponent&& _Other) noexcept = delete;
	EngineComponent& operator=(const EngineComponent& _Other) = delete;
	EngineComponent& operator=(EngineComponent&& _Other) noexcept = delete;

	void Destroy() override;

protected:
	void Init() override;
	void Render() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	
	virtual void ComponentUpdate(float _DeltaTime);
	virtual void ComponentRender();
	virtual void ComponentDestroy();

	std::unordered_map<std::string, std::shared_ptr<EngineComponent>> Components;
private:
};


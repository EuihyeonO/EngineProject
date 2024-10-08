#pragma once
#include "EngineObjectBase.h"
#include "EngineString.h"
#include "EngineComponent.h"
#include "EngineDebug.h"
#include "TransformComponent.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class EngineActor : public EngineObjectBase
{
	friend class EngineLevel;
public:
	EngineActor();
	~EngineActor();

	EngineActor(const EngineActor& _Other) = delete;
	EngineActor(EngineActor&& _Other) noexcept = delete;
	EngineActor& operator=(const EngineActor& _Other) = delete;
	EngineActor& operator=(EngineActor&& _Other) noexcept = delete;

public:
	std::shared_ptr<EngineComponent> GetComponent(std::string_view _Name);
	
	void Destroy() override;
protected:
	void Init() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render() override;
	void End() override;

	virtual void ComponentUpdate(float _DeltaTime);
	virtual void ComponentRender();
	virtual void ComponentDestroy();

	std::unordered_map<std::string, std::shared_ptr<EngineComponent>> Components;
	std::unordered_map<std::string, std::shared_ptr<EngineComponent>> RenderComponents;
private:

};


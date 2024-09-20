#pragma once
#include "EngineObjectBase.h"

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

protected:

private:
	void ComponentUpdate();

	std::unordered_map<std::string, std::shared_ptr<class EngineComponent>> Components;
};


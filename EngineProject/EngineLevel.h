#pragma once
#include "EngineObjectBase.h"

class EngineLevel : public EngineObjectBase
{

public:

	EngineLevel();
	~EngineLevel();

	EngineLevel(const EngineLevel& _Other) = delete;
	EngineLevel(EngineLevel&& _Other) noexcept = delete;
	EngineLevel& operator=(const EngineLevel& _Other) = delete;
	EngineLevel& operator=(EngineLevel&& _Other) noexcept = delete;

protected:

private:
};


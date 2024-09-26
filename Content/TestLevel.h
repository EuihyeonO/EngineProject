#pragma once
#include "EngineLevel.h"

class TestLevel :public EngineLevel
{

public:
	TestLevel();
	~TestLevel();

	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

	void OnCreated() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	void OnDestroyed() override;
protected:

private:

};


#pragma once
#include "EngineActor.h"

class TestActor : public EngineActor
{

public:
	TestActor();
	~TestActor();

	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;

	void OnCreated() override;
	void Start() override;
	void Update() override;
	void End() override;
	void OnDestroyed() override;

protected:

private:
	
};


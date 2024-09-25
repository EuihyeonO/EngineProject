#pragma once
#include "EngineActor.h"
#include "EngineMath.h"

struct TestStr
{
	SFloat4 ABCD;
	SFloat4 BEFG;
	SFloat4 CFDG;
	SFloat4 DASD;
};

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
	TestStr TestData;
};


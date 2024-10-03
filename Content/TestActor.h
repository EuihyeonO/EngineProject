#pragma once
#include "DynamicActor.h"
#include "EngineMath.h"

struct TestStr
{
	SFloat4 ABCD;
	SFloat4 BEFG;
	SFloat4 CFDG;
	SFloat4 DASD;
};

class TestActor : public DynamicActor
{

public:
	TestActor();
	~TestActor();

	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;

	void OnCreated() override;
	void OnStart() override;
	void OnUpdate(float _DeltaTime) override;
	void OnEnd() override;
	void OnDestroyed() override;

protected:

private:
	TestStr TestData;
};


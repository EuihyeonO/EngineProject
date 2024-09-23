#pragma once
#include "EngineActor.h"
#include "DirectXHeader.h"

struct TestStr
{
	Float4 ABCD;
	Float4 BEFG;
	Float4 CFDG;
	Float4 DASD;
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


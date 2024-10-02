#include "TestLevel.h"
#include "TestActor.h"

#include <iostream>

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::OnCreated()
{
}

void TestLevel::OnStart()
{
	CreateActor<TestActor>("TestActor");
}

void TestLevel::OnUpdate(float _DeltaTime)
{
}

void TestLevel::OnEnd()
{
}

void TestLevel::OnDestroyed()
{
}

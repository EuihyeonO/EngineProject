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

void TestLevel::Start()
{
	CreateActor<TestActor>("TestActor");
}

void TestLevel::Update()
{
}

void TestLevel::End()
{
}

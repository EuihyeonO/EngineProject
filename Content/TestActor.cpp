#include "TestActor.h"
#include "SkeletalMeshComponent.h"

#include <iostream>

TestActor::TestActor()
{
}

TestActor::~TestActor()
{
}

void TestActor::OnCreated()
{
}

void TestActor::Start()
{
	std::shared_ptr<SkeletalMeshComponent> SMComp = CreateComponent<SkeletalMeshComponent>("Body");
	
	SMComp->SetMesh("zeldaPosed001.fbx");
	SMComp->SetVertexShader("VS_Test.hlsl");
	SMComp->SetPixelShader("PS_Test.hlsl");
	SMComp->SetVSConstantBuffer("DATA", &TestData);
}

void TestActor::Update()
{
}

void TestActor::End()
{
}

void TestActor::OnDestroyed()
{
}

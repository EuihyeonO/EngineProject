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

std::shared_ptr<SkeletalMeshComponent> Comp;
std::shared_ptr<SkeletalMeshComponent> Trans;

void TestActor::Start()
{
	Comp = CreateComponent<SkeletalMeshComponent>("Body");
	
	Comp->SetMesh("zeldaPosed001.fbx");
	Comp->SetVertexShader("VS_Test.hlsl");
	Comp->SetPixelShader("PS_Test.hlsl");
	Comp->SetVSConstantBuffer("DATA", &TestData);
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

#include "TestActor.h"
#include "SkeletalMeshComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

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
std::shared_ptr<CameraComponent> Camera;
std::shared_ptr<TransformComponent> MyTransform;

void TestActor::OnStart()
{
	Comp = CreateComponent<SkeletalMeshComponent>("Body");
	Camera = CreateComponent<CameraComponent>("MainCamera");
	std::shared_ptr<EngineComponent> Test = std::dynamic_pointer_cast<EngineComponent>(Camera);

	MyTransform = GetTransformComponent();
	STransformConstantBuffer& _Transform = MyTransform->GetTransformBuffer();
	STransform& _1Transform = MyTransform->GetTransform();
	//
	SFloat4 EyePos = { 0.0f, 50.0f, -250.0f };
	SFloat4 EyeDir = { 0.0f, 0.0f, 1.0f };
	SFloat4 UpDir = { 0.0f, 1.0f, 0.0f };
	
	_Transform.ViewMatrix.Matrix4x4 = DirectX::XMMatrixLookToLH(EyePos.Vector4, EyeDir.Vector4, UpDir.Vector4);
	const float AspectRatio = (float)EngineDirectX::GetMainViewPortSize().first /
		(float)EngineDirectX::GetMainViewPortSize().second;
	const float fovAngleY = 70.0f * DirectX::XM_PI / 180.0f;
	_Transform.ProjMatrix.Matrix4x4 = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, AspectRatio, 0.01f, 1000.0f);
	_Transform.ViewMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(_Transform.ViewMatrix.Matrix4x4);
	_Transform.ProjMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(_Transform.ProjMatrix.Matrix4x4);
	
	_Transform.WorldMatrix.Matrix4x4 =
		DirectX::XMMatrixScaling(_1Transform.LocalScale.X, _1Transform.LocalScale.Y, _1Transform.LocalScale.Z) *
		DirectX::XMMatrixRotationQuaternion(_1Transform.LocalQuaternion.Vector4) *
		DirectX::XMMatrixTranslation(_1Transform.LocalPosition.X, _1Transform.LocalPosition.Y, _1Transform.LocalPosition.Z);
	_Transform.WorldMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(_Transform.WorldMatrix.Matrix4x4);
	
	Comp->SetMesh("zeldaPosed001.fbx");
	Comp->SetVertexShader("VS_Test.hlsl");
	Comp->SetPixelShader("PS_Test.hlsl");
	Comp->SetVSConstantBuffer("Transform", &(GetTransformComponent()->GetTransformBuffer()));
}

void TestActor::OnUpdate(float _DeltaTime)
{
}

void TestActor::OnEnd()
{
}

void TestActor::OnDestroyed()
{
}

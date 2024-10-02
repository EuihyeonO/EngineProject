#include "TestActor.h"
#include "SkeletalMeshComponent.h"
#include "TransformComponent.h"

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
std::shared_ptr<TransformComponent> Transform;

void TestActor::OnStart()
{
	Comp = CreateComponent<SkeletalMeshComponent>("Body");
	Transform = CreateComponent<TransformComponent>("Transform");
	STransform& _Transform = Transform->GetTransform();

	SFloat4 EyePos = { 0.0f, 7.5f, -25.0f };
	SFloat4 EyeDir = { 0.0f, 0.0f, 1.0f };
	SFloat4 UpDir = { 0.0f, 1.0f, 0.0f };

	_Transform.LocalScale = { 0.1f, 0.1f, 0.1f };
	_Transform.LocalPosition = { 0.0f, 0.0f, 0.0f };

	_Transform.ViewMatrix.Matrix4x4 = DirectX::XMMatrixLookToLH(EyePos.Vector4, EyeDir.Vector4, UpDir.Vector4);
	const float AspectRatio = (float)EngineDirectX::GetMainViewPortSize().first /
		(float)EngineDirectX::GetMainViewPortSize().second;
	const float fovAngleY = 70.0f * DirectX::XM_PI / 180.0f;
	_Transform.ProjMatrix.Matrix4x4 = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, AspectRatio, 0.01f, 1000.0f);
	_Transform.ViewMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(_Transform.ViewMatrix.Matrix4x4);
	_Transform.ProjMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(_Transform.ProjMatrix.Matrix4x4);

	_Transform.WorldMatrix.Matrix4x4 =
		DirectX::XMMatrixScaling(_Transform.LocalScale.X, _Transform.LocalScale.Y, _Transform.LocalScale.Z) *
		DirectX::XMMatrixRotationQuaternion(_Transform.LocalQuaternion.Vector4) *
		DirectX::XMMatrixTranslation(_Transform.LocalPosition.X, _Transform.LocalPosition.Y, _Transform.LocalPosition.Z);
	_Transform.WorldMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(_Transform.WorldMatrix.Matrix4x4);

	Comp->SetMesh("zeldaPosed001.fbx");
	Comp->SetPixelShader("PS_Test.hlsl");
	Comp->SetVertexShader("VS_Test.hlsl");
	Comp->SetVSConstantBuffer("DATA", &(Transform->GetTransform()));
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

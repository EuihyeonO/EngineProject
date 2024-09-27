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
std::shared_ptr<TransformComponent> Trans;

void TestActor::OnStart()
{
	Comp = CreateComponent<SkeletalMeshComponent>("Body");
	Trans = CreateComponent<TransformComponent>("Transform");
	STransform& Transform = Trans->GetTransform();

	SFloat4 EyePos = { 0.0f, 7.5f, -25.0f };
	SFloat4 EyeDir = { 0.0f, 0.0f, 1.0f };
	SFloat4 UpDir = { 0.0f, 1.0f, 0.0f };

	Transform.LocalScale = { 0.1f, 0.1f, 0.1f };
	Transform.LocalPosition = { 0.0f, 0.0f, 0.0f };

	Transform.ViewMatrix.Matrix4x4 = DirectX::XMMatrixLookToLH(EyePos.Vector4, EyeDir.Vector4, UpDir.Vector4);
	const float AspectRatio = (float)EngineDirectX::GetMainViewPortSize().first /
		(float)EngineDirectX::GetMainViewPortSize().second;
	const float fovAngleY = 70.0f * DirectX::XM_PI / 180.0f;
	Transform.ProjMatrix.Matrix4x4 = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, AspectRatio, 0.01f, 1000.0f);
	Transform.ViewMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(Transform.ViewMatrix.Matrix4x4);
	Transform.ProjMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(Transform.ProjMatrix.Matrix4x4);

	Transform.WorldMatrix.Matrix4x4 =
		DirectX::XMMatrixScaling(Transform.LocalScale.X, Transform.LocalScale.Y, Transform.LocalScale.Z) *
		DirectX::XMMatrixRotationQuaternion(Transform.LocalQuaternion.Vector4) *
		DirectX::XMMatrixTranslation(Transform.LocalPosition.X, Transform.LocalPosition.Y, Transform.LocalPosition.Z);
	Transform.WorldMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(Transform.WorldMatrix.Matrix4x4);

	Comp->SetMesh("zeldaPosed001.fbx");
	Comp->SetVertexShader("VS_Test.hlsl");
	Comp->SetPixelShader("PS_Test.hlsl");
	Comp->SetVSConstantBuffer("DATA", &(Trans->GetTransform()));
}

void TestActor::OnUpdate()
{
}

void TestActor::OnEnd()
{
}

void TestActor::OnDestroyed()
{
}

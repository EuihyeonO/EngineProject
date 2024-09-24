#pragma once
#include "EngineComponent.h"
#include "DirectXHeader.h"
#include "EngineMath.h"

struct STransform
{
	Float4 LocalScale = { 1.0f, 1.0f, 1.0f, 0.0f };
	Float4 LocalRotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	Float4 LocalQuaternion = { 0.0f, 0.0f, 0.0f, 1.0f };
	Float4 LocalPosition = { 0.0f, 0.0f, 0.0f, 1.0f };

	Float4 WorldScale = { 0.0f, 0.0f, 0.0f, 0.0f };
	Float4 WorldRotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	Float4 WorldQuaternion = { 0.0f, 0.0f, 0.0f, 1.0f };
	Float4 WorldPosition = { 0.0f, 0.0f, 0.0f, 1.0f };

	//SRP 다 곱한 것
	Float4x4 LocalMatrix;
	
	Float4x4 LocalScaleMatrix;
	Float4x4 LocalRotationMatrix;
	Float4x4 LocalPositionMatrix;
	
	//SRP 다 곱한 것
	Float4x4 WorldMatrix;

	Float4x4 WorldScaleMatrix;
	Float4x4 WorldRotationMatrix;
	Float4x4 WorldPositionMatrix;

	//카메라의 뷰행렬
	Float4x4 ViewMatrix;
	
	//프로젝션 행렬
	Float4x4 ProjMatrix;
};

class TransformComponent : public EngineComponent
{
public:
	TransformComponent();
	~TransformComponent();

	TransformComponent(const TransformComponent& _Other) = delete;
	TransformComponent(TransformComponent&& _Other) noexcept = delete;
	TransformComponent& operator=(const TransformComponent& _Other) = delete;
	TransformComponent& operator=(TransformComponent&& _Other) noexcept = delete;

	void AddLocalScale(const Float3 _AddScale)
	{
		Transform.LocalScale = EngineMath::AddFloat4(Transform.LocalScale, { _AddScale.x, _AddScale.y, _AddScale.z, 0.0f});
		
		Matrix4x4 Mat = DirectX::XMMatrixScaling(Transform.LocalScale.x, Transform.LocalScale.y, Transform.LocalScale.z);
		DirectX::XMStoreFloat4x4(&(Transform.LocalScaleMatrix), Mat);
	}

	void AddLocalRotation(const Float3 _AddRot)
	{
		Float4 Radian = EngineMath::DegreeToRadian({ _AddRot.x, _AddRot.y, _AddRot.z, 1.0f});

		//회전각 덧셈
		Vector4 MyQuaternion = DirectX::XMLoadFloat4(&Transform.LocalQuaternion);
		Vector4 AddQuaternion = DirectX::XMQuaternionRotationRollPitchYaw(Radian.x, Radian.y, Radian.z);
		
		Vector4 ResultQuaternion = DirectX::XMQuaternionMultiply(MyQuaternion, AddQuaternion);
		ResultQuaternion = DirectX::XMQuaternionNormalize(ResultQuaternion);

		DirectX::XMStoreFloat4(&Transform.LocalQuaternion, ResultQuaternion);

		//행렬에 반영
		Matrix4x4 Mat = DirectX::XMMatrixRotationQuaternion(ResultQuaternion);
		DirectX::XMStoreFloat4x4(&Transform.LocalRotationMatrix, Mat);

		//LocalRotation에 반영
		Transform.LocalRotation = EngineMath::QuaternionToEuler(Transform.LocalQuaternion);
		Transform.LocalRotation.w = 1.0f;
	}

	void AddLocalPosition(const Float3 _AddPos)
	{
		Transform.LocalPosition = EngineMath::AddFloat4(Transform.LocalPosition, { _AddPos.x, _AddPos.y, _AddPos.z, 0.0f});

		Matrix4x4 Mat = DirectX::XMMatrixTranslation(Transform.LocalPosition.x, Transform.LocalPosition.y, Transform.LocalPosition.z);
		DirectX::XMStoreFloat4x4(&(Transform.LocalPositionMatrix), Mat);
	}

	const Float4& GetLocalScale() const
	{
		return Transform.LocalScale;
	}

	const Float4& GetLocalRotation() const
	{
		return Transform.LocalRotation;
	}

	const Float4& AddLocalPosition() const
	{
		return Transform.LocalPosition;
	}

protected:

private:
	STransform Transform;
};


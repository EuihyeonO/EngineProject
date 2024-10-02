#pragma once
#include "EngineComponent.h"
#include "DirectXHeader.h"
#include "EngineMath.h"

struct STransform
{
	SFloat4 LocalScale = { 1.0f, 1.0f, 1.0f, 0.0f };
	SFloat4 LocalRotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	SFloat4 LocalQuaternion = { 0.0f, 0.0f, 0.0f, 1.0f };
	SFloat4 LocalPosition = { 0.0f, 0.0f, 0.0f, 1.0f };

	SFloat4 WorldScale = { 0.0f, 0.0f, 0.0f, 0.0f };
	SFloat4 WorldRotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	SFloat4 WorldQuaternion = { 0.0f, 0.0f, 0.0f, 1.0f };
	SFloat4 WorldPosition = { 0.0f, 0.0f, 0.0f, 1.0f };

	//SRP 다 곱한 것
	SFloat4x4 LocalMatrix;
	
	SFloat4x4 LocalScaleMatrix;
	SFloat4x4 LocalRotationMatrix;
	SFloat4x4 LocalPositionMatrix;
	
	//SRP 다 곱한 것
	SFloat4x4 WorldMatrix;

	SFloat4x4 WorldScaleMatrix;
	SFloat4x4 WorldRotationMatrix;
	SFloat4x4 WorldPositionMatrix;

	//카메라의 뷰행렬
	SFloat4x4 ViewMatrix;
	
	//프로젝션 행렬
	SFloat4x4 ProjMatrix;
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

	void AddLocalScale(const SFloat3& _AddScale)
	{
		Transform.LocalScale += SFloat4(_AddScale, 0.0f);
	}

	void AddLocalRotation(const SFloat3& _AddRot)
	{
		SFloat4 Radian = SFloat4(_AddRot).DegreeToRadianReturn();

		SFloat4 AddQuaternion;
		AddQuaternion.Vector4 = Radian.EulerToQuaternionReturn().Vector4;
		
		Transform.LocalQuaternion.MulQuaternion(AddQuaternion);

		//행렬에 반영
		Transform.LocalRotationMatrix.Matrix4x4 = DirectX::XMMatrixRotationQuaternion(Transform.LocalQuaternion.Vector4);

		//LocalRotation에 반영
		Transform.LocalRotation = Transform.LocalQuaternion.QuaternionToEulerReturn();
		Transform.LocalRotation.W = 1.0f;
	}

	void AddLocalPosition(const SFloat3 _AddPos)
	{
		Transform.LocalPosition += SFloat4(_AddPos);
		Transform.LocalPositionMatrix.Matrix4x4 = DirectX::XMMatrixTranslation(Transform.LocalPosition.X, Transform.LocalPosition.Y, Transform.LocalPosition.Z);
	}

	const SFloat4& GetLocalScale() const
	{
		return Transform.LocalScale;
	}

	const SFloat4& GetLocalRotation() const
	{
		return Transform.LocalRotation;
	}

	const SFloat4& AddLocalPosition() const
	{
		return Transform.LocalPosition;
	}

	STransform& GetTransform()
	{
		return Transform;
	}

	virtual void OnCreated(){}
	virtual void OnStart(){}
	virtual void OnUpdate(float _DeltaTime){}
	virtual void OnEnd(){} 
	virtual void OnDestroyed(){} 
	virtual void OnRender(){}

protected:

private:
	STransform Transform;
};


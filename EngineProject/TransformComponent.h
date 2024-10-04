#pragma once
#include "EngineComponent.h"
#include "DirectXHeader.h"
#include "EngineMath.h"

struct STransform
{
	SFloat4 LocalScale = { 1.0f, 1.0f, 1.0f, 0.0f };
	SFloat4 LocalRotation = { 0.0f, 0.0f, 0.0f, 0.0f };
	SFloat4 LocalQuaternion = { 0.0f, 0.0f, 0.0f, 1.0f };
	SFloat4 LocalPosition = { 0.0f, 0.0f, 0.0f, 1.0f };

	SFloat4 WorldScale = { 1.0f, 1.0f, 1.0f, 0.0f };
	SFloat4 WorldRotation = { 0.0f, 0.0f, 0.0f, 0.0f };
	SFloat4 WorldQuaternion = { 0.0f, 0.0f, 0.0f, 1.0f };
	SFloat4 WorldPosition = { 0.0f, 0.0f, 0.0f, 1.0f };

	SFloat4 UpVector = { 0.0f, 0.0f, 0.0f, 0.0f };
	SFloat4 LeftVector = { 0.0f, 0.0f, 0.0f, 0.0f };
	SFloat4 ForwardVector = { 0.0f, 0.0f, 0.0f, 0.0f };
};

struct STranformConstantBuffer
{
	SFloat4x4 LocalMatrix;
	SFloat4x4 WorldMatrix;
	SFloat4x4 ViewMatrix;
	SFloat4x4 ProjMatrix;
};

class TransformComponent final : public EngineComponent
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

		//LocalRotation에 반영
		Transform.LocalRotation = Transform.LocalQuaternion.QuaternionToEulerReturn();
		Transform.LocalRotation.W = 1.0f;
	}

	void AddLocalPosition(const SFloat3 _AddPos)
	{
		Transform.LocalPosition += SFloat4(_AddPos);
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

	//Private로 옮겨야함.
	STransform& GetTransform()
	{
		return Transform;
	}

	void SetParent(STransform* _Parent)
	{
		Parent = _Parent;
	}

	void MatrixUpdate();
	
	virtual void OnUpdate(float _DeltaTime)
	{
		MatrixUpdate();
	}

	virtual void OnCreated() {}
	virtual void OnStart() {}
	virtual void OnEnd(){} 
	virtual void OnDestroyed(){} 
	virtual void OnRender(){}

protected:

private:
	STransform* Parent = nullptr;
	STransform Transform;
};


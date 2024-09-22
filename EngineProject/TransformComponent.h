#pragma once
#include "EngineComponent.h"
#include "DirectXHeader.h"
#include "EngineMath.h"

struct STransform
{
	Float4 LocalScale = { 0.0f, 0.0f, 0.0f, 0.0f };
	Float4 LocalRotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	Float4 LocalPosition = { 0.0f, 0.0f, 0.0f, 1.0f };

	Float4 WorldScale = { 0.0f, 0.0f, 0.0f, 0.0f };
	Float4 WorldRotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	Float4 WorldPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
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

	void AddLocalScale(const Float4 _AddScale)
	{
		Transform.LocalScale = EngineMath::AddFloat4(Transform.LocalScale, _AddScale);
	}

	void AddLocalRotation(const Float4 _AddRot)
	{
		Transform.LocalRotation = EngineMath::AddFloat4(Transform.LocalRotation, _AddRot);
	}

	void AddLocalPosition(const Float4 _AddPos)
	{
		Transform.LocalPosition = EngineMath::AddFloat4(Transform.LocalPosition, _AddPos);
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


#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::MatrixUpdate()
{
	//Transform.LocalMatrix.Matrix4x4 =
	//	DirectX::XMMatrixScaling(Transform.LocalScale.X, Transform.LocalScale.Y, Transform.LocalScale.Z) *
	//	DirectX::XMMatrixRotationQuaternion(Transform.LocalQuaternion.Vector4) *
	//	DirectX::XMMatrixTranslation(Transform.LocalPosition.X, Transform.LocalPosition.Y, Transform.LocalPosition.Z);

	//Transform.WorldMatrix.Matrix4x4 = DirectX::XMMatrixTranspose(Transform.WorldMatrix.Matrix4x4);
	//Transform.ViewMatrix
	//Transform.ProjMatrix
}
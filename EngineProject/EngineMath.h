#pragma once
#include "DirectXHeader.h"

class EngineMath
{
public:
	static Float4 MulFloat4(const Float4 _Left, const Float4 _Right)
	{
		Vector4 LeftVector4 = DirectX::XMLoadFloat4(&_Left);
		Vector4 RightVector4 = DirectX::XMLoadFloat4(&_Right);

		Vector4 MulResult = DirectX::XMVectorMultiply(LeftVector4, RightVector4);
		
		Float4 ReturnValue;
		DirectX::XMStoreFloat4(&ReturnValue, MulResult);

		return ReturnValue;
	}

	static Float4 AddFloat4(const Float4 _Left, const Float4 _Right)
	{
		Vector4 LeftVector4 = DirectX::XMLoadFloat4(&_Left);
		Vector4 RightVector4 = DirectX::XMLoadFloat4(&_Right);

		Vector4 MulResult = DirectX::XMVectorAdd(LeftVector4, RightVector4);

		Float4 ReturnValue;
		DirectX::XMStoreFloat4(&ReturnValue, MulResult);

		return ReturnValue;
	}

	static Float4 SubFloat4(const Float4 _Left, const Float4 _Right)
	{
		Vector4 LeftVector4 = DirectX::XMLoadFloat4(&_Left);
		Vector4 RightVector4 = DirectX::XMLoadFloat4(&_Right);

		Vector4 MulResult = DirectX::XMVectorSubtract(LeftVector4, RightVector4);

		Float4 ReturnValue;
		DirectX::XMStoreFloat4(&ReturnValue, MulResult);

		return ReturnValue;
	}

	static Float4 DivFloat4(const Float4 _Left, const Float4 _Right)
	{
		Vector4 LeftVector4 = DirectX::XMLoadFloat4(&_Left);
		Vector4 RightVector4 = DirectX::XMLoadFloat4(&_Right);

		Vector4 MulResult = DirectX::XMVectorDivide(LeftVector4, RightVector4);

		Float4 ReturnValue;
		DirectX::XMStoreFloat4(&ReturnValue, MulResult);

		return ReturnValue;
	}

	//
	static Float4x4 MulFloat4x4(const Float4x4 _Left, const Float4x4 _Right)
	{
		Matrix4x4 LeftMatrix = DirectX::XMLoadFloat4x4(&_Left);
		Matrix4x4 RightMatrix = DirectX::XMLoadFloat4x4(&_Right);

		Matrix4x4 MulResult = DirectX::XMMatrixMultiply(LeftMatrix, RightMatrix);

		Float4x4 ReturnValue;
		DirectX::XMStoreFloat4x4(&ReturnValue, MulResult);
		
		return ReturnValue;
	}

	//
	static void Normalize(Float2& _Float2)
	{
		Vector4 Vector = DirectX::XMLoadFloat2(&_Float2);
		Vector = DirectX::XMVector2Normalize(Vector);

		DirectX::XMStoreFloat2(&_Float2, Vector);
	}

	static void Normalize(Float3& _Float3)
	{
		Vector4 Vector = DirectX::XMLoadFloat3(&_Float3);
		Vector = DirectX::XMVector3Normalize(Vector);

		DirectX::XMStoreFloat3(&_Float3, Vector);
	}

	static void Normalize(Float4& _Float4)
	{
		Vector4 Vector = DirectX::XMLoadFloat4(&_Float4);
		Vector = DirectX::XMVector4Normalize(Vector);

		DirectX::XMStoreFloat4(&_Float4, Vector);
	}

	//
	static Float2 Transform(const Float2& _Float2, const Float4x4& _Matrix)
	{
		Vector4 Vector = DirectX::XMLoadFloat2(&_Float2);
		Matrix4x4 Mat = DirectX::XMLoadFloat4x4(&_Matrix);

		Vector4 TransformResult = DirectX::XMVector2Transform(Vector, Mat);

		Float2 ReturnValue;
		DirectX::XMStoreFloat2(&ReturnValue, TransformResult);

		return ReturnValue;
	}

	static Float3 Transform(const Float3& _Float3, const Float4x4& _Matrix)
	{
		Vector4 Vector = DirectX::XMLoadFloat3(&_Float3);
		Matrix4x4 Mat = DirectX::XMLoadFloat4x4(&_Matrix);

		Vector4 TransformResult = DirectX::XMVector3Transform(Vector, Mat);

		Float3 ReturnValue;
		DirectX::XMStoreFloat3(&ReturnValue, TransformResult);

		return ReturnValue;
	}

	static Float4 Transform(const Float4& _Float4, const Float4x4& _Matrix)
	{
		Vector4 Vector = DirectX::XMLoadFloat4(&_Float4);
		Matrix4x4 Mat = DirectX::XMLoadFloat4x4(&_Matrix);

		Vector4 TransformResult = DirectX::XMVector4Transform(Vector, Mat);

		Float4 ReturnValue;
		DirectX::XMStoreFloat4(&ReturnValue, TransformResult);

		return ReturnValue;
	}
protected:

private:

};


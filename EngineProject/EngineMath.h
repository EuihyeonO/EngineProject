#pragma once
#include "DirectXHeader.h"

class EngineMath
{
	constexpr static float EnginePI = DirectX::XM_PI;
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

	static Float4x4 AddFloat4x4(const Float4x4 _Left, const Float4x4 _Right)
	{
		Matrix4x4 LeftMatrix = DirectX::XMLoadFloat4x4(&_Left);
		Matrix4x4 RightMatrix = DirectX::XMLoadFloat4x4(&_Right);

		Matrix4x4 AddResult;

		for (int i = 0; i < 4; i++)
		{
			AddResult.r[i] = DirectX::XMVectorAdd(LeftMatrix.r[i], RightMatrix.r[i]);
		}

		Float4x4 ReturnValue;
		DirectX::XMStoreFloat4x4(&ReturnValue, AddResult);

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

	static Float4 QuaternionToEuler(Float4 _Quaternion)
	{
		float X = _Quaternion.x;
		float Y = _Quaternion.y;
		float Z = _Quaternion.z;
		float W = _Quaternion.w;

		Float4 Euler;
		
		Euler.x = atan2f(2.0f * (Y * W + X * Z), 1.0f - 2.0f * (X * X + Y * Y));
		Euler.y = asinf(2.0f * (Y * Z - W * X)); 
		Euler.z = atan2f(2.0f * (X * W + Y * Z), 1.0f - 2.0f * (Y * Y + Z * Z));

		return Euler;
	}

	static Float4 DegreeToRadian(Float4 _Degree)
	{
		Float4 Radian;
		
		Radian.x = _Degree.x * EnginePI / 180.0f;
		Radian.y = _Degree.y * EnginePI / 180.0f;
		Radian.z = _Degree.z * EnginePI / 180.0f;

		return Radian;
	}

	static Float4 RadianToDegree(Float4 _Radian)
	{
		Float4 Degree;

		Degree.x = _Radian.x * 180.0f / EnginePI;
		Degree.y = _Radian.y * 180.0f / EnginePI;
		Degree.z = _Radian.z * 180.0f / EnginePI;

		return Degree;
	}

protected:

private:

};


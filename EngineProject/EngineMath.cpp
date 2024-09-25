#include "EngineMath.h"

void EngineMath::AddFloat4(SFloat4& _Stored, const SFloat4& _Add)
{
	_Stored.Vector4 = DirectX::XMVectorAdd(_Stored.Vector4, _Add.Vector4);
}

SFloat4 EngineMath::AddFloat4Return(const SFloat4& _Left, const SFloat4& _Right)
{
	SFloat4 ReturnValue;
	ReturnValue.Vector4 = DirectX::XMVectorAdd(_Left.Vector4, _Right.Vector4);
	return ReturnValue;
}

void EngineMath::SubFloat4(SFloat4& _Stored, const SFloat4& _Sub)
{
	_Stored.Vector4 = DirectX::XMVectorSubtract(_Stored.Vector4, _Sub.Vector4);
}

SFloat4 EngineMath::SubFloat4Return(const SFloat4& _Left, const SFloat4& _Right)
{
	SFloat4 ReturnValue;
	ReturnValue.Vector4 = DirectX::XMVectorSubtract(_Left.Vector4, _Right.Vector4);
	return ReturnValue;
}

void EngineMath::MulFloat4(SFloat4& _Stored, const SFloat4& _Sub)
{
	_Stored.Vector4 = DirectX::XMVectorMultiply(_Stored.Vector4, _Sub.Vector4);
}

SFloat4 EngineMath::MulFloat4Return(const SFloat4& _Left, const SFloat4& _Right)
{
	SFloat4 ReturnValue;
	ReturnValue.Vector4 = DirectX::XMVectorMultiply(_Left.Vector4, _Right.Vector4);
	return ReturnValue;
}

 void EngineMath::DivFloat4(SFloat4& _Stored, const SFloat4& _Sub)
{
	_Stored.Vector4 = DirectX::XMVectorDivide(_Stored.Vector4, _Sub.Vector4);
}

SFloat4 EngineMath::DivFloat4Return(const SFloat4& _Left, const SFloat4& _Right)
{
	SFloat4 ReturnValue;
	ReturnValue.Vector4 = DirectX::XMVectorDivide(_Left.Vector4, _Right.Vector4);
	return ReturnValue;
}

void EngineMath::MulQuaternion(SFloat4& _Stored, const SFloat4& _Mul)
{
	_Stored.Vector4 = DirectX::XMQuaternionMultiply(_Stored.Vector4, _Mul.Vector4);
}

SFloat4 EngineMath::MulQuaternionReturn(const SFloat4& _Left, const SFloat4& _Right)
{
	SFloat4 ReturnValue;
	ReturnValue.Vector4 = DirectX::XMQuaternionMultiply(_Left.Vector4, _Right.Vector4);
	return ReturnValue;
}

void EngineMath::MulFloat4x4(SFloat4x4& _Stored, const SFloat4x4& _Mul)
{
	_Stored.Matrix4x4 = DirectX::XMMatrixMultiply(_Stored.Matrix4x4, _Mul.Matrix4x4);
}

SFloat4x4 EngineMath::MulFloat4x4Return(const SFloat4x4& _Left, const SFloat4x4& _Right)
{
	SFloat4x4 ReturnValue;
	ReturnValue.Matrix4x4 = DirectX::XMMatrixMultiply(_Left.Matrix4x4, _Right.Matrix4x4);
	return ReturnValue;
}

void EngineMath::Normalize(SFloat2& _Float2)
{
	DirectX::XMVECTOR Vector = DirectX::XMVectorSet(_Float2.X, _Float2.Y, 0.0f, 0.0f);
	Vector = DirectX::XMVector3Normalize(Vector);
	XMStoreFloat2(&_Float2.Float2, Vector);
}

SFloat2 EngineMath::NormalizeReturn(const SFloat2& _Float2)
{
	SFloat2 ReturnValue;

	DirectX::XMVECTOR Vector = DirectX::XMVectorSet(_Float2.X, _Float2.Y, 0.0f, 0.0f);
	Vector = DirectX::XMVector3Normalize(Vector);
	XMStoreFloat2(&ReturnValue.Float2, Vector);

	return ReturnValue;
}

void EngineMath::Normalize(SFloat3& _Float3)
{
	DirectX::XMVECTOR Vector = DirectX::XMVectorSet(_Float3.X, _Float3.Y, _Float3.Z, 0.0f);
	Vector = DirectX::XMVector3Normalize(Vector);
	XMStoreFloat3(&_Float3.Float3, Vector);
}

SFloat3 EngineMath::NormalizeReturn(const SFloat3& _Float3)
{
	SFloat3 ReturnValue;

	DirectX::XMVECTOR Vector = DirectX::XMVectorSet(_Float3.X, _Float3.Y, _Float3.Z, 0.0f);
	Vector = DirectX::XMVector3Normalize(Vector);
	XMStoreFloat3(&ReturnValue.Float3, Vector);

	return ReturnValue;
}

void EngineMath::Normalize(SFloat4& _Float4)
{
	_Float4.Vector4 = DirectX::XMVector4Normalize(_Float4.Vector4);
}

SFloat4 EngineMath::NormalizeReturn(const SFloat4& _Float4)
{
	SFloat4 ReturnValue;
	ReturnValue.Vector4 = DirectX::XMVector4Normalize(_Float4.Vector4);
	return ReturnValue;
}

void EngineMath::NormalizeQuaternion(SFloat4& _Float4)
{
	_Float4.Vector4 = DirectX::XMQuaternionNormalize(_Float4.Vector4);
}

SFloat4 EngineMath::NormalizeQuaternionReturn(const SFloat4& _Float4)
{
	SFloat4 ReturnValue;
	ReturnValue.Vector4 = DirectX::XMQuaternionNormalize(_Float4.Vector4);
	return ReturnValue;
}

void EngineMath::QuaternionToEuler(SFloat4& _Quaternion)
{
	float QuatX = _Quaternion.X;
	float QuatY = _Quaternion.Y;
	float QuatZ = _Quaternion.Z;
	float QuatW = _Quaternion.W;

	_Quaternion.X = atan2f(2.0f * (QuatY * QuatW + QuatX * QuatZ), 1.0f - 2.0f * (QuatX * QuatX + QuatY * QuatY));
	_Quaternion.Y = asinf(2.0f * (QuatY * QuatZ - QuatW * QuatX));
	_Quaternion.Z = atan2f(2.0f * (QuatX * QuatW + QuatY * QuatZ), 1.0f - 2.0f * (QuatY * QuatY + QuatZ * QuatZ));

	_Quaternion.RadianToDegree();
}

SFloat4 EngineMath::QuaternionToEulerReturn(const SFloat4& _Quaternion)
{
	SFloat4 Euler;

	float QuatX = _Quaternion.X;
	float QuatY = _Quaternion.Y;
	float QuatZ = _Quaternion.Z;
	float QuatW = _Quaternion.W;

	float sinrCosp = 2.0f * (QuatW * QuatZ + QuatX * QuatY);
	float cosrCosp = 1.0f - 2.0f * (QuatZ * QuatZ + QuatX * QuatX);
	Euler.Z = atan2f(sinrCosp, cosrCosp);

	float pitchTest = QuatW * QuatX - QuatY * QuatZ;
	float asinThreshold = 0.4999995f;
	float sinp = 2.0f * pitchTest;

	if (pitchTest < -asinThreshold)
	{
		Euler.X = -(0.5f * EnginePI);
	}
	else if (pitchTest > asinThreshold)
	{
		Euler.X = (0.5f * EnginePI);
	}
	else
	{
		Euler.X = asinf(sinp);
	}

	float sinyCosp = 2.0f * (QuatW * QuatY + QuatX * QuatZ);
	float cosyCosp = 1.0f - 2.0f * (QuatX * QuatX + QuatY * QuatY);
	Euler.Y = atan2f(sinyCosp, cosyCosp);

	Euler.RadianToDegree();
	
	return Euler;
}

//인자는 Degree로 대입할 것
void EngineMath::EulerToQuaternion(SFloat4& _Euler)
{
	_Euler.Vector4 = DirectX::XMQuaternionRotationRollPitchYawFromVector(_Euler.DegreeToRadianReturn().Vector4);
}

//인자는 Degree로 대입할 것
SFloat4 EngineMath::EulerToQuaternionReturn(const SFloat4& _Euler)
{
	SFloat4 Quaternion;
	Quaternion.Vector4 = DirectX::XMQuaternionRotationRollPitchYawFromVector(_Euler.DegreeToRadianReturn().Vector4);
	return Quaternion;
}

void EngineMath::DegreeToRadian(SFloat4& _Degree)
{
	_Degree.X = _Degree.X * EnginePI / 180.0f;
	_Degree.Y = _Degree.Y * EnginePI / 180.0f;
	_Degree.Z = _Degree.Z * EnginePI / 180.0f;
}

SFloat4 EngineMath::DegreeToRadianReturn(const SFloat4& _Degree)
{
	SFloat4 Radian;

	Radian.X = _Degree.X * EnginePI / 180.0f;
	Radian.Y = _Degree.Y * EnginePI / 180.0f;
	Radian.Z = _Degree.Z * EnginePI / 180.0f;

	return Radian;
}

void EngineMath::RadianToDegree(SFloat4& _Radian)
{
	_Radian.X = _Radian.X * 180.0f / EnginePI;
	_Radian.Y = _Radian.Y * 180.0f / EnginePI;
	_Radian.Z = _Radian.Z * 180.0f / EnginePI;
}

SFloat4 EngineMath::RadianToDegreeReturn(const SFloat4& _Radian)
{
	SFloat4 Degree;

	Degree.X = _Radian.X * 180.0f / EnginePI;
	Degree.Y = _Radian.Y * 180.0f / EnginePI;
	Degree.Z = _Radian.Z * 180.0f / EnginePI;

	return Degree;
}

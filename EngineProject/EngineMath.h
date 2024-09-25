#pragma once
#include "DirectXHeader.h"

constexpr static float EnginePI = DirectX::XM_PI;

struct SFloat2;
struct SFloat3;
struct SFloat4;
struct SFloat4x4;

class EngineMath
{
	//Elementary Arithmetic (사칙연산)
public:
	static void AddFloat4(SFloat4& _Stored, const SFloat4& _Add);
	static SFloat4 AddFloat4Return(const SFloat4& _Left, const SFloat4& _Right);

	static void SubFloat4(SFloat4& _Stored, const SFloat4& _Sub);
	static SFloat4 SubFloat4Return(const SFloat4& _Left, const SFloat4& _Right);

	static void MulFloat4(SFloat4& _Stored, const SFloat4& _Sub);
	static SFloat4 MulFloat4Return(const SFloat4& _Left, const SFloat4& _Right);

	static void DivFloat4(SFloat4& _Stored, const SFloat4& _Sub);
	static SFloat4 DivFloat4Return(const SFloat4& _Left, const SFloat4& _Right);

	static void MulQuaternion(SFloat4& _Stored, const SFloat4& _Mul);
	static SFloat4 MulQuaternionReturn(const SFloat4& _Left, const SFloat4& _Right);

	static void MulFloat4x4(SFloat4x4& _Stored, const SFloat4x4& _Mul);
	static SFloat4x4 MulFloat4x4Return(const SFloat4x4& _Left, const SFloat4x4& _Right);

	//Normalize
public:
	static void Normalize(SFloat2& _Float2);
	static SFloat2 NormalizeReturn(const SFloat2& _Float2);

	static void Normalize(SFloat3& _Float3);
	static SFloat3 NormalizeReturn(const SFloat3& _Float3);

	static void Normalize(SFloat4& _Float4);
	static SFloat4 NormalizeReturn(const SFloat4& _Float4);
	
	static void NormalizeQuaternion(SFloat4& _Float4);
	static SFloat4 NormalizeQuaternionReturn(const SFloat4& _Float4);

	//Convert
public:
	static void QuaternionToEuler(SFloat4& _Quaternion);
	static SFloat4 QuaternionToEulerReturn(const SFloat4& _Quaternion);

	static void EulerToQuaternion(SFloat4& _Euler);
	static SFloat4 EulerToQuaternionReturn(const SFloat4& _Euler);

	static void DegreeToRadian(SFloat4& _Degree);
	static SFloat4 DegreeToRadianReturn(const SFloat4& _Degree);

	static void RadianToDegree(SFloat4& _Radian);
	static SFloat4 RadianToDegreeReturn(const SFloat4& _Radian);

protected:

private:

};

struct SFloat2
{
	//Constructor
public:
	SFloat2()
		:X(0.0f), Y(0.0f)
	{

	}

	SFloat2(const float _X, const float _Y)
		:X(_X), Y(_Y)
	{

	}

	SFloat2(const SFloat2& _Float2)
		:X(_Float2.X), Y(_Float2.Y)
	{

	}

	//Util Function
public:
	void Normalize()
	{
		EngineMath::Normalize(*this);
	}

	SFloat2 NormalizeReturn() const
	{
		return EngineMath::NormalizeReturn(*this);
	}

public:
	union
	{
		struct
		{
			float X;
			float Y;
		};

		DirectX::XMFLOAT2 Float2;
	};
};

struct SFloat3
{
	//Constructor
public:
	SFloat3()
		: X(0.0f), Y(0.0f), Z(0.0f)
	{

	}

	SFloat3(const float _X, const float _Y, const float _Z)
		:X(_X), Y(_Y), Z(_Z)
	{

	}

	SFloat3(const SFloat2& _Float2)
		:X(_Float2.X), Y(_Float2.Y), Z(0.0f)
	{

	}

	SFloat3(const SFloat2& _Float2, const float _Z)
		:X(_Float2.X), Y(_Float2.Y), Z(_Z)
	{

	}

	SFloat3(const SFloat3& _Float3)
		:X(_Float3.X), Y(_Float3.Y), Z(_Float3.Z)
	{

	}

	//Operator
public:

	//Util Function
public:
	void Normalize()
	{
		EngineMath::Normalize(*this);
	}

	SFloat3 NormalizeReturn() const
	{
		return EngineMath::NormalizeReturn(*this);
	}

public:
	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
		};

		struct
		{
			SFloat2 XY;
			float Z;
		};

		DirectX::XMFLOAT3 Float3;
	};
};

struct SFloat4
{
	//Constructor
public:
	SFloat4()
		: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
	{

	}

	SFloat4(const float _X, const float _Y, const float _Z)
		: X(_X), Y(_Y), Z(_Z), W(1.0f)
	{

	}

	SFloat4(const float _X, const float _Y, const float _Z, const float _W)
		: X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}

	SFloat4(const SFloat2& _Float2)
		: X(_Float2.X), Y(_Float2.Y), Z(0.0f), W(1.0f)
	{

	}

	SFloat4(const SFloat2& _XY, const SFloat2& _ZW)
		: X(_XY.X), Y(_XY.Y), Z(ZW.X), W(ZW.Y)
	{

	}

	SFloat4(const SFloat3& _Float3)
		: X(_Float3.X), Y(_Float3.Y), Z(_Float3.Z), W(1.0f)
	{

	}

	SFloat4(const SFloat3& _Float3, const float _W)
		: X(_Float3.X), Y(_Float3.Y), Z(_Float3.Z), W(_W)
	{

	}

	SFloat4(const SFloat4& _Float4)
		: X(_Float4.X), Y(_Float4.Y), Z(_Float4.Z), W(_Float4.W)
	{

	}
	//operator
public:
	SFloat4 operator+(const SFloat4& _Other) const
	{
		return EngineMath::AddFloat4Return(*this, _Other);
	}

	void operator+=(const SFloat4& _Other)
	{
		EngineMath::AddFloat4(*this, _Other);
	}

	SFloat4 operator-(const SFloat4& _Other) const
	{
		return EngineMath::SubFloat4Return(*this, _Other);
	}

	void operator-=(const SFloat4& _Other)
	{
		EngineMath::SubFloat4(*this, _Other);
	}

	SFloat4 operator*(const SFloat4& _Other) const
	{
		return EngineMath::MulFloat4Return(*this, _Other);
	}

	void operator*=(const SFloat4& _Other)
	{
		EngineMath::MulFloat4(*this, _Other);
	}

	SFloat4 operator/(const SFloat4& _Other) const
	{
		return EngineMath::DivFloat4Return(*this, _Other);
	}

	void operator/=(const SFloat4& _Other)
	{
		EngineMath::DivFloat4(*this, _Other);
	}

	//Util Function
public:
	void Normalize()
	{
		EngineMath::Normalize(*this);
	}

	SFloat4 NormalizeReturn() const
	{
		return EngineMath::NormalizeReturn(*this);
	}

	void QuaternionToEuler()
	{
		EngineMath::QuaternionToEuler(*this);
	}

	SFloat4 QuaternionToEulerReturn() const
	{
		return EngineMath::QuaternionToEulerReturn(*this);
	}

	void EulerToQuaternion()
	{
		EngineMath::EulerToQuaternion(*this);
	}

	SFloat4 EulerToQuaternionReturn() const 
	{
		return EngineMath::EulerToQuaternionReturn(*this);
	}

	void DegreeToRadian()
	{
		EngineMath::DegreeToRadian(*this);
	}

	SFloat4 DegreeToRadianReturn() const
	{
		return EngineMath::DegreeToRadianReturn(*this);
	}

	void RadianToDegree()
	{
		EngineMath::RadianToDegree(*this);
	}

	SFloat4 RadianToDegreeReturn() const
	{
		return EngineMath::RadianToDegreeReturn(*this);
	}

	void MulQuaternion(const SFloat4& _Quat)
	{
		EngineMath::MulQuaternion(*this, _Quat);
	}

	SFloat4 MulQuaternionReturn(const SFloat4& _Quat) const
	{
		return EngineMath::MulQuaternionReturn(*this, _Quat);
	}

public:
	union alignas(16)
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		struct
		{
			float R;
			float G;
			float B;
			float A;
		};

		struct
		{
			SFloat2 XY;
			SFloat2 ZW;
		};

		struct
		{
			SFloat3 XYZ;
			float W;
		};

		DirectX::XMFLOAT4 Float4;
		DirectX::XMVECTOR Vector4;
	};

private:
};

struct SFloat4x4
{
public:
	SFloat4x4()
	{
		Identify();
	}

	SFloat4x4(const SFloat4x4& _Other)
		:Float4x4(_Other.Float4x4)
	{
		
	}

public:
	void operator=(const SFloat4x4& _Other)
	{
		Float4x4 = _Other.Float4x4;
	}

	void operator*(const SFloat4x4& _Other)
	{
		EngineMath::MulFloat4x4(*this, _Other);
	}

	SFloat4x4 operator*=(const SFloat4x4& _Other)
	{
		return EngineMath::MulFloat4x4Return(*this, _Other);
	}

	//Util Function
public:
	void Identify()
	{
		Matrix4x4 = DirectX::XMMatrixIdentity();
	}

public:
	union
	{
		struct
		{
			SFloat4 _1;
			SFloat4 _2;
			SFloat4 _3;
			SFloat4 _4;
		};

		DirectX::XMFLOAT4X4 Float4x4;
		DirectX::XMMATRIX Matrix4x4;
	};
};

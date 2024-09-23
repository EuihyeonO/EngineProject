#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <DirectXMath.h>

#include "BaseHeader.h"

//Comptr
template <typename T>
using MSComPtr = Microsoft::WRL::ComPtr<T>;

//저장
using Float2 = DirectX::XMFLOAT2;
using Float3 = DirectX::XMFLOAT3;
using Float4 = DirectX::XMFLOAT4;
using Float4x4 = DirectX::XMFLOAT4X4;

//계산
using Vector4 = DirectX::XMVECTOR;
using Matrix4x4 = DirectX::XMMATRIX;

enum class ShaderType
{
	Vertex,
	Geometry,
	Compute,
	Pixel,
};

struct SConstantBuffer
{
	MSComPtr<ID3D11Buffer> ConstantBuffer;
	size_t BindPoint;
	size_t Size;
	void* Data;
};

struct SSamperState
{
	MSComPtr<ID3D11SamplerState> SamplerState;
	size_t BindPoint;
};
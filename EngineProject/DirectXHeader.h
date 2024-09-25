#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <DirectXMath.h>

#include "BaseHeader.h"

//Comptr
template <typename T>
using MSComPtr = Microsoft::WRL::ComPtr<T>;

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
	UINT BindPoint;
	UINT Size;
	void* Data;
};

struct SSamplerState
{
	MSComPtr<ID3D11SamplerState> SamplerState;
	UINT BindPoint;
};
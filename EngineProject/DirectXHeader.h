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

struct SRenderState
{
	MSComPtr<ID3D11Buffer> VertexBuffer = nullptr;
	MSComPtr<ID3D11Buffer> IndexBuffer = nullptr;
	
	MSComPtr<ID3D11VertexShader> VertexShader = nullptr;
	MSComPtr<ID3D11PixelShader> PixelShader = nullptr;

	MSComPtr<ID3D11InputLayout> InputLayout = nullptr;

	D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
	D3D11_VIEWPORT ViewPort;

	MSComPtr<ID3D11DepthStencilView> DSV = nullptr;
	MSComPtr<ID3D11DepthStencilState> DSState = nullptr;

	MSComPtr<ID3D11RasterizerState> RSState = nullptr;
};
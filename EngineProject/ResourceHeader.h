#pragma once

#include <vector>
#include <string>
#include <memory>

#include "EngineVertexShader.h"
#include "EnginePixelShader.h"

struct SVertex
{
	Float3 Position;
	Float3 Normal;
	Float2 Texcoord;
};

enum VertexOffset
{
	POSITION = 0,
	NORMAL = 12,
	TEXCOORED = 24,
};

struct SMesh
{
	std::vector<SVertex> Vertices;
	std::vector<uint32_t> Indices;
};

struct STextureData
{
	size_t BindPoint;

	MSComPtr<ID3D11Texture2D> Texture2D = nullptr;
	MSComPtr<ID3D11ShaderResourceView> SRV = nullptr;
};

struct SMaterial
{
	MSComPtr<ID3D11Buffer> VertexBuffer;
	MSComPtr<ID3D11Buffer> IndexBuffer;

	std::shared_ptr<EngineVertexShader> VertexShader;
	std::shared_ptr<EnginePixelShader> PixelShader;

	STextureData DiffuseTexture;
	STextureData NormalTexture;
};

struct SMeshData
{
	MSComPtr<ID3D11Buffer> VertexBuffer = nullptr;
	MSComPtr<ID3D11Buffer> IndexBuffer = nullptr;
	
	STextureData DiffuseTexture;
	STextureData NormalTexture;
};

struct AnimData
{

};


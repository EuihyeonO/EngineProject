#pragma once
#include <vector>
#include <string>

#include "DirectXHeader.h"

struct SVertex
{
	Float3 Position;
	Float3 Normal;
	Float2 Texcoord;
};

struct SMesh
{
	std::vector<SVertex> Vertices;
	std::vector<uint32_t> Indices;
};

struct SMaterial
{
	std::string DiffuseTexture = "";
	std::string NormalTexture = "";
};

struct SMeshData
{
	MSComPtr<ID3D11Buffer> VertexBuffer;
	MSComPtr<ID3D11Buffer> IndexBuffer;
	
	SMaterial Material;
};

struct AnimData
{

};

struct TextureData
{

};

struct MaterialData
{

};
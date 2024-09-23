#pragma once
#include "DirectXHeader.h"
#include "ResourceHeader.h"
#include "EngineResourceManager.h"
#include "EngineVertexShader.h"

#include <unordered_map>

class EngineRenderUnit
{

public:

	EngineRenderUnit();
	~EngineRenderUnit();

	EngineRenderUnit(const EngineRenderUnit& _Other) = delete;
	EngineRenderUnit(EngineRenderUnit&& _Other) noexcept = delete;
	EngineRenderUnit& operator=(const EngineRenderUnit& _Other) = delete;
	EngineRenderUnit& operator=(EngineRenderUnit&& _Other) noexcept = delete;

	void SetMesh(const SMeshData& _Mesh)
	{
		Material.VertexBuffer = _Mesh.VertexBuffer;
		Material.IndexBuffer = _Mesh.IndexBuffer;

		Material.DiffuseTexture = _Mesh.DiffuseTexture;
		Material.NormalTexture = _Mesh.NormalTexture;
	}

	void SetVertexShader(std::shared_ptr<EngineVertexShader> _VertexShader)
	{
		if (_VertexShader == nullptr)
		{ 
			return;
		}
		
		Material.VertexShader = nullptr;

		std::shared_ptr<EngineVertexShader> VertexShader = std::make_shared<EngineVertexShader>();

		const std::unordered_map<std::string, SConstantBuffer>& AllCBuffer = _VertexShader->GetAllConstantBuffer();
		for (const std::pair<std::string, SConstantBuffer>& Buffer : AllCBuffer)
		{
			VertexShader->AddConstantBuffer(Buffer.first, Buffer.second);
		}

		Material.VertexShader = VertexShader;
	}

	void SetPixelShader(std::shared_ptr<EnginePixelShader> _PixelShader)
	{
		if (_PixelShader == nullptr)
		{
			return;
		}

		Material.PixelShader = nullptr;

		std::shared_ptr<EnginePixelShader> PixelShader = std::make_shared<EnginePixelShader>();
		
		const std::unordered_map<std::string, STextureData>& AllTexture = _PixelShader->GetAllTexture();
		for (const std::pair<std::string, STextureData>& Texture : AllTexture)
		{
			PixelShader->AddTexture(Texture.first, Texture.second);
		}

		Material.PixelShader = PixelShader;
		
		if (PixelShader->HasTexture("DIFFUSETEX") == true)
		{
			Material.PixelShader->SetTexture("DIFFUSETEX", Material.DiffuseTexture);
		}
		
		if (PixelShader->HasTexture("NORMALTEX") == true)
		{
			Material.PixelShader->SetTexture("NORMALTEX", Material.NormalTexture);
		}
	}

	template<typename DataType>
	void SetVSConstantBuffer(std::string_view _Name, DataType* _Data)
	{
		Material.VertexShader->SetConstantBuffer(_Name, _Data);
	}

protected:

private:
	SMaterial Material;
};


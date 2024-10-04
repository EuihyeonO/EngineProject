#pragma once
#include "EngineDirectX.h"
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

	void SetMesh(const SMeshData& _Mesh);
	void SetSampler(std::string_view _Name);
	void SetVertexShader(std::shared_ptr<EngineVertexShader> _VertexShader);
	void SetPixelShader(std::shared_ptr<EnginePixelShader> _PixelShader);
	
	std::shared_ptr<EngineVertexShader> GetVertexShader()
	{
		return Material.VertexShader;
	}

	std::shared_ptr<EnginePixelShader> GetPixelShader()
	{
		return Material.PixelShader;
	}
	
	template<typename DataType>
	void SetVSConstantBuffer(std::string_view _Name, DataType* _Data)
	{
		Material.VertexShader->SetConstantBuffer(_Name, _Data);
	}

	template<typename DataType>
	void SetPSConstantBuffer(std::string_view _Name, DataType* _Data)
	{
		Material.PixelShader->SetConstantBuffer(_Name, _Data);
	}

	void Render()
	{
		EngineDirectX::RenderSetting(Material.VertexShader, Material.PixelShader, Material.VertexBuffer, Material.IndexBuffer);
		EngineDirectX::DrawIndexed(Material.IndexCount, 0, 0);
	}

protected:

private:
	SMaterial Material;
};


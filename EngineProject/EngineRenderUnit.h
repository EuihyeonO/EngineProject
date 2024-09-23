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
		
		Material.VertexShader = _VertexShader;

		ConstantBuffers.clear();

		const std::unordered_map<std::string, SConstantBuffer>& AllCBuffer = _VertexShader->GetAllConstantBuffer();
		for (const std::pair<std::string, SConstantBuffer>& _Data : AllCBuffer)
		{
			ConstantBuffers.insert(_Data);
		}
	}

	template<typename DataType>
	void SetConstantBuffer(std::string_view _Name, DataType* _Data)
	{
		if (ConstantBuffers.find(_Name.data()) == ConstantBuffers.end())
		{
			std::cerr << "Error : ConstantBuffer that you try to set is invalid." << std::endl;
			return;
		}

		if (ConstantBuffers[_Name.data()].Size != sizeof(DataType))
		{
			std::cerr << "Error : Size of constantBuffer data that you try to set is not same size of shader constant." << std::endl;
			return;
		}

		ConstantBuffers[_Name.data()].Data = reinterpret_cast<void*>(_Data);
	}

protected:

private:
	SMaterial Material;

	std::unordered_map<std::string, SConstantBuffer> ConstantBuffers;
};


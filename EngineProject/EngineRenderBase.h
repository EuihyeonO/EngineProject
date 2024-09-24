#pragma once

#include <memory>
#include <string_view>

#include "DirectXHeader.h"
#include "EngineRenderUnit.h"
#include "EngineResourceManager.h"

class EngineRenderBase
{

public:

	EngineRenderBase();
	~EngineRenderBase();

	EngineRenderBase(const EngineRenderBase& _Other) = delete;
	EngineRenderBase(EngineRenderBase&& _Other) noexcept = delete;
	EngineRenderBase& operator=(const EngineRenderBase& _Other) = delete;
	EngineRenderBase& operator=(EngineRenderBase&& _Other) noexcept = delete;

	void SetVertexShader(std::string_view _VertexShaderName)
	{
		std::shared_ptr<class EngineVertexShader> VertexShader = EngineResourceManager::FindVertexShader(_VertexShaderName);

		if (VertexShader == nullptr)
		{
			std::cerr << "VertexShader that you try to set is not loaded. ShaderName : " << _VertexShaderName.data() << std::endl;
			return;
		}

		for (std::shared_ptr<EngineRenderUnit> _Unit : RenderUnits)
		{
			_Unit->SetVertexShader(VertexShader);
		}
	}

	void SetPixelShader(std::string_view _PixelShaderName)
	{
		std::shared_ptr<class EnginePixelShader> PixelShader = EngineResourceManager::FindPixelShader(_PixelShaderName);

		if (PixelShader == nullptr)
		{
			std::cerr << "PixelShader that you try to set is not loaded. ShaderName : " << _PixelShaderName.data() << std::endl;
			return;
		}

		for (std::shared_ptr<EngineRenderUnit> _Unit : RenderUnits)
		{
			_Unit->SetPixelShader(PixelShader);
		}
	}

	template<typename DataType>
	void SetVSConstantBuffer(std::string_view _Name, DataType* _Data)
	{
		for (std::shared_ptr<EngineRenderUnit> _Unit : RenderUnits)
		{
			_Unit->SetVSConstantBuffer(_Name, _Data);
		}
	}

	template<typename DataType>
	void SetPSConstantBuffer(std::string_view _Name, DataType* _Data)
	{
		for (std::shared_ptr<EngineRenderUnit> _Unit : RenderUnits)
		{
			_Unit->SetPSConstantBuffer(_Name, _Data);
		}
	}

	void OnDestroyed()
	{
		RenderUnits.clear();
	}
	
	void Render()
	{
		for (std::shared_ptr<EngineRenderUnit> _Unit : RenderUnits)
		{
			_Unit->Render();
		}
	}

protected:
	std::vector<std::shared_ptr<EngineRenderUnit>> RenderUnits;
private:

};


#pragma once
#include "EngineComponent.h"
#include "EngineRenderUnit.h"
#include "EngineResourceManager.h"

#include <memory>
#include <string_view>
#include <vector>

class SkeletalMeshComponent : public EngineComponent
{

public:
	SkeletalMeshComponent();
	~SkeletalMeshComponent();

	SkeletalMeshComponent(const SkeletalMeshComponent& _Other) = delete;
	SkeletalMeshComponent(SkeletalMeshComponent&& _Other) noexcept = delete;
	SkeletalMeshComponent& operator=(const SkeletalMeshComponent& _Other) = delete;
	SkeletalMeshComponent& operator=(SkeletalMeshComponent&& _Other) noexcept = delete;

	void SetMesh(std::string_view _Name);

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

	void OnCreated() override {}
	void Start() override {}
	void Update() override {}
	
	void End() override {}

	void OnDestroyed() override { RenderUnits.clear(); }

protected:

private:
	std::vector<std::shared_ptr<EngineRenderUnit>> RenderUnits;
};


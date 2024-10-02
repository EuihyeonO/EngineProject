#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include <list>

#include "EngineString.h"
#include "ResourceHeader.h"
#include "DirectXHeader.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"

template <typename T>
concept ShaderTemplate = std::is_same_v<T, EngineVertexShader>  ||
                         std::is_same_v<T, EnginePixelShader>   ||
                         std::is_same_v<T, ID3D11GeometryShader>||
                         std::is_same_v<T, ID3D11ComputeShader>;

class EngineResourceManager
{

public:

	EngineResourceManager();
	~EngineResourceManager();

	EngineResourceManager(const EngineResourceManager& _Other) = delete;
	EngineResourceManager(EngineResourceManager&& _Other) noexcept = delete;
	EngineResourceManager& operator=(const EngineResourceManager& _Other) = delete;
	EngineResourceManager& operator=(EngineResourceManager&& _Other) noexcept = delete;
	
	//Shader
public:
	template<typename Shader> requires ShaderTemplate<Shader>
	static std::shared_ptr<Shader> FindShader(std::string_view _Name)
	{
		if constexpr (std::is_same_v<Shader, class EngineVertexShader>)
		{
			return FindVertexShader(_Name);
		}
		else if constexpr (std::is_same_v<Shader, class EnginePixelShader>)
		{
			return FindPixelShader(_Name);
		}
		else if constexpr (std::is_same_v<Shader, ID3D11GeometryShader>)
		{
			EngineDebug::LogErrorMsg("구현되지 않은 쉐이더타입 입니다.");
			return nullptr;
		}
		else if constexpr (std::is_same_v<Shader, ID3D11GeometryShader>)
		{
			EngineDebug::LogErrorMsg("구현되지 않은 쉐이더타입 입니다.");
			return nullptr;
		}
		else
		{
			EngineDebug::LogErrorMsg("지원하지 않는 쉐이더 타입이 아닙니다.");
			return nullptr;
		}
	}

public:
	static const std::shared_ptr<std::list<SMeshData>> FindMesh(std::string_view _Name);
	static std::shared_ptr<class EngineVertexShader> FindVertexShader(std::string_view _Name);
	static std::shared_ptr<class EnginePixelShader> FindPixelShader(std::string_view _Name);

	static void AddLoadedMesh(const std::string& _Name, std::shared_ptr<std::list<SMeshData>>& _MeshData);
	static void AddSamplerState(std::string_view _Name, MSComPtr<ID3D11SamplerState> _SamplerState);
	static void AddLoadedTexture(std::string_view _Name, STextureData _TextureData);
	static void AddLoadedVertexShader(std::string_view _Name, const std::shared_ptr<class EngineVertexShader> _VertexShader);
	static void AddLoadedPixelShader(std::string_view _Name, const std::shared_ptr<EnginePixelShader> _PixelShader);
	
	static void AddDSState(std::string_view _Name, const MSComPtr<ID3D11DepthStencilState> _DSState);
	static void AddBlendState(std::string_view _Name, const MSComPtr<ID3D11BlendState> _BlendState);
	static void AddRasterizerState(std::string_view _Name, const MSComPtr<ID3D11RasterizerState> _RasterizerState);

	static STextureData FindTexture(std::string_view _Name);
	static MSComPtr<ID3D11SamplerState> FindSampler(std::string_view _Name);
	static const MSComPtr<ID3D11BlendState> FindBlendState(std::string_view _Name);
	static const MSComPtr<ID3D11RasterizerState> FindRasterizerState(std::string_view _Name);
	static const MSComPtr<ID3D11DepthStencilState> FindDSState(std::string_view _Name);

protected:
	
private:
	static std::unordered_map<std::string, STextureData> LoadedTexture;
	static std::unordered_map<std::string, std::shared_ptr<std::list<SMeshData>>> LoadedMeshes;

	static std::unordered_map<std::string, std::shared_ptr<class EngineVertexShader>> LoadedVertexShaders;
	static std::unordered_map<std::string, std::shared_ptr<class EnginePixelShader>> LoadedPixelShaders;

	static std::unordered_map<std::string, MSComPtr<ID3D11SamplerState>> SamplerStates;
	static std::unordered_map<std::string, MSComPtr<ID3D11DepthStencilState>> DSStates;

	static std::unordered_map<std::string, MSComPtr<ID3D11RasterizerState>> RasterizerStates;
	static std::unordered_map<std::string, MSComPtr<ID3D11BlendState>> BlendStates;
};


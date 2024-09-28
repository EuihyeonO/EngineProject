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
concept ShaderTemplate = std::is_same_v<T, class EngineVertexShader>  ||
                         std::is_same_v<T, class EnginePixelShader>   ||
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
	
	//Mesh
	static const std::shared_ptr<std::list<SMeshData>> FindMesh(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedMeshes.find(UpperName) == LoadedMeshes.end())
		{
			return nullptr;
		}

		return LoadedMeshes[UpperName];
	}

	static void AddLoadedMesh(const std::string& _Name, std::shared_ptr<std::list<SMeshData>>& _MeshData)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (FindMesh(UpperName) != nullptr)
		{
			EngineDebug::LogErrorMsg(L"같은 이름의 메쉬가 이미 존재합니다.");
			return;
		}

		LoadedMeshes[UpperName] = _MeshData;
	}

	//Shader
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
		else if constexpr (std::is_same_v<Shader,ID3D11GeometryShader>)
		{
			return nullptr;
		}
		else if constexpr (std::is_same_v<Shader, ID3D11GeometryShader>)
		{
			return nullptr;
		}
		else
		{
			EngineDebug::LogErrorMsg("지원하지 않는 쉐이더 타입닙니다.");
			return nullptr;
		}
	}

	static std::shared_ptr<class EngineVertexShader> FindVertexShader(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedVertexShaders.find(UpperName) != LoadedVertexShaders.end())
		{
			return LoadedVertexShaders[UpperName];
		}

		return nullptr;
	}

	static std::shared_ptr<class EnginePixelShader> FindPixelShader(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedPixelShaders.find(UpperName) != LoadedPixelShaders.end())
		{
			return LoadedPixelShaders[UpperName];
		}

		return nullptr;
	}

	static STextureData FindTexture(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedTexture.find(UpperName) != LoadedTexture.end())
		{
			return LoadedTexture[UpperName];
		}

		return { 0, nullptr, nullptr };
	}

	static void AddLoadedVertexShader(std::string_view _Name, const std::shared_ptr<class EngineVertexShader> _VertexShader)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (FindShader<class EngineVertexShader>(UpperName) != nullptr)
		{
			EngineDebug::LogErrorMsg(L"같은 이름의 버텍스 쉐이더가 이미 존재합니다.");
			return;
		}

		LoadedVertexShaders[UpperName] = _VertexShader;
	}

	static void AddLoadedPixelShader(std::string_view _Name, const std::shared_ptr<EnginePixelShader> _PixelShader)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (FindShader<EnginePixelShader>(UpperName) != nullptr)
		{
			EngineDebug::LogErrorMsg(L"같은 이름의 픽셀 쉐이더가 이미 존재합니다.");
			return;
		}

		LoadedPixelShaders[UpperName] = _PixelShader;
	}

	static void AddLoadedTexture(std::string_view _Name, STextureData _TextureData)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedTexture.find(UpperName) != LoadedTexture.end())
		{
			EngineDebug::LogErrorMsg(L"같은 이름의 텍스쳐가 이미 존재합니다.");
			return;
		}

		LoadedTexture[UpperName] = _TextureData;
	}

	static MSComPtr<ID3D11SamplerState> FindSampler(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (SamplerStates.find(UpperName) == SamplerStates.end())
		{
			return nullptr;
		}

		return SamplerStates[_Name.data()];
	}

	static void AddSamplerState(std::string_view _Name, MSComPtr<ID3D11SamplerState> _SamplerState)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (SamplerStates.find(UpperName) != SamplerStates.end())
		{
			EngineDebug::LogErrorMsg(L"같은 이름의 샘플러가 이미 존재합니다.");
			return;
		}

		SamplerStates[UpperName] = _SamplerState;
	}

	static const MSComPtr<ID3D11DepthStencilState> FindDSState(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());
		
		if (DSStates.find(UpperName) != DSStates.end())
		{
			return DSStates[UpperName];
		}

		return nullptr;
	}

	static const void AddDSState(std::string_view _Name, const MSComPtr<ID3D11DepthStencilState> _DSState)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (DSStates.find(UpperName) != DSStates.end())
		{
			EngineDebug::LogErrorMsg(L"같은 이름의 DSState가 이미 존재합니다.");
			return;
		}

		DSStates[UpperName] = _DSState;
	}

	static const MSComPtr<ID3D11RasterizerState> FindRasterizerState(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (RasterizerStates.find(UpperName) != RasterizerStates.end())
		{
			return RasterizerStates[UpperName];
		}

		return nullptr;
	}

	static const void AddRasterizerState(std::string_view _Name, const MSComPtr<ID3D11RasterizerState> _RasterizerState)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (RasterizerStates.find(UpperName) != RasterizerStates.end())
		{
			EngineDebug::LogErrorMsg(L"같은 이름의 RSState가 이미 존재합니다.");
			return;
		}

		RasterizerStates[UpperName] = _RasterizerState;
	}

	static const MSComPtr<ID3D11BlendState> FindBlendState(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (BlendStates.find(UpperName) != BlendStates.end())
		{
			return BlendStates[UpperName];
		}

		return nullptr;
	}

	static const void AddBlendState(std::string_view _Name, const MSComPtr<ID3D11BlendState> _BlendState)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (BlendStates.find(UpperName) != BlendStates.end())
		{
			EngineDebug::LogErrorMsg(L"같은 이름의 BlendState가 이미 존재합니다.");
			return;
		}

		BlendStates[UpperName] = _BlendState;
	}

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


#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include <list>

#include "EngineString.h"
#include "ResourceHeader.h"
#include "DirectXHeader.h"

template <typename T>
concept ShaderTemplate = std::is_same_v<T, ID3D11VertexShader>  ||
                         std::is_same_v<T, ID3D11PixelShader>   ||
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
	static const std::list<SMeshData>* FindMesh(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedMeshes.find(UpperName) == LoadedMeshes.end())
		{
			return nullptr;
		}

		return &LoadedMeshes[UpperName];
	}

	static void AddLoadedMesh(const std::string& _Name, std::list<SMeshData>&& _MeshData)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (FindMesh(UpperName) != nullptr)
		{
			std::cerr << "Error : Mesh(Name : " + UpperName + ") is already loaded." << std::endl;
			return;
		}

		LoadedMeshes[UpperName] = _MeshData;
	}

	//Shader
	template<typename Shader> requires ShaderTemplate<Shader>
	static MSComPtr<Shader> FindShader(std::string_view _Name)
	{
		if constexpr (std::is_same_v<Shader,ID3D11VertexShader>)
		{
			return FindVertexShader(_Name);
		}
		else if constexpr (std::is_same_v<Shader, ID3D11PixelShader>)
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
			std::cerr << "Error : Shader that Try to find is Invalid ShaderType." << std::endl;
			return nullptr;
		}
	}

	static MSComPtr<ID3D11VertexShader> FindVertexShader(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedVertexShaders.find(UpperName) != LoadedVertexShaders.end())
		{
			return LoadedVertexShaders[UpperName];
		}

		return nullptr;
	}

	static MSComPtr<ID3D11PixelShader> FindPixelShader(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedPixelShaders.find(UpperName) != LoadedPixelShaders.end())
		{
			return LoadedPixelShaders[UpperName];
		}

		return nullptr;
	}

	//Vertex Shader의 이름을 인자로 대입하면 된다.
	static MSComPtr<ID3D11InputLayout> FindInputLayOut(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedInputLayout.find(UpperName) != LoadedInputLayout.end())
		{
			return LoadedInputLayout[UpperName];
		}

		return nullptr;
	}

	static const TextureData FindTexture(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedTexture.find(UpperName) != LoadedTexture.end())
		{
			return LoadedTexture[UpperName];
		}

		return TextureData{ nullptr, nullptr };
	}

	static void AddLoadedVertexShader(std::string_view _Name, const  MSComPtr<ID3D11VertexShader>& _VertexShader)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (FindShader<ID3D11VertexShader>(UpperName) != nullptr)
		{
			std::cerr << "Error : Shader(Name : " + UpperName + ") is already loaded." << std::endl;
			return;
		}

		LoadedVertexShaders[UpperName] = _VertexShader;
	}

	static void AddLoadedPixelShader(std::string_view _Name, const MSComPtr<ID3D11PixelShader>& _PixelShader)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (FindShader<ID3D11PixelShader>(UpperName) != nullptr)
		{
			std::cerr << "Error : Shader(Name : " + UpperName + ") is already loaded." << std::endl;
			return;
		}

		LoadedPixelShaders[UpperName] = _PixelShader;
	}

	static void AddLoadedInputLayout(std::string_view _Name, const  MSComPtr<ID3D11InputLayout>& _InputLayOut)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedInputLayout.find(UpperName) != LoadedInputLayout.end())
		{
			std::cerr << "Error : InputLayout(Name : " + UpperName + ") is already loaded." << std::endl;
			return;
		}

		LoadedInputLayout[UpperName] = _InputLayOut;
	}

	static void AddLoadedTexture(std::string_view _Name, const TextureData& _TextureData)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (LoadedTexture.find(UpperName) != LoadedTexture.end())
		{
			std::cerr << "Error : Texture(Name : " + UpperName + ") is already loaded." << std::endl;
			return;
		}

		LoadedTexture[UpperName] = _TextureData;
	}
protected:
	
private:


private:
	static std::unordered_map<std::string, std::list<SMeshData>> LoadedMeshes;

	static std::unordered_map<std::string, MSComPtr<ID3D11VertexShader>> LoadedVertexShaders;
	static std::unordered_map<std::string, MSComPtr<ID3D11InputLayout>> LoadedInputLayout;

	static std::unordered_map<std::string, MSComPtr<ID3D11PixelShader>> LoadedPixelShaders;
	static std::unordered_map<std::string, TextureData> LoadedTexture;
};


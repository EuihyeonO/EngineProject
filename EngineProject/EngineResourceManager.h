#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include <list>

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
		if (LoadedMeshes.find(_Name.data()) == LoadedMeshes.end())
		{
			return nullptr;
		}

		return &LoadedMeshes[_Name.data()];
	}

	static void AddLoadedMesh(const std::string& _Name, std::list<SMeshData>&& _MeshData)
	{
		if (FindMesh(_Name) != nullptr)
		{
			std::cerr << "Error : Mesh(Name : " + _Name + ") is already loaded." << std::endl;
			return;
		}

		LoadedMeshes[_Name] = _MeshData;
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
		if (LoadedVertexShaders.find(_Name.data()) != LoadedVertexShaders.end())
		{
			return LoadedVertexShaders[_Name.data()];
		}

		return nullptr;
	}

	static MSComPtr<ID3D11PixelShader> FindPixelShader(std::string_view _Name)
	{
		if (LoadedPixelShaders.find(_Name.data()) != LoadedPixelShaders.end())
		{
			return LoadedPixelShaders[_Name.data()];
		}

		return nullptr;
	}

	static void AddLoadedVertexShader(const std::string& _Name, const  MSComPtr<ID3D11VertexShader>& _VertexShader)
	{
		if (FindShader<ID3D11VertexShader>(_Name) != nullptr)
		{
			std::cerr << "Error : Shader(Name : " + _Name + ") is already loaded." << std::endl;
			return;
		}

		LoadedVertexShaders[_Name] = _VertexShader;
	}

	static void AddLoadedInputLayout(const std::string& _Name, const  MSComPtr<ID3D11InputLayout>& _InputLayOut)
	{
		if (LoadedInputLayout.find(_Name.data()) != LoadedInputLayout.end())
		{
			std::cerr << "Error : Shader(Name : " + _Name + ") is already loaded." << std::endl;
			return;
		}

		LoadedInputLayout[_Name] = _InputLayOut;
	}

protected:
	
private:


private:
	static std::unordered_map<std::string, std::list<SMeshData>> LoadedMeshes;

	static std::unordered_map<std::string, MSComPtr<ID3D11VertexShader>> LoadedVertexShaders;
	static std::unordered_map<std::string, MSComPtr<ID3D11InputLayout>> LoadedInputLayout;

	static std::unordered_map<std::string, MSComPtr<ID3D11PixelShader>> LoadedPixelShaders;
};


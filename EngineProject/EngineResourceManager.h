#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include <list>

#include "ResourceHeader.h"
#include "DirectXHeader.h"

class EngineResourceManager
{

public:

	EngineResourceManager();
	~EngineResourceManager();

	EngineResourceManager(const EngineResourceManager& _Other) = delete;
	EngineResourceManager(EngineResourceManager&& _Other) noexcept = delete;
	EngineResourceManager& operator=(const EngineResourceManager& _Other) = delete;
	EngineResourceManager& operator=(EngineResourceManager&& _Other) noexcept = delete;
	
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

protected:
	
private:
	static std::unordered_map<std::string, std::list<SMeshData>> LoadedMeshes;
};


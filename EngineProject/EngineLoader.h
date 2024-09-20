#pragma once
#include "DirectXHeader.h"
#include "ResourceHeader.h"

#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"

#include <string_view>
#include <list>

#pragma comment(lib, "assimp-vc143-mtd.lib")

enum ExtensionType
{
	FBX,
	DDS,
	PNG,
};

class EngineLoader
{

public:

	EngineLoader();
	~EngineLoader();

	EngineLoader(const EngineLoader& _Other) = delete;
	EngineLoader(EngineLoader&& _Other) noexcept = delete;
	EngineLoader& operator=(const EngineLoader& _Other) = delete;
	EngineLoader& operator=(EngineLoader&& _Other) noexcept = delete;

	static void LoadAllFile(ExtensionType _Extension);
	static void LoadFile(std::string_view _FileName);

	static void LoadFBX(class EngineFile& _FileData);
protected:

private:
	static void LoadAllFBX();

	static void ProcessMeshNode(struct aiNode* _Node, const struct aiScene* _Scene, Float4x4 _Transform, std::list<SMeshData>& _MeshList);
	static void ProcessMesh(struct aiMesh* _Mesh, const struct aiScene* _Scene, Float4x4 _Transform, std::list<SMeshData>& _MeshList);
};


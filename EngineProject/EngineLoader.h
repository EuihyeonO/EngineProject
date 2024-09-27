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
	
	static void LoadAllFBX();
	static void LoadFBX(std::string_view _FileData);
	static void LoadFBX(class EngineFile& _FileData);

	static void LoadAllShader();
	static void LoadShader(std::string_view _FileName);
	static void LoadShader(class EngineFile& _ShaderFile);
	
	static void LoadAllPNG();
	static void LoadPNG(std::string_view _FileName);
	static void LoadPNG(class EngineFile& __FileData);

	static void LoadAllSampler();

	static void LoadAllDSState();
	static void LoadAllRasterizer();
	static void LoadAllBlendState();

protected:

private:
	static void LoadVertexShader(class EngineFile& _ShaderFile);
	static void LoadPixelShader(class EngineFile& _ShaderFile);

	static void ProcessMeshNode(struct aiNode* _Node, const struct aiScene* _Scene, const SFloat4x4& _Transform, std::shared_ptr<std::list<SMeshData>> _MeshList);
	static void ProcessMesh(struct aiMesh* _Mesh, const struct aiScene* _Scene, const SFloat4x4& _Transform, std::shared_ptr<std::list<SMeshData>> _MeshList);
};


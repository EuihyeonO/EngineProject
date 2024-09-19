#pragma once
#include "DirectXHeader.h"
#include "ResourceStruct.h"

#include <string_view>
#include <list>

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

	static void ProcessMeshNode(struct aiNode* _Node, const struct aiScene* _Scene, Float4x4 _Transform, std::list<SMesh>& _MeshList);
	static void ProcessMesh(struct aiMesh* _Mesh, const struct aiScene* _Scene, std::list<SMesh>& _MeshList, SMaterial& _Meterial);
};


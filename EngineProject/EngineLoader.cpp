#include "EngineLoader.h"
#include "EnginePath.h"
#include "EngineFile.h"
#include "EngineResourceManager.h"
#include "EngineMath.h"
#include "EngineDirectX.h"
#include "EngineString.h"

#include <iostream>

EngineLoader::EngineLoader()
{
}

EngineLoader::~EngineLoader()
{
}

void EngineLoader::LoadAllFile(ExtensionType _Extension)
{
	switch (_Extension)	
	{
	case FBX:
		LoadAllFBX();
		break;
	case DDS:
		break;
	case PNG:
		break;
	default:
		break;
	}
}

void EngineLoader::LoadFile(std::string_view _FileName)
{
	EngineFile FileData;
	EnginePath::FindFile(_FileName, FileData);

	std::string_view Extension = FileData.GetExtension();

	if (Extension == ".FBX")
	{
		LoadFBX(FileData);
	}
}

void EngineLoader::ShaderLoad(std::string_view _FileName)
{
	EngineFile File;
	EnginePath::FindFile(_FileName, File);

	if (File.GetFileName() == "")
	{
		return;
	}

	ShaderLoad(File);
}

void EngineLoader::ShaderLoad(EngineFile& _ShaderFile)
{
	std::string ShaderType = _ShaderFile.GetFileName().substr(0, 2);
	EngineString::ToUpper(ShaderType);

	if (ShaderType == "VS")
	{
		VertexShaderLoad(_ShaderFile);
	}
	else if (ShaderType == "PS")
	{
		
	}
}

void EngineLoader::VertexShaderLoad(EngineFile& _ShaderFile)
{
	std::string ShaderType = _ShaderFile.GetFileName().substr(0, 2).data();
	EngineString::ToUpper(ShaderType);

	VertexShaderData Data = EngineDirectX::VertexShaderCompile(_ShaderFile);

	EngineResourceManager::AddLoadedVertexShader(_ShaderFile.GetFileName(), Data.VertexShader);
	EngineResourceManager::AddLoadedInputLayout(_ShaderFile.GetFileName(), Data.InputLayOut);
}

void EngineLoader::LoadAllFBX()
{
	std::vector<EngineFile> AllFBX;
	EnginePath::FindAllFile(".FBX", AllFBX);

	for(EngineFile& File : AllFBX)
	{
		LoadFBX(File);
	}
}

void EngineLoader::AllShaderLoad()
{
	std::vector<EngineFile> AllShader;
	EnginePath::FindAllFile(".hlsl", AllShader);

	for (EngineFile& File : AllShader)
	{
		ShaderLoad(File);
	}
}

void EngineLoader::LoadFBX(EngineFile& _FileData)
{
	Assimp::Importer Importer;
	const aiScene* Scene = Importer.ReadFile(_FileData.GetAbsolutePath(), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	
	if (Scene == nullptr)
	{
		std::cerr << "Error : FileLoad is failed. " << "FileName : " << _FileData.GetFileName() << std::endl;
		return;
	}

	//�޽� �ε�
	if(Scene->HasMeshes() == true)
	{
		std::list<SMeshData> MeshList;

		if (EngineResourceManager::FindMesh(_FileData.GetFileName()) != nullptr)
		{
			std::cerr << "Error : Mesh(Name : " + _FileData.GetFileName() + ") is already loaded." << std::endl;
		}
		else
		{
			Float4x4 Transform;
			Matrix4x4 IdentifyMat = DirectX::XMMatrixIdentity();
			DirectX::XMStoreFloat4x4(&Transform, IdentifyMat);

			ProcessMeshNode(Scene->mRootNode, Scene, Transform, MeshList);
		}

		EngineResourceManager::AddLoadedMesh(_FileData.GetFileName(), std::move(MeshList));
	}

	if (Scene->HasAnimations() == true)
	{
		//�ִϸ��̼� �ε�
	}
}


void EngineLoader::ProcessMeshNode(aiNode* _Node, const aiScene* _Scene, Float4x4 _Transform, std::list<SMeshData>& _MeshList)
{
	Float4x4 Transform;
	ai_real* Temp = &_Node->mTransformation.a1;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Transform.m[j][i] = Temp[i * 4 + j];
		}
	}

	Transform = EngineMath::MulFloat4x4(Transform, _Transform);

	for (UINT i = 0; i < _Node->mNumMeshes; i++)
	{
		aiMesh* Mesh = _Scene->mMeshes[_Node->mMeshes[i]];
		SMaterial Material;

		ProcessMesh(Mesh, _Scene, Transform, _MeshList);
	}

	for (UINT i = 0; i < _Node->mNumChildren; i++)
	{
		ProcessMeshNode(_Node->mChildren[i], _Scene, Transform, _MeshList);
	}
}

void EngineLoader::ProcessMesh(aiMesh* _Mesh, const aiScene* _Scene, Float4x4 _Transform, std::list<SMeshData>& _MeshList)
{
	SMesh NewMesh;
	SMeshData NewMeshData;

	UINT IndicesCount = 0;
	for (UINT i = 0; i < _Mesh->mNumFaces; i++)
	{
		IndicesCount += _Mesh->mFaces[i].mNumIndices;
	}

	NewMesh.Vertices.reserve(_Mesh->mNumVertices);
	NewMesh.Indices.reserve(IndicesCount);

	for (UINT i = 0; i < _Mesh->mNumVertices; i++)
	{
		SVertex NewVertex;

		NewVertex.Position.x = _Mesh->mVertices[i].x;
		NewVertex.Position.y = _Mesh->mVertices[i].y;
		NewVertex.Position.z = _Mesh->mVertices[i].z;

		NewVertex.Normal.x = _Mesh->mNormals[i].x;
		NewVertex.Normal.y = _Mesh->mNormals[i].y;
		NewVertex.Normal.z = _Mesh->mNormals[i].z;

		EngineMath::Normalize(NewVertex.Normal);

		if (_Mesh->mTextureCoords[0] != nullptr)
		{
			NewVertex.Texcoord.x = (float)_Mesh->mTextureCoords[0][i].x;
			NewVertex.Texcoord.y = (float)_Mesh->mTextureCoords[0][i].y;
		}

		NewVertex.Position = EngineMath::Transform(NewVertex.Position, _Transform);
		
		NewMesh.Vertices.push_back(NewVertex);
	}

	for (UINT i = 0; i < _Mesh->mNumFaces; i++)
	{
		aiFace& Face = _Mesh->mFaces[i];

		for (UINT j = 0; j < Face.mNumIndices; j++)
		{
			NewMesh.Indices.push_back(Face.mIndices[j]);
		}
	}

	std::pair<MSComPtr<ID3D11Buffer>, MSComPtr<ID3D11Buffer>> BufferPair
		= EngineDirectX::CreateVertexBufferAndIndexBuffer(NewMesh);

	NewMeshData.VertexBuffer = BufferPair.first;
	NewMeshData.IndexBuffer = BufferPair.second;

	if (_Mesh->mMaterialIndex >= 0)
	{
		aiMaterial* Material = _Scene->mMaterials[_Mesh->mMaterialIndex];

		if (Material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString TexturePath;
			Material->GetTexture(aiTextureType_DIFFUSE, 0, &TexturePath);

			std::string TextureName = EnginePath::GetFileName(TexturePath.C_Str()); 
			
			NewMeshData.Material.DiffuseTexture = TextureName;

			//�ؽ��ķε�
			//if (LoadedTextures.find(TextureName) == LoadedTextures.end())
			//{
			//	LoadTexture(TextureName);
			//}
		}
	}

	_MeshList.push_back(NewMeshData);
}

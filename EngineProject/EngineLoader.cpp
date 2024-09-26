#include "EngineLoader.h"
#include "EnginePath.h"
#include "EngineFile.h"
#include "EngineResourceManager.h"
#include "EngineMath.h"
#include "EngineDirectX.h"
#include "EngineString.h"
#include "EngineVertexShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
		LoadAllPNG();
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

void EngineLoader::LoadShader(std::string_view _FileName)
{
	EngineFile File;
	EnginePath::FindFile(_FileName, File);

	if (File.GetFileName() == "")
	{
		return;
	}

	LoadShader(File);
}

void EngineLoader::LoadShader(EngineFile& _ShaderFile)
{
	std::string ShaderType = _ShaderFile.GetFileName().substr(0, 2);
	EngineString::ToUpper(ShaderType);

	if (ShaderType == "VS")
	{
		LoadVertexShader(_ShaderFile);
	}
	else if (ShaderType == "PS")
	{
		LoadPixelShader(_ShaderFile);
	}
}

void EngineLoader::LoadVertexShader(EngineFile& _ShaderFile)
{
	if (EngineResourceManager::FindShader<EngineVertexShader>(_ShaderFile.GetFileName()) != nullptr)
	{
		std::cerr << "Error : Shader that try to compile is already compiled." << std::endl;
		return;
	}

	std::shared_ptr<EngineVertexShader> LoadedVertexShader = EngineDirectX::CreateVertexShader(_ShaderFile);

	EngineResourceManager::AddLoadedVertexShader(_ShaderFile.GetFileName(), LoadedVertexShader);
}

void EngineLoader::LoadAllDepthStencil()
{
	{
		//
		D3D11_TEXTURE2D_DESC DepthStencilBufferDesc;

		DepthStencilBufferDesc.Width = (UINT)EngineDirectX::GetMainViewPortSize().first;
		DepthStencilBufferDesc.Height = (UINT)EngineDirectX::GetMainViewPortSize().second;

		DepthStencilBufferDesc.MipLevels = 1;
		DepthStencilBufferDesc.ArraySize = 1;

		DepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		DepthStencilBufferDesc.SampleDesc.Count = 1;
		DepthStencilBufferDesc.SampleDesc.Quality = 0;

		DepthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		DepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DepthStencilBufferDesc.CPUAccessFlags = 0;
		DepthStencilBufferDesc.MiscFlags = 0;

		//
		D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
		ZeroMemory(&DepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		DepthStencilDesc.DepthEnable = true;
		DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		DepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

		SDepthStencil DSData = EngineDirectX::CreateDepthStencil(DepthStencilBufferDesc, DepthStencilDesc);

		EngineResourceManager::AddDepthStencil("BaseDepthStencil", DSData);
	}
}

void EngineLoader::LoadAllRasterizer()
{
	{
		MSComPtr<ID3D11RasterizerState> RSState;

		D3D11_RASTERIZER_DESC RD;
		ZeroMemory(&RD, sizeof(D3D11_RASTERIZER_DESC));
		RD.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		RD.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		RD.FrontCounterClockwise = false;

		HRESULT Result = EngineDirectX::GetDevice()->CreateRasterizerState(&RD, &RSState);
		EngineResourceManager::AddRasterizerState("Solid", RSState);
	}
}

void EngineLoader::LoadAllBlendState()
{
	MSComPtr<ID3D11BlendState> BlendState;

	D3D11_BLEND_DESC Desc = { 0, };

	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = false;
	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	EngineDirectX::GetDevice()->CreateBlendState(&Desc, BlendState.GetAddressOf());
	EngineResourceManager::AddBlendState("BaseBlendState", BlendState);
}

void EngineLoader::LoadPixelShader(class EngineFile& _ShaderFile)
{
	const std::string& ShaderName = _ShaderFile.GetFileName();
	if (EngineResourceManager::FindShader<EnginePixelShader>(ShaderName) != nullptr)
	{
		std::cerr << "Error : Shader that try to compile is already compiled." << std::endl;
		return;
	}

	std::shared_ptr<EnginePixelShader> PixelShader = EngineDirectX::CreatePixelShader(_ShaderFile);
	EngineResourceManager::AddLoadedPixelShader(ShaderName, PixelShader);
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

void EngineLoader::LoadAllShader()
{
	std::vector<EngineFile> AllShader;
	EnginePath::FindAllFile(".hlsl", AllShader);

	for (EngineFile& File : AllShader)
	{
		LoadShader(File);
	}
}

void EngineLoader::LoadFBX(std::string_view _FileName)
{
	EngineFile File;
	EnginePath::FindFile(_FileName, File);

	if (File.GetFileName() == "")
	{
		return;
	}

	LoadFBX(File);
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

	//메쉬 로드
	if(Scene->HasMeshes() == true)
	{
		std::shared_ptr<std::list<SMeshData>> MeshList = std::make_shared<std::list<SMeshData>>();

		if (EngineResourceManager::FindMesh(_FileData.GetFileName()) != nullptr)
		{
			std::cerr << "Error : Mesh(Name : " + _FileData.GetFileName() + ") is already loaded." << std::endl;
		}
		else
		{
			SFloat4x4 Transform;
			Transform.Identify();

			ProcessMeshNode(Scene->mRootNode, Scene, Transform, MeshList);
		}

		EngineResourceManager::AddLoadedMesh(_FileData.GetFileName(), MeshList);
	}

	if (Scene->HasAnimations() == true)
	{
		//애니메이션 로드
	}
}

void EngineLoader::LoadAllPNG()
{
	std::vector<EngineFile> AllPNG;
	EnginePath::FindAllFile(".PNG", AllPNG);

	for (EngineFile& File : AllPNG)
	{
		LoadPNG(File);
	}
}

void EngineLoader::LoadPNG(std::string_view _FileName)
{
	EngineFile File;
	EnginePath::FindFile(_FileName, File);

	if (File.GetFileName() == "")
	{
		return;
	}

	LoadPNG(File);
}

void EngineLoader::LoadPNG(EngineFile& _FileData)
{
	int Width = 0;
	int Height = 0;
	int Channels = 0;
	
	unsigned char* LoadedImage = stbi_load(_FileData.GetAbsolutePath().c_str(), &Width, &Height, &Channels, 0);
	if (LoadedImage == nullptr)
	{
		std::cout << "Image Load Failed" << std::endl;
		return;
	}
	
	std::vector<uint8_t> Image;
	
	Image.resize(Width * Height * Channels);
	memcpy(Image.data(), LoadedImage, Image.size() * sizeof(uint8_t));

	STextureData NewTexture = EngineDirectX::CreateTexture(LoadedImage, Width, Height, Channels);
	stbi_image_free(LoadedImage);

	EngineResourceManager::AddLoadedTexture(_FileData.GetFileName(), NewTexture);

	return;
}


void EngineLoader::ProcessMeshNode(aiNode* _Node, const aiScene* _Scene, const SFloat4x4& _Transform, std::shared_ptr<std::list<SMeshData>> _MeshList)
{
	SFloat4x4 Transform;
	ai_real* Temp = &_Node->mTransformation.a1;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Transform.Float4x4.m[j][i] = Temp[i * 4 + j];
		}
	}

	Transform = EngineMath::MulFloat4x4Return(Transform, _Transform);

	for (UINT i = 0; i < _Node->mNumMeshes; i++)
	{
		aiMesh* Mesh = _Scene->mMeshes[_Node->mMeshes[i]];

		ProcessMesh(Mesh, _Scene, Transform, _MeshList);
	}

	for (UINT i = 0; i < _Node->mNumChildren; i++)
	{
		ProcessMeshNode(_Node->mChildren[i], _Scene, Transform, _MeshList);
	}
}

void EngineLoader::ProcessMesh(aiMesh* _Mesh, const aiScene* _Scene, const SFloat4x4& _Transform, std::shared_ptr<std::list<SMeshData>> _MeshList)
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

		NewVertex.Position.X = _Mesh->mVertices[i].x;
		NewVertex.Position.Y = _Mesh->mVertices[i].y;
		NewVertex.Position.Z = _Mesh->mVertices[i].z;

		NewVertex.Normal.X = _Mesh->mNormals[i].x;
		NewVertex.Normal.Y = _Mesh->mNormals[i].y;
		NewVertex.Normal.Z = _Mesh->mNormals[i].z;

		EngineMath::Normalize(NewVertex.Normal);

		if (_Mesh->mTextureCoords[0] != nullptr)
		{
			NewVertex.Texcoord.X = (float)_Mesh->mTextureCoords[0][i].x;
			NewVertex.Texcoord.Y = (float)_Mesh->mTextureCoords[0][i].y;
		}
		
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
	NewMeshData.IndexCount = (UINT)NewMesh.Indices.size();

	if (_Mesh->mMaterialIndex >= 0)
	{
		aiMaterial* Material = _Scene->mMaterials[_Mesh->mMaterialIndex];

		if (Material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString TexturePath;
			Material->GetTexture(aiTextureType_DIFFUSE, 0, &TexturePath);

			std::string TextureName = EnginePath::GetFileName(TexturePath.C_Str()); 
			std::string Extension = EnginePath::GetExtension(TextureName);
			
			EngineString::ToUpper(TextureName);
			EngineString::ToUpper(Extension);

			STextureData FindTexture = EngineResourceManager::FindTexture(TextureName);
			if (FindTexture.Texture2D == nullptr)
			{
				if (Extension == ".PNG")
				{
					LoadPNG(TextureName);
				}
			}
	
			NewMeshData.DiffuseTexture = EngineResourceManager::FindTexture(TextureName);
		}
		else if (Material->GetTextureCount(aiTextureType_NORMALS) > 0)
		{
			aiString TexturePath;
			Material->GetTexture(aiTextureType_NORMALS, 0, &TexturePath);

			std::string TextureName = EnginePath::GetFileName(TexturePath.C_Str());
			std::string Extension = EnginePath::GetExtension(TextureName);

			EngineString::ToUpper(TextureName);
			EngineString::ToUpper(Extension);

			STextureData FindTexture = EngineResourceManager::FindTexture(TextureName);
			if (FindTexture.Texture2D == nullptr)
			{
				if (Extension == ".PNG")
				{
					LoadPNG(TextureName);
				}
			}

			NewMeshData.NormalTexture = EngineResourceManager::FindTexture(TextureName);
		}
	}

	_MeshList->push_back(NewMeshData);
}

void EngineLoader::LoadAllSampler()
{
	{
		std::string SamplerName = "LINEARSAMPLER";
		MSComPtr<ID3D11SamplerState> LinearSampler = EngineDirectX::CreateSamplerState(SamplerName);
		EngineResourceManager::AddSamplerState(SamplerName, LinearSampler);
	}
}
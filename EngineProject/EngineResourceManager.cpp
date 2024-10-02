#include "EngineResourceManager.h"

std::unordered_map<std::string, std::shared_ptr<std::list<SMeshData>>> EngineResourceManager::LoadedMeshes;
std::unordered_map<std::string, std::shared_ptr<EnginePixelShader>> EngineResourceManager::LoadedPixelShaders;
std::unordered_map<std::string, std::shared_ptr<EngineVertexShader>> EngineResourceManager::LoadedVertexShaders;
std::unordered_map<std::string, STextureData> EngineResourceManager::LoadedTexture;
std::unordered_map<std::string, MSComPtr<ID3D11SamplerState>> EngineResourceManager::SamplerStates;
std::unordered_map<std::string, MSComPtr<ID3D11DepthStencilState>> EngineResourceManager::DSStates;
std::unordered_map<std::string, MSComPtr<ID3D11RasterizerState>> EngineResourceManager::RasterizerStates;
std::unordered_map<std::string, MSComPtr<ID3D11BlendState>> EngineResourceManager::BlendStates;

EngineResourceManager::EngineResourceManager()
{
}

EngineResourceManager::~EngineResourceManager()
{
}

const std::shared_ptr<std::list<SMeshData>> EngineResourceManager::FindMesh(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (LoadedMeshes.find(UpperName) == LoadedMeshes.end())
	{
		return nullptr;
	}

	return LoadedMeshes[UpperName];
}

void EngineResourceManager::AddLoadedMesh(const std::string& _Name, std::shared_ptr<std::list<SMeshData>>& _MeshData)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (FindMesh(UpperName) != nullptr)
	{
		EngineDebug::LogErrorMsg(L"같은 이름의 메쉬가 이미 존재합니다.");
		return;
	}

	LoadedMeshes[UpperName] = _MeshData;
}

std::shared_ptr<class EngineVertexShader> EngineResourceManager::FindVertexShader(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (LoadedVertexShaders.find(UpperName) != LoadedVertexShaders.end())
	{
		return LoadedVertexShaders[UpperName];
	}

	return nullptr;
}

std::shared_ptr<class EnginePixelShader> EngineResourceManager::FindPixelShader(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (LoadedPixelShaders.find(UpperName) != LoadedPixelShaders.end())
	{
		return LoadedPixelShaders[UpperName];
	}

	return nullptr;
}

STextureData EngineResourceManager::FindTexture(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (LoadedTexture.find(UpperName) != LoadedTexture.end())
	{
		return LoadedTexture[UpperName];
	}

	return { 0, nullptr, nullptr };
}

void EngineResourceManager::AddLoadedVertexShader(std::string_view _Name, const std::shared_ptr<class EngineVertexShader> _VertexShader)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (FindShader<class EngineVertexShader>(UpperName) != nullptr)
	{
		EngineDebug::LogErrorMsg(L"같은 이름의 버텍스 쉐이더가 이미 존재합니다.");
		return;
	}

	LoadedVertexShaders[UpperName] = _VertexShader;
}

void EngineResourceManager::AddLoadedPixelShader(std::string_view _Name, const std::shared_ptr<EnginePixelShader> _PixelShader)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (FindShader<EnginePixelShader>(UpperName) != nullptr)
	{
		EngineDebug::LogErrorMsg(L"같은 이름의 픽셀 쉐이더가 이미 존재합니다.");
		return;
	}

	LoadedPixelShaders[UpperName] = _PixelShader;
}

void EngineResourceManager::AddLoadedTexture(std::string_view _Name, STextureData _TextureData)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (LoadedTexture.find(UpperName) != LoadedTexture.end())
	{
		EngineDebug::LogErrorMsg(L"같은 이름의 텍스쳐가 이미 존재합니다.");
		return;
	}

	LoadedTexture[UpperName] = _TextureData;
}

MSComPtr<ID3D11SamplerState> EngineResourceManager::FindSampler(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (SamplerStates.find(UpperName) == SamplerStates.end())
	{
		return nullptr;
	}

	return SamplerStates[_Name.data()];
}

void EngineResourceManager::AddSamplerState(std::string_view _Name, MSComPtr<ID3D11SamplerState> _SamplerState)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (SamplerStates.find(UpperName) != SamplerStates.end())
	{
		EngineDebug::LogErrorMsg(L"같은 이름의 샘플러가 이미 존재합니다.");
		return;
	}

	SamplerStates[UpperName] = _SamplerState;
}

const MSComPtr<ID3D11DepthStencilState> EngineResourceManager::FindDSState(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (DSStates.find(UpperName) != DSStates.end())
	{
		return DSStates[UpperName];
	}

	return nullptr;
}

void EngineResourceManager::AddDSState(std::string_view _Name, const MSComPtr<ID3D11DepthStencilState> _DSState)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (DSStates.find(UpperName) != DSStates.end())
	{
		EngineDebug::LogErrorMsg(L"같은 이름의 DSState가 이미 존재합니다.");
		return;
	}

	DSStates[UpperName] = _DSState;
}

const MSComPtr<ID3D11RasterizerState> EngineResourceManager::FindRasterizerState(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (RasterizerStates.find(UpperName) != RasterizerStates.end())
	{
		return RasterizerStates[UpperName];
	}

	return nullptr;
}

void EngineResourceManager::AddRasterizerState(std::string_view _Name, const MSComPtr<ID3D11RasterizerState> _RasterizerState)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (RasterizerStates.find(UpperName) != RasterizerStates.end())
	{
		EngineDebug::LogErrorMsg(L"같은 이름의 RSState가 이미 존재합니다.");
		return;
	}

	RasterizerStates[UpperName] = _RasterizerState;
}

const MSComPtr<ID3D11BlendState> EngineResourceManager::FindBlendState(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (BlendStates.find(UpperName) != BlendStates.end())
	{
		return BlendStates[UpperName];
	}

	return nullptr;
}

void EngineResourceManager::AddBlendState(std::string_view _Name, const MSComPtr<ID3D11BlendState> _BlendState)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (BlendStates.find(UpperName) != BlendStates.end())
	{
		EngineDebug::LogErrorMsg(L"같은 이름의 BlendState가 이미 존재합니다.");
		return;
	}

	BlendStates[UpperName] = _BlendState;
}
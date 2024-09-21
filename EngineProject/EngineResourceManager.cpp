#include "EngineResourceManager.h"

std::unordered_map<std::string, std::list<SMeshData>> EngineResourceManager::LoadedMeshes;
std::unordered_map<std::string, MSComPtr<ID3D11InputLayout>> EngineResourceManager::LoadedInputLayout;
std::unordered_map<std::string, MSComPtr<ID3D11PixelShader>> EngineResourceManager::LoadedPixelShaders;
std::unordered_map<std::string, MSComPtr<ID3D11VertexShader>> EngineResourceManager::LoadedVertexShaders;

EngineResourceManager::EngineResourceManager()
{
}

EngineResourceManager::~EngineResourceManager()
{
}
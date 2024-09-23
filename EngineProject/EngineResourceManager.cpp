#include "EngineResourceManager.h"

std::unordered_map<std::string, std::shared_ptr<std::list<SMeshData>>> EngineResourceManager::LoadedMeshes;
std::unordered_map<std::string, std::shared_ptr<EnginePixelShader>> EngineResourceManager::LoadedPixelShaders;
std::unordered_map<std::string, std::shared_ptr<EngineVertexShader>> EngineResourceManager::LoadedVertexShaders;
std::unordered_map<std::string, STextureData> EngineResourceManager::LoadedTexture;
std::unordered_map<std::string, MSComPtr<ID3D11SamplerState>> EngineResourceManager::SamplerStates;

EngineResourceManager::EngineResourceManager()
{
}

EngineResourceManager::~EngineResourceManager()
{
}
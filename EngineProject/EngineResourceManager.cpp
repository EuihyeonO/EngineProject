#include "EngineResourceManager.h"

std::unordered_map<std::string, std::list<SMeshData>> EngineResourceManager::LoadedMeshes;
std::unordered_map<std::string, std::shared_ptr<EnginePixelShader>> EngineResourceManager::LoadedPixelShaders;
std::unordered_map<std::string, std::shared_ptr<EngineVertexShader>> EngineResourceManager::LoadedVertexShaders;
std::unordered_map<std::string, TextureData> EngineResourceManager::LoadedTexture;

EngineResourceManager::EngineResourceManager()
{
}

EngineResourceManager::~EngineResourceManager()
{
}
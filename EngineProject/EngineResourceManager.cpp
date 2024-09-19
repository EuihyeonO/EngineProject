#include "EngineResourceManager.h"

std::unordered_map<std::string, std::list<SMeshData>> EngineResourceManager::LoadedMeshes;

EngineResourceManager::EngineResourceManager()
{
}

EngineResourceManager::~EngineResourceManager()
{
}
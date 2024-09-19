#include "EngineLoader.h"
#include "EnginePath.h"
#include "ENgineFile.h"

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
		break;
	case DDS:
		break;
	case PNG:
		break;
	default:
		break;
	}
}

void EngineLoader::LoadAllFBX()
{
	std::vector<EngineFile> AllFBX;
	EnginePath::FindAllFile(".FBX", AllFBX);
}
#include "SkeletalMeshComponent.h"
#include "EngineResourceManager.h"
#include "EngineRenderUnit.h"

SkeletalMeshComponent::SkeletalMeshComponent()
{
}

SkeletalMeshComponent::~SkeletalMeshComponent()
{
}

void SkeletalMeshComponent::SetMesh(std::string_view _Name)
{
	std::shared_ptr<std::list<SMeshData>> FindedMesh = EngineResourceManager::FindMesh(_Name);

	if (FindedMesh == nullptr)
	{
		std::string MeshName = _Name.data();
		std::cerr << "Mesh that you try set is not loaded. MeshName : " + MeshName << std::endl;
	
		return;
	}

	if (RenderUnits.size() > 0)
	{
		//±âÁ¸ ·»´õÀ¯´Ö Á¤¸®
	}

	RenderUnits.reserve(FindedMesh->size());

	for(const SMeshData& Mesh : *FindedMesh)
	{
		std::shared_ptr<EngineRenderUnit> NewUnit = std::make_shared<EngineRenderUnit>();
		NewUnit->SetMesh(Mesh);

		RenderUnits.push_back(NewUnit);
	}
}

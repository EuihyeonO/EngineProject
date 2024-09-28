#include "SkeletalMeshComponent.h"
#include "EngineResourceManager.h"
#include "EngineRenderUnit.h"
#include "EngineDebug.h"
#include "EngineString.h"

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
		std::wstring Msg = L"�����ϰ��� �ϴ� �޽��� �ε���� �ʾҽ��ϴ�. MeshName : ";
		Msg += EngineString::StringToWString(_Name.data());
		EngineDebug::LogErrorMsg(Msg);
		return;
	}

	if (RenderUnits.size() > 0)
	{
		//���� �������� ����
	}

	RenderUnits.reserve(FindedMesh->size());

	for(const SMeshData& Mesh : *FindedMesh)
	{
		std::shared_ptr<EngineRenderUnit> NewUnit = std::make_shared<EngineRenderUnit>();
		NewUnit->SetMesh(Mesh);

		RenderUnits.push_back(NewUnit);
	}
}

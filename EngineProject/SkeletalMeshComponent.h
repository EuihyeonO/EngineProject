#pragma once
#include "EngineComponent.h"
#include "EngineRenderUnit.h"
#include "EngineResourceManager.h"
#include "EngineRenderBase.h"

#include <memory>
#include <string_view>
#include <vector>

class SkeletalMeshComponent : public EngineComponent, public EngineRenderBase
{

public:
	SkeletalMeshComponent();
	~SkeletalMeshComponent();

	SkeletalMeshComponent(const SkeletalMeshComponent& _Other) = delete;
	SkeletalMeshComponent(SkeletalMeshComponent&& _Other) noexcept = delete;
	SkeletalMeshComponent& operator=(const SkeletalMeshComponent& _Other) = delete;
	SkeletalMeshComponent& operator=(SkeletalMeshComponent&& _Other) noexcept = delete;

	void SetMesh(std::string_view _Name);
	void OnCreated() override {}
	void OnStart() override {}
	void OnUpdate(float _DeltaTime) override {}
	void OnEnd() override {}

	void OnRender() override
	{
		EngineRenderBase::Render();
	}

	void OnDestroyed() override { EngineRenderBase::OnDestroyed(); };

protected:

private:
};


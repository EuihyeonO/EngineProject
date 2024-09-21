#pragma once
#include "EngineComponent.h"

#include <memory>
#include <string_view>
#include <vector>

class SkeletalMeshComponent : public EngineComponent
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
	void Start() override {}
	void Update() override {}
	void End() override {}
	void OnDestroyed() override {}

protected:

private:
	std::vector<std::shared_ptr<class EngineRenderUnit>> RenderUnits;
};


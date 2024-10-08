#pragma once
#include "DynamicComponent.h"

class CameraComponent final : public DynamicComponent
{

public:
	CameraComponent();
	~CameraComponent();

	CameraComponent(const CameraComponent& _Other) = delete;
	CameraComponent(CameraComponent&& _Other) noexcept = delete;
	CameraComponent& operator=(const CameraComponent& _Other) = delete;
	CameraComponent& operator=(CameraComponent&& _Other) noexcept = delete;

	void OnCreated() override;
	void OnStart() override;
	void OnUpdate(float _DeltaTime) override;
	void OnRender() override;
	void OnEnd() override;
	void OnDestroyed() override;

protected:

private:
	SFloat4x4 ViewMat;
	SFloat4x4 ProjMat;
};


#pragma once
#include "EngineActor.h"
#include "EngineMath.h"
#include "DynamicActor.h"

class CameraActor final : public DynamicActor
{

public:
	CameraActor();
	~CameraActor();

	CameraActor(const CameraActor& _Other) = delete;
	CameraActor(CameraActor&& _Other) noexcept = delete;
	CameraActor& operator=(const CameraActor& _Other) = delete;
	CameraActor& operator=(CameraActor&& _Other) noexcept = delete;

	void OnCreated() override;
	void OnStart() override;
	void OnUpdate(float _DeltaTime) override;
	void OnRender() override;
	void OnDestroyed() override;

protected:

private:
	SFloat4x4 ViewMatrix;
	SFloat4x4 ProjMatrix;
};


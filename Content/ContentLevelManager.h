#pragma once
#include "EngineLevelManager.h"

class ContentLevelManager : public EngineLevelManager
{

public:
	ContentLevelManager();
	~ContentLevelManager();

	ContentLevelManager(const ContentLevelManager& _Other) = delete;
	ContentLevelManager(ContentLevelManager&& _Other) noexcept = delete;
	ContentLevelManager& operator=(const ContentLevelManager& _Other) = delete;
	ContentLevelManager& operator=(ContentLevelManager&& _Other) noexcept = delete;

	void OnUpdate(float _DeltaTime) override;
	void OnStart() override;
	void OnEnd() override;

protected:

private:

};


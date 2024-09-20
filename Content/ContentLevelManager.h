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

	void Start() override;
	void End() override;

protected:

private:

};


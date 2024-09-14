#pragma once
#include "EngineGUIWindow.h"

class TestWindow : public EngineGUIWindow
{
public:

	TestWindow();
	~TestWindow();

	TestWindow(const TestWindow& _Other) = delete;
	TestWindow(TestWindow&& _Other) noexcept = delete;
	TestWindow& operator=(const TestWindow& _Other) = delete;
	TestWindow& operator=(TestWindow&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

protected:
};


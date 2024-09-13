#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <memory>
#include <vector>

class EngineGUIWindow;

template<typename T>
concept GUIWindow = std::is_base_of_v<EngineGUIWindow, T>;

class EngineGUIWindow
{
	friend class Engine;
public:

	EngineGUIWindow();
	~EngineGUIWindow();

	EngineGUIWindow(const EngineGUIWindow& _Other) = delete;
	EngineGUIWindow(EngineGUIWindow&& _Other) noexcept = delete;
	EngineGUIWindow& operator=(const EngineGUIWindow& _Other) = delete;
	EngineGUIWindow& operator=(EngineGUIWindow&& _Other) noexcept = delete;

	virtual void Start();
	virtual void Update();


	template<typename Window> requires GUIWindow<Window>
	static std::shared_ptr<EngineGUIWindow> CreateGUIWIndow()
	{
		std::shared_ptr<Window> NewWindow = std::make_shared<Window>();
		NewWindow->Start();

		GUIWindows.push_back(NewWindow);
		return NewWindow;
	}

private:
	static void GUIStart();
	static void GUIEnd();

	static void GUIUpdate()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		for (std::shared_ptr<EngineGUIWindow> Window : GUIWindows)
		{
			Window->Update();
		}
	}

	static void GUIRender()
	{
		//ImGui::Render();
		//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

private:
	static std::vector<std::shared_ptr<EngineGUIWindow>> GUIWindows;

};


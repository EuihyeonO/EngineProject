#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

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
	static std::shared_ptr<EngineGUIWindow> CreateGUIWIndow(const std::string _GUIName)
	{
		if (GUIWindows.find(_GUIName) != GUIWindows.end())
		{
			std::cerr << _GUIName << " is already created" << std::endl;
			return nullptr;
		}

		std::shared_ptr<Window> NewWindow = std::make_shared<Window>();
		NewWindow->Start();
		NewWindow->Name = _GUIName;

		GUIWindows.insert({ _GUIName, NewWindow });
		return NewWindow;
	}

	const std::string& GetName()
	{
		return Name;
	}

	void SetWindowSize(ImVec2 _Size)
	{
		WindowSize = _Size;
	}

	void SetWindowPos(ImVec2 _Pos)
	{
		WindowPos = _Pos;
	}

private:
	static void GUIStart();
	static void GUIEnd();

	static void GUIUpdate()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		for (std::pair<std::string, std::shared_ptr<EngineGUIWindow>> GUIData : GUIWindows)
		{
			GUIData.second->Update();
		}
	}

	static void GUIRender()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

protected:
	ImVec2 WindowSize = { 0, 0 };
	ImVec2 WindowPos = { 0, 0 };

private:
	std::string Name = "";

private:
	static std::unordered_map<std::string, std::shared_ptr<EngineGUIWindow>> GUIWindows;
};


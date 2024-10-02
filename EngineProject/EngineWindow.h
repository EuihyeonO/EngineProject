#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "BaseHeader.h"

class EngineWindow
{
	friend class Engine;
public:
	static EngineWindow* GetInstance()
	{
		static EngineWindow Instance;
		return &Instance;
	}

	static std::pair<int, int> GetWindowSize()
	{
		return { WindowWidth, WindowHeight };
	}

	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:
	static HWND GetHWND()
	{
		return GetInstance()->hWnd;
	}

protected:

private:
	EngineWindow();
	~EngineWindow();

private:
	static void Start(HINSTANCE hInstance, int nCmdShow, std::function<void(float)> _LoopFunc);
	static void Loop(float _DeltaTime);
	static void End();

	ATOM RegisterWindow();
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

private:
	std::function<void(float)> LoopFunc = nullptr;

	static bool isWindowUpdate;

	HWND hWnd;
	HINSTANCE HInst;
	std::wstring TitleName = L"MyEngine";
	std::wstring WindowClass = L"MainWindow";

	static int WindowWidth;
	static int WindowHeight;
};


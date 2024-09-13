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

	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:
	HWND GetHWND()
	{
		return hWnd;
	}

protected:

private:
	EngineWindow();
	~EngineWindow();

private:
	static void Start(HINSTANCE hInstance, int nCmdShow);
	static void Loop(std::function<void()> _LoopFunc);
	static void End();

	ATOM RegisterWindow();
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

	static std::pair<int, int> GetWindowSize()
	{
		return { WindowWidth, WindowHeight };
	}

private:
	static bool isWindowUpdate;

	HWND hWnd;
	HINSTANCE HInst;
	std::wstring TitleName = L"MyEngine";
	std::wstring WindowClass = L"MainWindow";

	static int WindowWidth;
	static int WindowHeight;
};


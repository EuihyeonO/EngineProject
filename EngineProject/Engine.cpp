#include "Engine.h"
#include "EngineWindow.h"
#include "EngineGUIWindow.h"
#include "EngineDirectX.h"
#include "TestWindow.h"

bool Engine::isEngineOn = false;
std::shared_ptr<EngineLevelManager> Engine::LevelManager = nullptr;

Engine::Engine()
{
}

Engine::~Engine()
{
}

#include "EngineMath.h"

void Engine::EngineStart(HINSTANCE hInstance, int nCmdShow)
{
	EngineWindow::Start(hInstance, nCmdShow);
	EngineDirectX::Start();
	EngineGUIWindow::GUIStart();

	LevelManager->Start();
	CreateEngineGUI();
}

void Engine::EngineLoop()
{
	std::function<void()> Func = std::bind(&Engine::Loop, GetInstance());
	EngineWindow::Loop(Func);
}

void Engine::Update()
{
	LevelManager->Update();
}

void Engine::Render()
{
	LevelManager->Render();
	EngineGUIWindow::GUIUpdate();

	//GUI Renderring	
	EngineGUIWindow::GUIRender();

	//Present
	EngineDirectX::GetInstance()->GetSwapChain()->Present(1, 0);
}

void Engine::Loop()
{
	Update();
	Render();
}

void Engine::CreateEngineGUI()
{
	std::shared_ptr<EngineGUIWindow> LeftGUI = TestWindow::CreateGUIWindow<TestWindow>("LeftGUI");
	LeftGUI->SetWindowPos({ 0, 0 });
	LeftGUI->SetWindowSize({ 250, 900 });
	
	std::shared_ptr<EngineGUIWindow> DownGUI = TestWindow::CreateGUIWindow<TestWindow>("DownGUI");
	DownGUI->SetWindowPos({ 250, 650 });
	DownGUI->SetWindowSize({ 1350, 250 });
	
	std::shared_ptr<EngineGUIWindow> RightGUI = TestWindow::CreateGUIWindow<TestWindow>("RightGUI");
	RightGUI->SetWindowPos({ 1350, 0 });
	RightGUI->SetWindowSize({ 250, 650 });
}

void Engine::EngineEnd()
{
	EngineGUIWindow::GUIEnd();
	LevelManager->Destroy();
	EngineDirectX::End();
}


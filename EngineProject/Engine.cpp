#include "Engine.h"
#include "EngineWindow.h"
#include "EngineGUIWindow.h"
#include "EngineDirectX.h"
#include "TestWindow.h"
#include "EngineMath.h"
#include "EngineRenderTarget.h"

bool Engine::isEngineOn = false;
std::shared_ptr<EngineLevelManager> Engine::LevelManager = nullptr;
std::pair<float, float> Engine::ViewPortSize = { 1100.0f, 650.0f };

Engine::Engine()
{
}

Engine::~Engine()
{
}

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
}

void Engine::Render()
{
	LevelManager->Render();

	EngineDirectX::GetInstance()->ClearMainRenderTarget();
	EngineDirectX::SetRenderTarget(EngineDirectX::GetMainRTV(), nullptr);

	//GUI Renderring	
	if (LevelManager->CurrentLevel != nullptr)
	{
		EngineGUIWindow::GUIUpdate(LevelManager->CurrentLevel->GetRenderTarget()->GetSRV());
		EngineGUIWindow::GUIRender();
	}

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
	std::shared_ptr<EngineGUIWindow> LeftGUI = TestWindow::CreateGUIWindow<TestWindow>("Hierachy");
	LeftGUI->SetWindowPos({ 0, 0 });
	LeftGUI->SetWindowSize({ 250, 900 });
	
	std::shared_ptr<EngineGUIWindow> DownGUI = TestWindow::CreateGUIWindow<TestWindow>("Files");
	DownGUI->SetWindowPos({ 250, 650 });
	DownGUI->SetWindowSize({ 1350, 250 });
	
	std::shared_ptr<EngineGUIWindow> RightGUI = TestWindow::CreateGUIWindow<TestWindow>("Details");
	RightGUI->SetWindowPos({ 1350, 0 });
	RightGUI->SetWindowSize({ 250, 650 });

	std::shared_ptr<EngineGUIWindow> ViewPortGUI = TestWindow::CreateGUIWindow<TestWindow>("ViewPort");
	ViewPortGUI->SetWindowPos({ 250, 0 });
	ViewPortGUI->SetWindowSize({1100, 650});
}

void Engine::EngineEnd()
{
	EngineGUIWindow::GUIEnd();
	LevelManager->Destroy();
	EngineDirectX::End();
}


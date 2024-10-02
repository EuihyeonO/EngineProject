#include "Engine.h"
#include "EngineWindow.h"
#include "EngineGUIWindow.h"
#include "EngineDirectX.h"
#include "TestWindow.h"
#include "EngineMath.h"
#include "EngineRenderTarget.h"
#include "EngineTimer.h"

bool Engine::isEngineOn = false;
std::shared_ptr<EngineLevelManager> Engine::LevelManager = nullptr;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::EngineStart(HINSTANCE hInstance, int nCmdShow)
{
	EngineWindow::Start(hInstance, nCmdShow, std::bind(&Engine::Loop, GetInstance(), std::placeholders::_1));
	EngineDirectX::Start();
	EngineGUIWindow::GUIStart();

	LevelManager->Start();
	CreateEngineGUI();
}

void Engine::EngineLoop()
{
	EngineTimer::DeltaTimeUpdate();
	EngineWindow::Loop(EngineTimer::GetDeltaTime());
}

void Engine::Update(float _DeltaTime)
{
	LevelManager->Update(_DeltaTime);
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

void Engine::Loop(float _DeltaTime)
{
	Update(_DeltaTime);
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


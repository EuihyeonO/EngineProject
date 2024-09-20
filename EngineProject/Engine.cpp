#include "Engine.h"
#include "EngineWindow.h"
#include "EngineGUIWindow.h"
#include "EngineDirectX.h"
#include "TestWindow.h"

bool Engine::isEngineOn = false;


Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::PlayEngine(HINSTANCE hInstance, int nCmdShow)
{
	//혹시나 main함수 말고 다른데서 호출하면 안된다
	if (isEngineOn == true)
	{
		std::cerr << "Why do you call \"PlayEngine\"?" << std::endl;
		return;
	}

	isEngineOn = true;

	GetInstance()->EngineStart(hInstance, nCmdShow);
	GetInstance()->EngineLoop();
	GetInstance()->EngineEnd();
}

void Engine::EngineStart(HINSTANCE hInstance, int nCmdShow)
{
	EngineWindow::Start(hInstance, nCmdShow);
	EngineDirectX::Start();
	EngineGUIWindow::GUIStart();
	
	CreateEngineGUI();
}

void Engine::EngineLoop()
{
	std::function<void()> Func = std::bind(&Engine::Loop, GetInstance());
	EngineWindow::Loop(Func);
}

void Engine::Update()
{
	EngineGUIWindow::GUIUpdate();
}

void Engine::Render()
{
	const float clear_color_with_alpha[4] = { 0.0, 1.0, 1.0, 1.0 };

	//렌더타겟 세팅
	EngineDirectX::GetInstance()->GetDeviceContext()->OMSetRenderTargets(1, EngineDirectX::GetInstance()->GetMainRTV().GetAddressOf(), nullptr);
	EngineDirectX::GetInstance()->GetDeviceContext()->ClearRenderTargetView(EngineDirectX::GetInstance()->GetMainRTV().Get(), clear_color_with_alpha);

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
}


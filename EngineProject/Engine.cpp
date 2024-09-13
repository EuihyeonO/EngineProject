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
	//Ȥ�ó� main�Լ� ���� �ٸ����� ȣ���ϸ� �ȵȴ�
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

	TestWindow::CreateGUIWIndow<TestWindow>();
}

void Engine::EngineLoop()
{
	std::function<void()> Func = std::bind(&Engine::Update, GetInstance());
	EngineWindow::Loop(Func);
}

void Engine::Update()
{
	//EngineGUIWindow::GUIUpdate();
	
	//Render();
	//EngineGUIWindow::GUIRender();
	//EngineDirectX::GetInstance()->GetSwapChain()->Present(1, 0);
}

void Engine::Render()
{
	const float clear_color_with_alpha[4] = { 1.0, 1.0, 1.0, 1.0 };
	
	//����
	EngineDirectX::GetInstance()->GetDeviceContext()->OMSetRenderTargets(1, EngineDirectX::GetInstance()->GetRenderTarget(), nullptr);
	EngineDirectX::GetInstance()->GetDeviceContext()->ClearRenderTargetView(EngineDirectX::GetInstance()->GetRenderT(), clear_color_with_alpha);
}

void Engine::EngineEnd()
{

}


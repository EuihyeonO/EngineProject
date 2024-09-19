#include "EngineGUIWindow.h"
#include "EngineWindow.h"
#include "EngineDirectX.h"



#include <d3d11.h>

std::unordered_map<std::string, std::shared_ptr<EngineGUIWindow>> EngineGUIWindow::GUIWindows;

EngineGUIWindow::EngineGUIWindow()
{
}

EngineGUIWindow::~EngineGUIWindow()
{
}

void EngineGUIWindow::Start()
{
}

void EngineGUIWindow::Update()
{
}

void EngineGUIWindow::GUIStart()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    ImGui_ImplWin32_Init(EngineWindow::GetInstance()->GetHWND());
    ImGui_ImplDX11_Init(EngineDirectX::GetInstance()->GetDevice().Get(), EngineDirectX::GetInstance()->GetDeviceContext().Get());
}

void EngineGUIWindow::GUIEnd()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

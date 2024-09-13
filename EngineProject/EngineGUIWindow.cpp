#include "EngineGUIWindow.h"
#include "EngineWindow.h"
#include "EngineDirectX.h"



#include <d3d11.h>

std::vector<std::shared_ptr<EngineGUIWindow>> EngineGUIWindow::GUIWindows;

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
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(EngineWindow::GetInstance()->GetHWND());
    ImGui_ImplDX11_Init(EngineDirectX::GetInstance()->GetDevice(), EngineDirectX::GetInstance()->GetDeviceContext());
}

void EngineGUIWindow::GUIEnd()
{

}

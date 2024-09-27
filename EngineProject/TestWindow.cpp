#include "TestWindow.h"
#include "EngineDirectX.h"
#include "DirectXHeader.h"

TestWindow::TestWindow()
{
}

TestWindow::~TestWindow()
{
}

void TestWindow::Start()
{
    ImGuiStyle& Style = ImGui::GetStyle();

    Style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    Style.Colors[ImGuiCol_WindowBg] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    Style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void TestWindow::Update(MSComPtr<ID3D11ShaderResourceView> _SRV)
{
    ImGui::Begin(GetName().c_str());

    ImGui::SetWindowPos(WindowPos);
    ImGui::SetWindowSize(WindowSize);

    if (_SRV != nullptr && GetName() == "ViewPort")
    {
        ImGui::Image((ImTextureID)_SRV.Get(), ImGui::GetContentRegionAvail());
    }

    ImGui::End();
}

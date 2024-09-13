#include "TestWindow.h"

TestWindow::TestWindow()
{
}

TestWindow::~TestWindow()
{
}

void TestWindow::Start()
{
    //ImGuiStyle& Style = ImGui::GetStyle();
    //Style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    //Style.Colors[ImGuiCol_WindowBg] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
}

void TestWindow::Update()
{
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
    ImGui::SetWindowPos({ 0, 0 });
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::End();
}

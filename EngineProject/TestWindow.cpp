#include "TestWindow.h"

TestWindow::TestWindow()
{
}

TestWindow::~TestWindow()
{
}

void TestWindow::Update()
{
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::End();
}

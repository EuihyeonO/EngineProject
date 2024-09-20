#include "Engine.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#pragma comment(lib, "EngineProject.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
                      _In_opt_ HINSTANCE hPrevInstance, 
                      _In_ LPWSTR lpCmdLine, 
                      _In_ int nCmdShow)
{
    Engine::PlayEngine(hInstance, nCmdShow);
    return 0;
}

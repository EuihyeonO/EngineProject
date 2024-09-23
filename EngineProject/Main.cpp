#pragma comment(lib, "EngineProject.lib")

#include "Engine.h"
#include "ContentLevelManager.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
                      _In_opt_ HINSTANCE hPrevInstance, 
                      _In_ LPWSTR lpCmdLine, 
                      _In_ int nCmdShow)
{
    std::locale::global(std::locale("korean"));
    Engine::PlayEngine<ContentLevelManager>(hInstance, nCmdShow);
    return 0;
}

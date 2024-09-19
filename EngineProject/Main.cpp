#include "Engine.h"
#include "EngineLoader.h"
#include "EngineFile.h"
#include "EnginePath.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
                      _In_opt_ HINSTANCE hPrevInstance, 
                      _In_ LPWSTR lpCmdLine, 
                      _In_ int nCmdShow)
{
    EngineFile File;
    EnginePath::FindFile("zeldaPosed001.fbx", File);
    EngineLoader::LoadFBX(File);

    Engine::PlayEngine(hInstance, nCmdShow);
    return 0;
}

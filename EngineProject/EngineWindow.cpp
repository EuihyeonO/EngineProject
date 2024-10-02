#include "EngineWindow.h"
#include "framework.h"
#include "EngineGUIWindow.h"

bool EngineWindow::isWindowUpdate = true;

int EngineWindow::WindowWidth = 1600;
int EngineWindow::WindowHeight = 900;

EngineWindow::EngineWindow()
{
}

EngineWindow::~EngineWindow()
{
}

void EngineWindow::Start(HINSTANCE hInstance, int nCmdShow, std::function<void(float)> _LoopFunc)
{
	GetInstance()->RegisterWindow();
    GetInstance()->InitInstance(hInstance, nCmdShow); 
    GetInstance()->LoopFunc = _LoopFunc;
}

void EngineWindow::Loop(float _DeltaTime)
{
    EngineWindow* Window = GetInstance();

    HACCEL hAccelTable = LoadAccelerators(Window->HInst, MAKEINTRESOURCE(IDC_ENGINEPROJECT));
    MSG msg;

    while (isWindowUpdate)
    {
        if (Window->LoopFunc != nullptr)
        {
            Window->LoopFunc(_DeltaTime);
        }

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK EngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(GetInstance()->HInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            isWindowUpdate = false;
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        isWindowUpdate = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR EngineWindow::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

ATOM EngineWindow::RegisterWindow()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = HInst;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ENGINEPROJECT);
    wcex.lpszClassName = WindowClass.c_str();
    wcex.hIcon = NULL;
    wcex.hIconSm = NULL;

    return RegisterClassExW(&wcex);
}

BOOL EngineWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(WindowClass.c_str(), TitleName.c_str(), WS_OVERLAPPEDWINDOW,
        0, 0, WindowWidth, WindowHeight, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    GetInstance()->hWnd = hWnd;
    return TRUE;
}
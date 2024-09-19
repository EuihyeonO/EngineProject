#include "EngineDirectX.h"
#include "EngineWindow.h"
#include "EngineDebug.h"

#include <iostream>

EngineDirectX::EngineDirectX()
{
}

EngineDirectX::~EngineDirectX()
{
}

void EngineDirectX::CreateDevice()
{
    //D3D_DRIVER_TYPE_HARDWARE -> GPU -> ���� ���� (���� ������)
    //D3D_DRIVER_TYPE_REFERENCE -> CPU -> ��������, ��Ȯ�� ���� -> �ַ� �׷��� �׽�Ʈ������ ���
    //D3D_DRIVER_TYPE_SOFTWARE -> CPU -> REFERENCE�� ����������, Ŀ���� ����Ʈ��� ����ϰ� ���� �� 
    
    const D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;

    //����� ����� ����� ���ΰ� (����� ������, ���� ���� �� ���� ���� D3D11_CREATE_DEVICE_DEBUG ���� ���� �� �ϴ�.)
    UINT CreateDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    //���̷�ƮX�� ���� ��� (���� ��ǻ�Ϳ� ������ ���ٸ�, �� ���� �������� Device ������ �õ�)
    const D3D_FEATURE_LEVEL featureLevels[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_9_3 };

    //������ Device�� ���̷�ƮX ������ ����(���� 0�� �ε��� ���� ������ �����߰� 1�� �ε��� ���� ������ �����ߴٸ�, 1�� �ε��� ������ ��� ��)
    D3D_FEATURE_LEVEL featureLevel;
    
    HRESULT Result = D3D11CreateDevice(
        nullptr,                  // nullptr�̸� �⺻ ����͸� ���
        DriverType,               // � ����̹��� ����Ͽ� Device�� ���� ���ΰ�
        0,                        // ����Ʈ���� ����̹��� ����� ���̶��, �ش� ����Ʈ��� �˾ƾ� �ϱ� ������
        CreateDeviceFlags,        // �÷���
        featureLevels,            // ���̷�ƮX ���� ��� �迭
        ARRAYSIZE(featureLevels), // ���� �迭�� ������
        D3D11_SDK_VERSION,        // ������ D3D11_SDK_VERSION ����� ���ֳ�
        &Device,                  // ������ ����̽��� ����
        &featureLevel,            // ������ ����̽��� DirectX ������ ����
        &DeviceContext            // ������ ����̽��� Context�� ����
    );
    
    if (featureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        std::cerr << "Created Device Version is not D3D11" << std::endl;
        return;
    }

    if (Result != S_OK)
    {
        _com_error Error(Result);
        LPCTSTR ErrMsg = Error.ErrorMessage();
        
        std::wcerr << L"Error : " << ErrMsg << std::endl;
        return;
    }
}

void EngineDirectX::CreateSwapChain()
{
    HRESULT Result = S_OK;

    MSComPtr<IDXGIDevice> DXGIDevice;
    Result = Device.As(&DXGIDevice);

    MSComPtr<IDXGIAdapter> DXGIAdapter;
    Result = DXGIDevice->GetAdapter(&DXGIAdapter);

    MSComPtr<IDXGIFactory> DXGIFactory;
    Result = DXGIAdapter->GetParent(IID_PPV_ARGS(&DXGIFactory));

    SwapChain.Reset();
 
    DXGI_SWAP_CHAIN_DESC SD;
    ZeroMemory(&SD, sizeof(SD));
    SD.BufferDesc.Width = (UINT)0;                                               // ����� ������ (�ʺ�)
    SD.BufferDesc.Height = (UINT)0;                                              // ����� ������ (����)
    SD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                           // ���� ����
    SD.BufferCount = 2;                                                          // ����� ����
    SD.BufferDesc.RefreshRate.Numerator = 60;                                    // ���ŷ� (����)
    SD.BufferDesc.RefreshRate.Denominator = 1;                                   // ���ŷ� (�и�)
    SD.BufferUsage = DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_RENDER_TARGET_OUTPUT;  // ����ü���� ��� �� ���ΰ�
    SD.OutputWindow = EngineWindow::GetHWND();                                   // ����ü���� ���� ������
    SD.Windowed = TRUE;                                                          // â���, ��ü��� 
    SD.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                           // â���, ��ü��� ��ȯ�� ����� ���ΰ�
    SD.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    SD.SampleDesc.Count = 1;
    SD.SampleDesc.Quality = 0;

    Result = DXGIFactory->CreateSwapChain(Device.Get(), &SD, SwapChain.GetAddressOf());
    EngineDebug::CheckResult(Result);

    //������� ����Ÿ�� ��, ���̴� ���ҽ� �� ����
    Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBuffer;
    SwapChain->GetBuffer(0, IID_PPV_ARGS(BackBuffer.GetAddressOf()));

    if (BackBuffer != nullptr)
    {
        Result = Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, MainRTV.GetAddressOf());
        EngineDebug::CheckResult(Result);

        Result = Device->CreateShaderResourceView(BackBuffer.Get(), nullptr, MainSRV.GetAddressOf());
        EngineDebug::CheckResult(Result);
    }
    else
    {
        std::cout << "CreateRenderTargetView() failed!" << std::endl;
    }
}

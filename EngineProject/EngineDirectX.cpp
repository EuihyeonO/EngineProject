#include "EngineDirectX.h"
#include "EngineWindow.h"
#include "EngineDebug.h"
#include "ResourceStruct.h"

#include <iostream>

EngineDirectX::EngineDirectX()
{
}

EngineDirectX::~EngineDirectX()
{
}

std::pair<MSComPtr<ID3D11Buffer>, MSComPtr<ID3D11Buffer>> EngineDirectX::CreateVertexBufferAndIndexBuffer(const SMesh& _Mesh)
{
    const std::vector<SVertex>& Vertices = _Mesh.Vertices;
    const std::vector<uint32_t>& Indices = _Mesh.Indices;
    
    MSComPtr<ID3D11Buffer> VertexBuffer;
    MSComPtr<ID3D11Buffer> IndexBuffer;

    //VertexBuffer
    {
        D3D11_BUFFER_DESC BufferDesc = { 0, };
        ZeroMemory(&BufferDesc, sizeof(BufferDesc));

        BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        BufferDesc.ByteWidth = UINT(sizeof(SVertex) * Vertices.size());
        BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        BufferDesc.CPUAccessFlags = 0;
        BufferDesc.StructureByteStride = sizeof(SVertex);

        D3D11_SUBRESOURCE_DATA VertexBufferData = { 0, };
        VertexBufferData.pSysMem = _Mesh.Vertices.data();
        VertexBufferData.SysMemPitch = 0;
        VertexBufferData.SysMemSlicePitch = 0;

        const HRESULT Result = GetInstance()->GetDevice()->CreateBuffer(&BufferDesc, &VertexBufferData, VertexBuffer.GetAddressOf());
        EngineDebug::CheckResult(Result);
    }

    //IndexBuffer
    {
        D3D11_BUFFER_DESC BufferDesc = { 0, };
        BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        BufferDesc.ByteWidth = UINT(sizeof(uint32_t) * Indices.size());
        BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        BufferDesc.CPUAccessFlags = 0;
        BufferDesc.StructureByteStride = sizeof(uint32_t);

        D3D11_SUBRESOURCE_DATA IndexBufferData = { 0 };
        IndexBufferData.pSysMem = Indices.data();
        IndexBufferData.SysMemPitch = 0;
        IndexBufferData.SysMemSlicePitch = 0;

        HRESULT Result = GetInstance()->GetDevice()->CreateBuffer(&BufferDesc, &IndexBufferData, IndexBuffer.GetAddressOf());
        EngineDebug::CheckResult(Result);
    }

    return { VertexBuffer, IndexBuffer };
}

void EngineDirectX::CreateDevice()
{
    //D3D_DRIVER_TYPE_HARDWARE -> GPU -> 가장 고성능 (가장 빠르다)
    //D3D_DRIVER_TYPE_REFERENCE -> CPU -> 느리지만, 정확성 높다 -> 주로 그래픽 테스트용으로 사용
    //D3D_DRIVER_TYPE_SOFTWARE -> CPU -> REFERENCE와 유사하지만, 커스텀 소프트웨어를 사용하고 싶을 때 
    
    const D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;

    //디버그 기능을 사용할 것인가 (목록이 많은데, 현재 내가 쓸 만한 것은 D3D11_CREATE_DEVICE_DEBUG 말곤 없는 듯 하다.)
    UINT CreateDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    //다이렉트X의 버전 목록 (만약 컴퓨터에 버전이 없다면, 더 낮은 버전으로 Device 생성을 시도)
    const D3D_FEATURE_LEVEL featureLevels[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_9_3 };

    //생성된 Device의 다이렉트X 버전을 저장(만약 0번 인덱스 버전 생성이 실패했고 1번 인덱스 버전 생성이 성공했다면, 1번 인덱스 버전이 담길 것)
    D3D_FEATURE_LEVEL featureLevel;
    
    HRESULT Result = D3D11CreateDevice(
        nullptr,                  // nullptr이면 기본 어댑터를 사용
        DriverType,               // 어떤 드라이버를 사용하여 Device를 만들 것인가
        0,                        // 소프트웨어 드라이버를 사용할 것이라면, 해당 소프트웨어를 알아야 하기 때문에
        CreateDeviceFlags,        // 플래그
        featureLevels,            // 다이렉트X 버전 목록 배열
        ARRAYSIZE(featureLevels), // 위의 배열의 사이즈
        D3D11_SDK_VERSION,        // 무조건 D3D11_SDK_VERSION 쓰라고 써있네
        &Device,                  // 생성된 디바이스를 저장
        &featureLevel,            // 생성된 디바이스의 DirectX 버전을 저장
        &DeviceContext            // 생성된 디바이스의 Context를 저장
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
    SD.BufferDesc.Width = (UINT)0;                                               // 백버퍼 사이즈 (너비)
    SD.BufferDesc.Height = (UINT)0;                                              // 백버퍼 사이즈 (높이)
    SD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                           // 색상 포맷
    SD.BufferCount = 2;                                                          // 백버퍼 개수
    SD.BufferDesc.RefreshRate.Numerator = 60;                                    // 갱신률 (분자)
    SD.BufferDesc.RefreshRate.Denominator = 1;                                   // 갱신률 (분모)
    SD.BufferUsage = DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_RENDER_TARGET_OUTPUT;  // 스왑체인을 어떻게 쓸 것인가
    SD.OutputWindow = EngineWindow::GetHWND();                                   // 스왑체인이 사용될 윈도우
    SD.Windowed = TRUE;                                                          // 창모드, 전체모드 
    SD.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                           // 창모드, 전체모드 전환을 허용할 것인가
    SD.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    SD.SampleDesc.Count = 1;
    SD.SampleDesc.Quality = 0;

    Result = DXGIFactory->CreateSwapChain(Device.Get(), &SD, SwapChain.GetAddressOf());
    EngineDebug::CheckResult(Result);

    //백버퍼의 렌더타겟 뷰, 쉐이더 리소스 뷰 생성
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

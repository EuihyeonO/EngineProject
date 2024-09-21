#include "EngineDirectX.h"
#include "EngineWindow.h"
#include "EngineDebug.h"
#include "ResourceHeader.h"
#include "EngineFile.h"
#include "EnginePath.h"
#include "EngineString.h"
#include "EngineResourceManager.h"

#include <d3dcompiler.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

EngineDirectX::EngineDirectX()
{
}

EngineDirectX::~EngineDirectX()
{
}

VertexShaderData EngineDirectX::VertexShaderCompile(const EngineFile& _Shader)
{
	if (EngineResourceManager::FindShader<ID3D11VertexShader>(_Shader.GetFileName()) != nullptr)
	{
		std::cerr << "Error : Shader that try to compile is already compiled." << std::endl;
		return { nullptr,nullptr };
	}

	MSComPtr<ID3DBlob> ShaderBlob;
	MSComPtr<ID3DBlob> ErrorBlob;

	UINT CompileFlag = 0;

#if defined(DEBUG) || defined(_DEBUG)
	CompileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	std::wstring WShaderPath = EngineString::StringToWString(_Shader.GetAbsolutePath());
	HRESULT Result = D3DCompileFromFile(WShaderPath.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_5_0", CompileFlag, 0, &ShaderBlob, &ErrorBlob);
	
	if (Result != S_OK)
	{
		// 파일이 없을 경우
		if ((Result & D3D11_ERROR_FILE_NOT_FOUND) != 0)
		{
			std::wcout << "Error : Shader that try to compile is not found. File Path+ Name : " << WShaderPath << std::endl;
		}

		// 에러 메시지가 있으면 출력
		if (ErrorBlob != nullptr)
		{
			std::cout << "Shader Compile Error\n" << (char*)ErrorBlob->GetBufferPointer() << std::endl;
		}

		return { nullptr,nullptr };
	}

	MSComPtr<ID3D11VertexShader> NewVertextShader;
	
	Result = GetDevice()->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), NULL, &NewVertextShader);
	if (Result != S_OK)
	{
		std::cout << "Error : Vertexbuffer Creation failed." << std::endl;
		return { nullptr,nullptr };
	}

	MSComPtr<ID3D11InputLayout> InputLayOut = CreateInputLayOut(_Shader, ShaderBlob);

	return { NewVertextShader, InputLayOut };
}

MSComPtr<ID3D11InputLayout> EngineDirectX::CreateInputLayOut(const EngineFile& _ShaderFile, MSComPtr<ID3DBlob> _ShaderBlob)
{
	std::string Str = _ShaderFile.GetFileString();
	EngineString::ToUpper(Str);

	std::string FindStr = "STRUCT VS_INPUT";
	size_t Index = Str.find(FindStr);
	Index += FindStr.size();

	size_t MinIndex = 0;
	size_t MaxIndex = 0;

	for (size_t i = Index; i < Str.size(); i++)
	{
		if (Str[i] == '{')
		{
			MinIndex = i;
		}
		else if (Str[i] == '}')
		{
			MaxIndex = i;
			break;
		}
	}

	std::vector<std::pair<size_t, std::string>> InputLayOutDatas;

	size_t PositionIndex = Str.find("POSITION");
	if (PositionIndex != std::string::npos && PositionIndex >= MinIndex && PositionIndex <= MaxIndex)
	{
		InputLayOutDatas.push_back({ PositionIndex, "POSITION" });
	}

	size_t NormalIndex = Str.find("NORMAL");
	if (NormalIndex != std::string::npos && NormalIndex >= MinIndex && NormalIndex <= MaxIndex)
	{
		InputLayOutDatas.push_back({ NormalIndex, "NORMAL" });
	}

	size_t TexcoordIndex = Str.find("TEXCOORD");
	if (TexcoordIndex != std::string::npos && TexcoordIndex >= MinIndex && TexcoordIndex <= MaxIndex)
	{
		InputLayOutDatas.push_back({ TexcoordIndex, "TEXCOORD" });
	}

	std::sort(InputLayOutDatas.begin(), InputLayOutDatas.end());

	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements(InputLayOutDatas.size());
	
	for (int i = 0; i < InputLayOutDatas.size(); i++)
	{
		std::string Semantics = InputLayOutDatas[i].second;
		
		if (Semantics == "POSITION")
		{
			inputElements[i] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, VertexOffset::POSITION, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		}
		else if (Semantics == "NORMAL")
		{
			inputElements[i] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, VertexOffset::NORMAL, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		}
		else if (Semantics == "TEXCOORD")
		{
			inputElements[i] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, VertexOffset::TEXCOORED, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		}
	}

	MSComPtr<ID3D11InputLayout> InputLayOut;

	HRESULT Result =
		GetInstance()->GetDevice()->CreateInputLayout(inputElements.data(), UINT(inputElements.size()),
			_ShaderBlob->GetBufferPointer(), _ShaderBlob->GetBufferSize(),
			&InputLayOut);

	if (Result != S_OK)
	{
		std::cout << "CreateInputLayOut() failed" << std::endl;
		return FALSE;
	}
	
	return InputLayOut;
}

void EngineDirectX::PixelShaderCompile(const EngineFile& _Shader)
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
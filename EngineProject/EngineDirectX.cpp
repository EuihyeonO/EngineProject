#include "EngineDirectX.h"
#include "EngineWindow.h"
#include "EngineDebug.h"
#include "ResourceHeader.h"
#include "EngineFile.h"
#include "EnginePath.h"
#include "EngineString.h"
#include "EngineResourceManager.h"
#include "EngineVertexShader.h"
#include "EngineString.h"
#include "EnginePixelShader.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

EngineDirectX::EngineDirectX()
{
}

EngineDirectX::~EngineDirectX()
{
}

std::shared_ptr<EngineVertexShader> EngineDirectX::CreateVertexShader(const EngineFile& _Shader)
{
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
		// ������ ���� ���
		if ((Result & D3D11_ERROR_FILE_NOT_FOUND) != 0)
		{
			std::wcout << "Error : Shader that try to compile is not found. File Path : " << WShaderPath << std::endl;
		}

		// ���� �޽����� ������ ���
		if (ErrorBlob != nullptr)
		{
			std::cout << "Shader Compile Error\n" << (char*)ErrorBlob->GetBufferPointer() << std::endl;
		}

		return nullptr;
	}

	MSComPtr<ID3D11VertexShader> NewVertextShader;
	
	Result = GetDevice()->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), NULL, &NewVertextShader);
	if (Result != S_OK)
	{
		std::cout << "Error : Vertexbuffer Creation failed." << std::endl;
		return nullptr;
	}

	MSComPtr<ID3D11InputLayout> InputLayOut = CreateInputLayOut(_Shader, ShaderBlob);
	
	std::shared_ptr<EngineVertexShader> NewEngineVertexShader = std::make_shared<EngineVertexShader>();
	NewEngineVertexShader->VertexShader = NewVertextShader;
	NewEngineVertexShader->InputLayOut = InputLayOut;

	CreateVertexShaderResource(NewEngineVertexShader, ShaderBlob);

	return NewEngineVertexShader;
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

STextureData EngineDirectX::CreateTexture(unsigned char* _LoadedImage, int _Width, int _Height, int _Channels)
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SRV;

	D3D11_TEXTURE2D_DESC TexDesc = {};
	TexDesc.Width = _Width;
	TexDesc.Height = _Height;
	TexDesc.MipLevels = TexDesc.ArraySize = 1;
	TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	TexDesc.SampleDesc.Count = 1;
	TexDesc.Usage = D3D11_USAGE_IMMUTABLE;
	TexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = _LoadedImage;
	InitData.SysMemPitch = TexDesc.Width * sizeof(uint8_t) * _Channels;

	HRESULT Result = GetInstance()->GetDevice()->CreateTexture2D(&TexDesc, &InitData, Texture.GetAddressOf());
	EngineDebug::CheckResult(Result);

	Result = GetInstance()->GetDevice()->CreateShaderResourceView(Texture.Get(), nullptr, SRV.GetAddressOf());
	EngineDebug::CheckResult(Result);

	STextureData NewTextureData;
	NewTextureData.Texture2D = Texture;
	NewTextureData.SRV = SRV;

	return NewTextureData;
}

std::shared_ptr<EnginePixelShader> EngineDirectX::CreatePixelShader(const EngineFile& _Shader)
{
	Microsoft::WRL::ComPtr<ID3DBlob> ShaderBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> ErrorBlob;

	UINT CompileFlag = 0;
#if defined(DEBUG) || defined(_DEBUG)
	CompileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	std::wstring WShaderPath = EngineString::StringToWString(_Shader.GetAbsolutePath());
	HRESULT Result = D3DCompileFromFile(WShaderPath.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_5_0", CompileFlag, 0, &ShaderBlob, &ErrorBlob);

	if (Result != S_OK)
	{
		// ������ ���� ���
		if ((Result & D3D11_ERROR_FILE_NOT_FOUND) != 0)
		{
			std::wcout << "Error : Shader that try to compile is not found. File Path : " << WShaderPath << std::endl;
		}

		// ���� �޽����� ������ ���
		if (ErrorBlob)
		{
			std::cout << "Shader compile error\n" << (char*)ErrorBlob->GetBufferPointer() << std::endl;
		}

		return FALSE;
	}

	Microsoft::WRL::ComPtr<ID3D11PixelShader> NewPixelShader;

	Result = GetDevice()->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), NULL, &NewPixelShader);

	if (Result != S_OK)
	{
		std::cout << "Error : Vertexbuffer Creation failed." << std::endl;
		return nullptr;
	}

	std::shared_ptr<EnginePixelShader> NewEnginePixelShader = std::make_shared<EnginePixelShader>();
	NewEnginePixelShader->PixelShader = NewPixelShader;

	CreatePixelShaderResource(NewEnginePixelShader, ShaderBlob);

	return NewEnginePixelShader;
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

MSComPtr<ID3D11SamplerState> EngineDirectX::CreateSamplerState(std::string_view _Sampler)
{
	std::string UpperName = EngineString::ToUpperReturn(_Sampler.data());

	if (UpperName == "LINEARSAMPLER")
	{
		MSComPtr<ID3D11SamplerState> NewSampler;

		D3D11_SAMPLER_DESC SamplerDesc;
		ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));

		SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		SamplerDesc.MinLOD = 0;
		SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		// Create the Sample State
		HRESULT Result = GetInstance()->GetDevice()->CreateSamplerState(&SamplerDesc, NewSampler.GetAddressOf());
		EngineDebug::CheckResult(Result);

		return NewSampler;
	}

	return MSComPtr<ID3D11SamplerState>();
}

void EngineDirectX::CreateVertexShaderResource(std::shared_ptr<EngineVertexShader> _Shader, MSComPtr<ID3DBlob> _ShaderBlob)
{
	if (_Shader == nullptr || _ShaderBlob == nullptr)
	{
		std::cerr << "Error : VSResource Creation is failed. (Nullptr)" << std::endl;
		return;
	}

	ID3D11ShaderReflection* CompileInfo = nullptr;

	HRESULT Result = D3DReflect(_ShaderBlob->GetBufferPointer(), _ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo));
	EngineDebug::CheckResult(Result);

	D3D11_SHADER_DESC Info;
	CompileInfo->GetDesc(&Info);

	D3D11_SHADER_INPUT_BIND_DESC ResDesc;

	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		std::string Name = ResDesc.Name;
		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		std::string UpperName = EngineString::ToUpperReturn(ResDesc.Name);

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResDesc.Name);

			D3D11_SHADER_BUFFER_DESC BufferDesc;
			CBufferPtr->GetDesc(&BufferDesc);

			if(_Shader->HasConstantBuffer(UpperName) == true)
			{
				continue;
			}

			MSComPtr<ID3D11Buffer> NewCBuffer = CreateConstantBuffer(BufferDesc);
			
			SConstantBuffer NewBufferData;
			NewBufferData.ConstantBuffer = NewCBuffer;
			NewBufferData.BindPoint = ResDesc.BindPoint;
			NewBufferData.Size = BufferDesc.Size;
			
			_Shader->AddConstantBuffer(UpperName, NewBufferData);

			break;
		}
		default:
			break;
		}
	}
}

void EngineDirectX::CreatePixelShaderResource(std::shared_ptr<EnginePixelShader> _Shader, MSComPtr<ID3DBlob> _ShaderBlob)
{
	if (_Shader == nullptr || _ShaderBlob == nullptr)
	{
		std::cerr << "Error : PSResource Creation is failed. (Nullptr)" << std::endl;
		return;
	}

	ID3D11ShaderReflection* CompileInfo = nullptr;

	HRESULT Result = D3DReflect(_ShaderBlob->GetBufferPointer(), _ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo));
	EngineDebug::CheckResult(Result);

	D3D11_SHADER_DESC Info;
	CompileInfo->GetDesc(&Info);

	D3D11_SHADER_INPUT_BIND_DESC ResDesc;

	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		std::string Name = ResDesc.Name;
		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		std::string UpperName = EngineString::ToUpperReturn(ResDesc.Name);

		switch (Type)
		{
		case D3D_SIT_TEXTURE:
		{
			if (_Shader->HasTexture(UpperName) == true)
			{
				continue;
			}

			STextureData TextureData;
			TextureData.BindPoint = ResDesc.BindPoint;

			_Shader->AddTexture(UpperName, TextureData);

			break;
		}
		case D3D_SIT_SAMPLER:
		{
			if (_Shader->HasSampler(UpperName) == true)
			{
				continue;
			}

			SSamplerState SamplerState;
			SamplerState.BindPoint = ResDesc.BindPoint;

			_Shader->AddSampler(UpperName, SamplerState);
		}
		default:
			break;
		}
	}
}

MSComPtr<ID3D11Buffer> EngineDirectX::CreateConstantBuffer(D3D11_SHADER_BUFFER_DESC& _Desc)
{
	D3D11_BUFFER_DESC CBufferDesc = { 0, };

	CBufferDesc.ByteWidth = _Desc.Size;
	CBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	MSComPtr<ID3D11Buffer> NewCBuffer;
	HRESULT Result = GetInstance()->GetDevice()->CreateBuffer(&CBufferDesc, nullptr, NewCBuffer.GetAddressOf());
	EngineDebug::CheckResult(Result);

	return NewCBuffer;
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
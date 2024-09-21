#pragma once
#include "DirectXHeader.h"

class EngineDirectX
{
public:
	static EngineDirectX* GetInstance()
	{
		static EngineDirectX Instance;
		return &Instance;
	}

	EngineDirectX();
	~EngineDirectX();

	EngineDirectX(const EngineDirectX& _Other) = delete;
	EngineDirectX(EngineDirectX&& _Other) noexcept = delete;
	EngineDirectX& operator=(const EngineDirectX& _Other) = delete;
	EngineDirectX& operator=(EngineDirectX&& _Other) noexcept = delete;

	static void Start()
	{
		GetInstance()->CreateDevice();
		GetInstance()->CreateSwapChain();
	}

	static MSComPtr<ID3D11Device> GetDevice()
	{
		return GetInstance()->Device;
	}

	static MSComPtr<ID3D11DeviceContext> GetDeviceContext()
	{
		return GetInstance()->DeviceContext;
	}

	static MSComPtr<ID3D11RenderTargetView> GetMainRTV()
	{
		return GetInstance()->MainRTV;
	}

	static MSComPtr<ID3D11ShaderResourceView> GetMainSRV()
	{
		return GetInstance()->MainSRV;
	}

	static MSComPtr<IDXGISwapChain> GetSwapChain()
	{
		return GetInstance()->SwapChain;
	}

	static VertexShaderData VertexShaderCompile(const class EngineFile& _ShaderFile);
	static MSComPtr<ID3D11InputLayout> CreateInputLayOut(const class EngineFile& _ShaderFile, MSComPtr<ID3DBlob> _ShaderBlob);
	
	static std::pair<MSComPtr<ID3D11Buffer>, MSComPtr<ID3D11Buffer>> CreateVertexBufferAndIndexBuffer(const struct SMesh& _Mesh);

protected:

private:
	void CreateDevice();
	void CreateSwapChain();
	
	void PixelShaderCompile(const class EngineFile& _ShaderFile);

	MSComPtr<ID3D11Device> Device = nullptr;
	MSComPtr<ID3D11DeviceContext> DeviceContext = nullptr;
	MSComPtr<IDXGISwapChain> SwapChain = nullptr;
	MSComPtr<ID3D11RenderTargetView> MainRTV = nullptr;
	MSComPtr<ID3D11ShaderResourceView> MainSRV = nullptr;
};


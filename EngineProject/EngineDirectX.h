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

protected:

private:
	void CreateDevice();
	void CreateSwapChain();

	MSComPtr<ID3D11Device> Device = nullptr;
	MSComPtr<ID3D11DeviceContext> DeviceContext = nullptr;
	MSComPtr<IDXGISwapChain> SwapChain = nullptr;
	MSComPtr<ID3D11RenderTargetView> MainRTV = nullptr;
	MSComPtr<ID3D11ShaderResourceView> MainSRV = nullptr;
};


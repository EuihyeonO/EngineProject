#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

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
		GetInstance()->CreateDeviceAndSwapChain();
		GetInstance()->CreateRenderTarget();
	}

	ID3D11Device* GetDevice()
	{
		return Device;
	}

	ID3D11DeviceContext* GetDeviceContext()
	{
		return DeviceContext;
	}

	ID3D11RenderTargetView** GetRenderTarget()
	{
		return &MainRenderTargetView;
	}

	ID3D11RenderTargetView* GetRenderT()
	{
		return MainRenderTargetView;
	}

	IDXGISwapChain* GetSwapChain()
	{
		return SwapChain;
	}
protected:

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTarget();

	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11RenderTargetView* MainRenderTargetView = nullptr;

	bool g_SwapChainOccluded = false;

	UINT g_ResizeWidth = 0;
	UINT g_ResizeHeight = 0;

};


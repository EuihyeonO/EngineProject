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
		return g_pd3dDevice;
	}

	ID3D11DeviceContext* GetDeviceContext()
	{
		return g_pd3dDeviceContext;
	}

	ID3D11RenderTargetView** GetRenderTarget()
	{
		return &g_mainRenderTargetView;
	}

	ID3D11RenderTargetView* GetRenderT()
	{
		return g_mainRenderTargetView;
	}

	IDXGISwapChain* GetSwapChain()
	{
		return g_pSwapChain;
	}
protected:

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTarget();

	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	bool                     g_SwapChainOccluded = false;
	UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
	ID3D11RenderTargetView * g_mainRenderTargetView = nullptr;
};


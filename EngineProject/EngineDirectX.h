#pragma once
#include "DirectXHeader.h"
#include "ResourceHeader.h"

#include <memory>

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

	static MSComPtr<ID3D11RenderTargetView> GetMainRTV()
	{
		return GetInstance()->MainRTV;
	}

	static MSComPtr<ID3D11ShaderResourceView> GetMainSRV()
	{
		return GetInstance()->MainSRV;
	}

	static MSComPtr<ID3D11DepthStencilView> GetMainDSV()
	{
		return GetInstance()->MainDSV;
	}

	static MSComPtr<IDXGISwapChain> GetSwapChain()
	{
		return GetInstance()->SwapChain;
	}

	static void DrawIndexed(UINT _IndexCount, UINT _StartIndex = 0, INT _BaseVertexLocation = 0)
	{
		GetInstance()->GetDeviceContext()->DrawIndexed(_IndexCount, _StartIndex, _BaseVertexLocation);
	}

	static MSComPtr<ID3D11Device> GetDevice()
	{
		return GetInstance()->Device;
	}

	static MSComPtr<ID3D11DeviceContext> GetDeviceContext()
	{
		return GetInstance()->DeviceContext;
	}

	static void RenderSetting(class std::shared_ptr<class EngineVertexShader> _VS, class std::shared_ptr<class EnginePixelShader> _PS, MSComPtr<ID3D11Buffer> _VertexBuffer, MSComPtr<ID3D11Buffer> _IndexBuffer);

	//Create
public:
	static void CreateRenderTarget();
	
	static std::shared_ptr<class EngineVertexShader> CreateVertexShader(const class EngineFile& _ShaderFile);
	static std::shared_ptr<class EnginePixelShader> CreatePixelShader(const class EngineFile& _ShaderFile);
	
	static STextureData CreateTexture(unsigned char* _LoadedImage, int _Width, int _Height, int _Channels);
	static SDepthStencil CreateDepthStencil(const D3D11_TEXTURE2D_DESC& _BufferDesc, const D3D11_DEPTH_STENCIL_DESC& _StateDesc);
	
	static MSComPtr<ID3D11InputLayout> CreateInputLayOut(const class EngineFile& _ShaderFile, MSComPtr<ID3DBlob> _ShaderBlob);
	static MSComPtr<ID3D11SamplerState> CreateSamplerState(std::string_view _Sampler);

	static std::pair<MSComPtr<ID3D11Buffer>, MSComPtr<ID3D11Buffer>> CreateVertexBufferAndIndexBuffer(const struct SMesh& _Mesh);

public:
	void SetVertexBuffer(UINT _BindPoint, MSComPtr<ID3D11Buffer> _VertexBuffer)
	{
		UINT Stride = sizeof(SVertex);
		UINT Offset = 0;

		if (RenderState.VertexBuffer != _VertexBuffer)
		{
			GetDeviceContext()->IASetVertexBuffers(0, 1, _VertexBuffer.GetAddressOf(), &Stride, &Offset);
			RenderState.VertexBuffer = _VertexBuffer;
		}
	}

	void SetIndexBuffer(MSComPtr<ID3D11Buffer> _IndexBuffer)
	{
		if(RenderState.IndexBuffer != _IndexBuffer)
		{ 
			GetDeviceContext()->IASetIndexBuffer(_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			RenderState.IndexBuffer = _IndexBuffer;
		}
	}

	void SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology)
	{
		if (RenderState.Topology != _Topology)
		{
			GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(_Topology);
			RenderState.Topology = _Topology;
		}
	}

	void SetVertexShader(MSComPtr<ID3D11VertexShader> _VertexShader)
	{
		if (RenderState.VertexShader != _VertexShader)
		{
			GetInstance()->GetDeviceContext()->VSSetShader(_VertexShader.Get(), 0, 0);
			RenderState.VertexShader = _VertexShader;
		}
	}

	void SetInputLayout(MSComPtr<ID3D11InputLayout> _InputLayout)
	{
		if (RenderState.InputLayout != _InputLayout)
		{
			GetInstance()->GetDeviceContext()->IASetInputLayout(_InputLayout.Get());
			RenderState.InputLayout = _InputLayout;
		}
	}

	void SetPixelShader(MSComPtr<ID3D11PixelShader> _PixelShader)
	{
		if (RenderState.PixelShader != _PixelShader)
		{
			GetInstance()->GetDeviceContext()->PSSetShader(_PixelShader.Get(), 0, 0);
			RenderState.PixelShader = _PixelShader;
		}
	}

	void SetRasterizerState(MSComPtr<ID3D11RasterizerState> _RSState)
	{
		if (RenderState.RSState != _RSState)
		{
			GetInstance()->GetDeviceContext()->RSSetState(_RSState.Get());
			RenderState.RSState = _RSState;
		}
	}

	static std::pair<float ,float> GetMainViewPortSize()
	{
		return MainViewPortSize;
	}

	static void SetMainViewPortSize(float _Width, float _Height)
	{
		MainViewPortSize.first = _Width;
		MainViewPortSize.second = _Height;
	}

	void SetMainViewport()
	{
		if (RenderState.ViewPort.Width != MainViewPortSize.first || RenderState.ViewPort.Height != MainViewPortSize.second)
		{
			ZeroMemory(&(RenderState.ViewPort), sizeof(D3D11_VIEWPORT));
			RenderState.ViewPort.TopLeftX = 0;
			RenderState.ViewPort.TopLeftY = 0;
			RenderState.ViewPort.Width = float(MainViewPortSize.first);
			RenderState.ViewPort.Height = float(MainViewPortSize.second);
			RenderState.ViewPort.MinDepth = 0.0f;
			RenderState.ViewPort.MaxDepth = 1.0f;

			DeviceContext->RSSetViewports(1, &(RenderState.ViewPort));

			RenderState.ViewPort.Width = MainViewPortSize.first;
			RenderState.ViewPort.Height = MainViewPortSize.second;
		}
	}

	void ClearMainRenderTarget()
	{
		float ClearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

		if (MainRTV != nullptr)
		{
			DeviceContext->ClearRenderTargetView(MainRTV.Get(), ClearColor);
		}

		if (RenderState.DSV != nullptr)
		{
			DeviceContext->ClearDepthStencilView(RenderState.DSV.Get(),D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		}
	}

	void SetRenderTarget(MSComPtr<ID3D11RenderTargetView> _RTV, MSComPtr<ID3D11DepthStencilView> _DSV)
	{
		RenderState.DSV = _DSV;
		DeviceContext->OMSetRenderTargets(1, _RTV.GetAddressOf(), _DSV.Get());
	}

	void MainRenderSetting()
	{
	}

	void SetDepthStencilState(MSComPtr<ID3D11DepthStencilState> _DSState)
	{
		if (RenderState.DSState != _DSState)
		{
			GetDeviceContext()->OMGetDepthStencilState(_DSState.GetAddressOf(), 0);
		}
	}

protected:

private:
	void CreateDevice();
	void CreateSwapChain();

	static MSComPtr<ID3D11Buffer> CreateConstantBuffer(D3D11_SHADER_BUFFER_DESC& _Desc);
	static void CreatePixelShaderResource(std::shared_ptr<EnginePixelShader> _Shader, MSComPtr<ID3DBlob> _ShaderBlob);
	static void CreateVertexShaderResource(std::shared_ptr<EngineVertexShader> _Shader, MSComPtr<ID3DBlob> _ShaderBlob);

	SRenderState RenderState;

	static std::pair<float, float> MainViewPortSize;

 	MSComPtr<ID3D11Device> Device = nullptr;
	MSComPtr<ID3D11DeviceContext> DeviceContext = nullptr;
	MSComPtr<IDXGISwapChain> SwapChain = nullptr;

	MSComPtr<ID3D11RenderTargetView> MainRTV = nullptr;
	MSComPtr<ID3D11ShaderResourceView> MainSRV = nullptr;
	MSComPtr<ID3D11DepthStencilView> MainDSV = nullptr;
};


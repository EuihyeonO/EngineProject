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

	static void RenderSetting(class std::shared_ptr<class EngineVertexShader> _VS, class std::shared_ptr<class EnginePixelShader> _PS, MSComPtr<ID3D11Buffer> _VertexBuffer, MSComPtr<ID3D11Buffer> _IndexBuffer);

	static std::shared_ptr<class EngineVertexShader> CreateVertexShader(const class EngineFile& _ShaderFile);
	static std::shared_ptr<class EnginePixelShader> CreatePixelShader(const class EngineFile& _ShaderFile);
	static MSComPtr<ID3D11InputLayout> CreateInputLayOut(const class EngineFile& _ShaderFile, MSComPtr<ID3DBlob> _ShaderBlob);
	static STextureData CreateTexture(unsigned char* _LoadedImage, int _Width, int _Height, int _Channels);
	static std::pair<MSComPtr<ID3D11Buffer>, MSComPtr<ID3D11Buffer>> CreateVertexBufferAndIndexBuffer(const struct SMesh& _Mesh);
	
	static MSComPtr<ID3D11SamplerState> CreateSamplerState(std::string_view _Sampler);

protected:

private:
	static void CreateVertexShaderResource(std::shared_ptr<EngineVertexShader> _Shader, MSComPtr<ID3DBlob> _ShaderBlob);
	static void CreatePixelShaderResource(std::shared_ptr<EnginePixelShader> _Shader, MSComPtr<ID3DBlob> _ShaderBlob);

	static MSComPtr<ID3D11Buffer> CreateConstantBuffer(D3D11_SHADER_BUFFER_DESC& _Desc);

	void CreateDevice();
	void CreateSwapChain();

	MSComPtr<ID3D11Device> Device = nullptr;
	MSComPtr<ID3D11DeviceContext> DeviceContext = nullptr;
	MSComPtr<IDXGISwapChain> SwapChain = nullptr;
	MSComPtr<ID3D11RenderTargetView> MainRTV = nullptr;
	MSComPtr<ID3D11ShaderResourceView> MainSRV = nullptr;
};


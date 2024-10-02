#pragma once
#include "EngineDirectX.h"
#include "EngineDebug.h"

class EngineRenderTarget
{

public:

	EngineRenderTarget();
	~EngineRenderTarget();

	EngineRenderTarget(const EngineRenderTarget& _Other) = delete;
	EngineRenderTarget(EngineRenderTarget&& _Other) noexcept = delete;
	EngineRenderTarget& operator=(const EngineRenderTarget& _Other) = delete;
	EngineRenderTarget& operator=(EngineRenderTarget&& _Other) noexcept = delete;

	//Getter, Setter
public:
	MSComPtr<ID3D11RenderTargetView> GetRTV()
	{
		return RTV;
	}

	MSComPtr<ID3D11ShaderResourceView> GetSRV()
	{
		return SRV;
	}

	MSComPtr<ID3D11DepthStencilView> GetDSV()
	{
		return DSV;
	}

	void SetTargetSize(UINT _Width, UINT _Height)
	{
		if (TargetSize.first == 0 && TargetSize.second == 0)
		{
			TargetSize = { _Width , _Height };
		}
		else
		{
			//Resize
		}
	}

	//Create
public:
	//EngineRenderTarget 클래스만 생성해주는 함수이다. RTV, SRV, DSV는 별도의 함수 호출을 통해 생성해야 한다.
	static std::shared_ptr<EngineRenderTarget> CreateRenderTarget(std::string _view, UINT _Width, UINT _Height, const D3D11_TEXTURE2D_DESC* _Desc = nullptr);
	void CreateRTV(const D3D11_RENDER_TARGET_VIEW_DESC* _Desc = nullptr);
	void CreateSRV(const D3D11_SHADER_RESOURCE_VIEW_DESC* _Desc = nullptr);
	void CreateDepthStencil(const D3D11_TEXTURE2D_DESC* _TexDesc = nullptr, const D3D11_DEPTH_STENCIL_VIEW_DESC* _DSVDesc = nullptr);

	//렌더타겟뷰, 뎁스스텐실뷰를 초기화한다.
	void Clear()
	{
		float Color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		EngineDirectX::GetDeviceContext()->ClearRenderTargetView(RTV.Get(), Color);
		EngineDirectX::GetDeviceContext()->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	//Destroy를 호출한 이후, 스마트 포인터 변수에 nullptr을 반드시 삽입해주어야 한다.
	void Destroy()
	{
		Texture2D = nullptr;
		DepthTexture2D = nullptr;
		RTV = nullptr;
		SRV = nullptr;
		DSV = nullptr;
		DSState = nullptr;
	}

protected:

private:
	void CreateTexture2D(const D3D11_TEXTURE2D_DESC* _Desc = nullptr);

private:
	std::pair<UINT, UINT> TargetSize = { 0, 0 };

	MSComPtr<ID3D11Texture2D> Texture2D = nullptr;
	MSComPtr<ID3D11Texture2D> DepthTexture2D = nullptr;

	MSComPtr<ID3D11RenderTargetView> RTV = nullptr;
	MSComPtr<ID3D11ShaderResourceView> SRV = nullptr;
	MSComPtr<ID3D11DepthStencilView> DSV = nullptr;

	MSComPtr<ID3D11DepthStencilState> DSState = nullptr;
};


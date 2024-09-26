#pragma once
#include "EngineDirectX.h"

class EngineRenderTarget
{

public:

	EngineRenderTarget();
	~EngineRenderTarget();

	EngineRenderTarget(const EngineRenderTarget& _Other) = delete;
	EngineRenderTarget(EngineRenderTarget&& _Other) noexcept = delete;
	EngineRenderTarget& operator=(const EngineRenderTarget& _Other) = delete;
	EngineRenderTarget& operator=(EngineRenderTarget&& _Other) noexcept = delete;

	//EngineRenderTarget 클래스만 생성해주는 함수이다. RTV, SRV, DSV는 별도의 함수 호출을 통해 생성해야 한다.
	static std::shared_ptr<EngineRenderTarget> CreateRenderTarget(std::string _view, UINT _Width, UINT _Height, const D3D11_TEXTURE2D_DESC* _Desc = nullptr)
	{
		std::shared_ptr<EngineRenderTarget> NewRenderTarget = std::make_shared<EngineRenderTarget>();
		
		NewRenderTarget->SetTargetSize(_Width, _Height);
		NewRenderTarget->CreateTexture2D(_Desc);

		return NewRenderTarget;
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

	void CreateTexture2D(const D3D11_TEXTURE2D_DESC* _Desc = nullptr)
	{
		if (_Desc == nullptr)
		{
			D3D11_TEXTURE2D_DESC Desc;
			ZeroMemory(&Desc, sizeof(Desc));

			Desc.Width = TargetSize.first;
			Desc.Height = TargetSize.second;
			Desc.MipLevels = Desc.ArraySize = 1;
			Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			Desc.SampleDesc.Count = 1;
			Desc.Usage = D3D11_USAGE_DEFAULT;
			Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET | D3D11_BIND_UNORDERED_ACCESS;
			Desc.MiscFlags = 0;
			Desc.CPUAccessFlags = 0;

			Texture2D = EngineDirectX::CreateTexture2D(Desc);
		}
		else
		{
			Texture2D = EngineDirectX::CreateTexture2D(*_Desc);
		}
	}

	void CreateRTV(const D3D11_RENDER_TARGET_VIEW_DESC* _Desc = nullptr)
	{
		if (Texture2D == nullptr)
		{
			std::cerr << "Texture2D is nullptr." << std::endl;
			return;
		}

		if (_Desc == nullptr)
		{
			D3D11_TEXTURE2D_DESC TexDesc;
			Texture2D->GetDesc(&TexDesc);

			D3D11_RENDER_TARGET_VIEW_DESC Desc;
			ZeroMemory(&Desc, sizeof(Desc));

			Desc.Format = TexDesc.Format;
			Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			Desc.Texture2D.MipSlice = 0;

			RTV = EngineDirectX::CreateRTV(Texture2D, Desc);
		}
		else
		{
			RTV = EngineDirectX::CreateRTV(Texture2D, *_Desc);
		}
	}

	void CreateSRV(const D3D11_SHADER_RESOURCE_VIEW_DESC* _Desc = nullptr)
	{
		if (Texture2D == nullptr)
		{
			std::cerr << "Texture2D is nullptr." << std::endl;
			return;
		}

		if (_Desc == nullptr)
		{
			D3D11_TEXTURE2D_DESC TexDesc;
			Texture2D->GetDesc(&TexDesc);

			D3D11_SHADER_RESOURCE_VIEW_DESC Desc;
			ZeroMemory(&Desc, sizeof(Desc));

			Desc.Format = TexDesc.Format;
			Desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

			SRV = EngineDirectX::CreateSRV(Texture2D, Desc);
		}
		else
		{
			SRV = EngineDirectX::CreateSRV(Texture2D, *_Desc);
		}
	}

protected:

private:
	std::pair<UINT, UINT> TargetSize = { 0, 0 };

	MSComPtr<ID3D11Texture2D> Texture2D = nullptr;

	MSComPtr<ID3D11RenderTargetView> RTV = nullptr;
	MSComPtr<ID3D11ShaderResourceView> SRV = nullptr;
	MSComPtr<ID3D11ShaderResourceView> DSV = nullptr;
};


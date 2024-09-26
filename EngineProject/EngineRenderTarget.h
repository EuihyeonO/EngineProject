#pragma once
#include "DirectXHeader.h"

class EngineRenderTarget
{

public:

	EngineRenderTarget();
	~EngineRenderTarget();

	EngineRenderTarget(const EngineRenderTarget& _Other) = delete;
	EngineRenderTarget(EngineRenderTarget&& _Other) noexcept = delete;
	EngineRenderTarget& operator=(const EngineRenderTarget& _Other) = delete;
	EngineRenderTarget& operator=(EngineRenderTarget&& _Other) noexcept = delete;

protected:

private:
	MSComPtr<ID3D11RenderTargetView> RTV;
	MSComPtr<ID3D10DepthStencilView> DSV;
	MSComPtr<ID3D11ShaderResourceView> SRV;

	MSComPtr<ID3D11BlendState> BlendState;
	MSComPtr<ID3D11RasterizerState> RasterizerState;
	MSComPtr<ID3D11DepthStencilState> DepthStencilState;
};


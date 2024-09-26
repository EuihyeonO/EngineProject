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

	//EngineRenderTarget 클래스만 생성해주는 함수이다. RTV, SRV, DSV는 별도의 함수 호출을 통해 생성해야 한다.
	static std::shared_ptr<EngineRenderTarget> CreateRenderTarget(std::string _view, std::shared_ptr<class EngineLevel> _OwnerLevel)
	{
		std::shared_ptr<EngineRenderTarget> NewRenderTarget = std::make_shared<EngineRenderTarget>();
		return NewRenderTarget;
	}

protected:

private:
	MSComPtr<ID3D11RenderTargetView> RTV = nullptr;
	MSComPtr<ID3D11ShaderResourceView> SRV = nullptr;
	MSComPtr<ID3D11ShaderResourceView> DSV = nullptr;
};


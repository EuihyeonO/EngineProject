#pragma once
#include "DirectXHeader.h"

class EnginePixelShader
{
	friend class EngineDirectX;
public:

	EnginePixelShader();
	~EnginePixelShader();

	EnginePixelShader(const EnginePixelShader& _Other) = delete;
	EnginePixelShader(EnginePixelShader&& _Other) noexcept = delete;
	EnginePixelShader& operator=(const EnginePixelShader& _Other) = delete;
	EnginePixelShader& operator=(EnginePixelShader&& _Other) noexcept = delete;

protected:

private:
	MSComPtr<ID3D11PixelShader> PixelShader;
};


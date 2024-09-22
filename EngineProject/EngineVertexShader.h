#pragma once
#include "DirectXHeader.h"

class EngineVertexShader
{
	friend class EngineDirectX;
public:

	EngineVertexShader();
	~EngineVertexShader();

	EngineVertexShader(const EngineVertexShader& _Other) = delete;
	EngineVertexShader(EngineVertexShader&& _Other) noexcept = delete;
	EngineVertexShader& operator=(const EngineVertexShader& _Other) = delete;
	EngineVertexShader& operator=(EngineVertexShader&& _Other) noexcept = delete;

protected:

private:
	MSComPtr<ID3D11VertexShader> VertexShader;
	MSComPtr<ID3D11InputLayout> InputLayOut;
};


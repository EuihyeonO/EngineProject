#pragma once
#include "DirectXHeader.h"

#include <unordered_map>

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

	bool HasTexture(std::string_view _Name);
	void AddTexture(std::string_view _Name, const struct STextureData& _TextureData);
	void SetTexture(std::string_view _Name, const struct STextureData& _TextureData);

	const std::unordered_map<std::string, struct STextureData>& GetAllTexture()
	{
		return TextureData;
	}

	const std::unordered_map<std::string, struct SSamplerState>& GetAllSampler()
	{
		return SamplerStates;
	}

	bool HasSampler(std::string_view _Name);
	void AddSampler(std::string_view _Name, const struct SSamplerState& _SamplerData);
	void SetSampler(std::string_view _Name, MSComPtr<ID3D11SamplerState> _SamplerData);

	MSComPtr<ID3D11PixelShader> GetPixelShader()
	{
		return PixelShader;
	}

	void SetPixelShader(MSComPtr<ID3D11PixelShader> _PixelShader)
	{
		PixelShader = _PixelShader;
	}

protected:

private:
	MSComPtr<ID3D11PixelShader> PixelShader;
	std::unordered_map<std::string, struct STextureData> TextureData;
	std::unordered_map<std::string, struct SSamplerState> SamplerStates;
};


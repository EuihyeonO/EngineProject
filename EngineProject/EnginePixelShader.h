#pragma once
#include "DirectXHeader.h"
#include "EngineDebug.h"

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

	void AddConstantBuffer(std::string _Name, const SConstantBuffer& _Buffer);
	bool HasConstantBuffer(std::string_view _Name);
	const SConstantBuffer& GetConstantBuffer(std::string_view _Name);

	void SetPixelShader(MSComPtr<ID3D11PixelShader> _PixelShader)
	{
		PixelShader = _PixelShader;
	}

	const std::unordered_map<std::string, SConstantBuffer>& GetAllConstantBuffer() const
	{
		return ConstantBuffers;
	}

	template<typename DataType>
	void SetConstantBuffer(std::string_view _Name, DataType* _Data)
	{
		if (ConstantBuffers.find(_Name.data()) == ConstantBuffers.end())
		{
			EngineDebug::LogErrorMsg(L"세팅하고자 하는 상수버퍼 이름이 쉐이더 내에 존재하지 않습니다.");
			return;
		}

		if (ConstantBuffers[_Name.data()].Size != sizeof(DataType))
		{
			EngineDebug::LogErrorMsg(L"세팅하고자 하는 상수버퍼 크기가 쉐이더 내에서 사용된 크기와 일치하지 않습니다.");
			return;
		}

		ConstantBuffers[_Name.data()].Data = reinterpret_cast<void*>(_Data);
	}

protected:

private:
	MSComPtr<ID3D11PixelShader> PixelShader;
	std::unordered_map<std::string, struct STextureData> TextureData;
	std::unordered_map<std::string, struct SSamplerState> SamplerStates;

	std::unordered_map<std::string, SConstantBuffer> ConstantBuffers;
};


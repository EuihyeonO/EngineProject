#include "EnginePixelShader.h"
#include "ResourceHeader.h"

EnginePixelShader::EnginePixelShader()
{
}

EnginePixelShader::~EnginePixelShader()
{
}

bool EnginePixelShader::HasTexture(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (TextureData.find(UpperName) != TextureData.end())
	{
		return true;
	}

	return false;
}

void EnginePixelShader::AddTexture(std::string_view _Name, const STextureData& _TextureData)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (TextureData.find(UpperName) != TextureData.end())
	{
		std::cerr << "Error : TextureData that you try add to PixelShader is already exist. TextureDataName : " << _Name << std::endl;
		return;
	}

	TextureData.insert({ UpperName, _TextureData });
}

void EnginePixelShader::SetTexture(std::string_view _Name, const STextureData& _TextureData)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (TextureData.find(UpperName) == TextureData.end())
	{
		std::cerr << "Error : TextureData that you try set to PixelShader is not exist. TextureDataName : " << _Name << std::endl;
		return;
	}

	TextureData[_Name.data()].Texture2D = _TextureData.Texture2D;
	TextureData[_Name.data()].SRV = _TextureData.SRV;
}

bool EnginePixelShader::HasSampler(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (SamplerStates.find(_Name.data()) != SamplerStates.end())
	{
		return true;
	}

	return false;
}

void EnginePixelShader::AddSampler(std::string_view _Name, const SSamplerState& _SamplerData)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (SamplerStates.find(UpperName) != SamplerStates.end())
	{
		std::cerr << "Error : SamplerStates that you try add to PixelShader is already exist. SamplerStates : " << _Name << std::endl;
		return;
	}

	SamplerStates.insert({ UpperName, _SamplerData });
}

void EnginePixelShader::SetSampler(std::string_view _Name, MSComPtr<ID3D11SamplerState> _SamplerData)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (SamplerStates.find(UpperName) == SamplerStates.end())
	{
		std::cerr << "Error : SamplerStates that you try set to PixelShader is not exist. SamplerStates : " << _Name << std::endl;
		return;
	}

	SamplerStates[_Name.data()].SamplerState = _SamplerData;
}

void EnginePixelShader::AddConstantBuffer(std::string _Name, const SConstantBuffer& _Buffer)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name);

	if (ConstantBuffers.find(UpperName) != ConstantBuffers.end())
	{
		std::cerr << "Error : ConstantBuffer that you try add to VertexShader is already exist. ConstantBufferName : " << _Name << std::endl;
		return;
	}

	ConstantBuffers[UpperName] = _Buffer;
}

bool EnginePixelShader::HasConstantBuffer(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (ConstantBuffers.find(UpperName) == ConstantBuffers.end())
	{
		return false;
	}

	return true;
}

const SConstantBuffer& EnginePixelShader::GetConstantBuffer(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (ConstantBuffers.find(UpperName) == ConstantBuffers.end())
	{
		return {};
	}

	return ConstantBuffers[_Name.data()];
}

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

#include "EnginePixelShader.h"
#include "ResourceHeader.h"
#include "EngineDebug.h"

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
		EngineDebug::LogErrorMsg(L"�ȼ� ���̴��� �߰��ϰ��� �ϴ� �ؽ��İ� �̹� �����մϴ�. ������ �̸��� �� �� ������� �ʵ��� ���ּ���.");
		return;
	}

	TextureData.insert({ UpperName, _TextureData });
}

void EnginePixelShader::SetTexture(std::string_view _Name, const STextureData& _TextureData)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (TextureData.find(UpperName) == TextureData.end())
	{
		EngineDebug::LogErrorMsg(L"�ȼ� ���̴��� �����ϰ��� �ϴ� �ؽ��İ� �ε���� �ʾҽ��ϴ�.");
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
		EngineDebug::LogErrorMsg(L"�ȼ� ���̴��� �߰��ϰ��� �ϴ� ���÷��� �̹� �����մϴ�. ������ �̸��� �� �� ������� �ʵ��� ���ּ���");
		return;
	}

	SamplerStates.insert({ UpperName, _SamplerData });
}

void EnginePixelShader::SetSampler(std::string_view _Name, MSComPtr<ID3D11SamplerState> _SamplerData)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (SamplerStates.find(UpperName) == SamplerStates.end())
	{
		EngineDebug::LogErrorMsg(L"�ȼ� ���̴��� �����ϰ��� �ϴ� ���÷��� �������� �ʽ��ϴ�.");
		return;
	}

	SamplerStates[_Name.data()].SamplerState = _SamplerData;
}

void EnginePixelShader::AddConstantBuffer(std::string _Name, const SConstantBuffer& _Buffer)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name);

	if (ConstantBuffers.find(UpperName) != ConstantBuffers.end())
	{
		EngineDebug::LogErrorMsg(L"�ȼ� ���̴��� �����ϰ��� �ϴ� ������۰� �̹� �����մϴ�. ������ �̸��� �� �� ������� �ʵ��� ���ּ���");
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

#include "EngineVertexShader.h"
#include "EngineDebug.h"

EngineVertexShader::EngineVertexShader()
{
}

EngineVertexShader::~EngineVertexShader()
{
}

bool EngineVertexShader::HasConstantBuffer(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (ConstantBuffers.find(UpperName) == ConstantBuffers.end())
	{
		return false;
	}

	return true;
}

const SConstantBuffer& EngineVertexShader::GetConstantBuffer(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name.data());

	if (ConstantBuffers.find(UpperName) == ConstantBuffers.end())
	{
		return {};
	}

	return ConstantBuffers[_Name.data()];
}

void EngineVertexShader::AddConstantBuffer(std::string _Name, const SConstantBuffer& _Buffer)
{
	std::string UpperName = EngineString::ToUpperReturn(_Name);

	if (ConstantBuffers.find(UpperName) != ConstantBuffers.end())
	{
		EngineDebug::LogErrorMsg(L"���ؽ� ���̴��� �����ϰ��� �ϴ� ������۰� �̹� �����մϴ�. ������ �̸��� �� �� ������� �ʵ��� ���ּ���");
		return;
	}

	ConstantBuffers[UpperName] = _Buffer;
}

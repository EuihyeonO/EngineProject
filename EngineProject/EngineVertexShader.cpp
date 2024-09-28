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
		EngineDebug::LogErrorMsg(L"버텍스 쉐이더에 생성하고자 하는 상수버퍼가 이미 존재합니다. 동일한 이름을 두 번 사용하지 않도록 해주세요");
		return;
	}

	ConstantBuffers[UpperName] = _Buffer;
}

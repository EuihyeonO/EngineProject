#pragma once
#include "DirectXHeader.h"
#include "EngineString.h"

#include <unordered_map>

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

	const SConstantBuffer& GetConstantBuffer(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (ConstantBuffers.find(UpperName) == ConstantBuffers.end())
		{
			return {};
		}

		return ConstantBuffers[_Name.data()];
	}

	const std::unordered_map<std::string, SConstantBuffer>& GetAllConstantBuffer() const
	{
		return ConstantBuffers;
	}

	bool HasConstantBuffer(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name.data());

		if (ConstantBuffers.find(UpperName) == ConstantBuffers.end())
		{
			return false;
		}

		return true;
	}

	const MSComPtr<ID3D11InputLayout> GetInputLayout() const
	{
		return InputLayOut;
	}

protected:

private:

	void AddConstantBuffer(std::string _Name, const SConstantBuffer& _Buffer)
	{
		std::string UpperName = EngineString::ToUpperReturn(_Name);

		if (ConstantBuffers.find(UpperName) != ConstantBuffers.end())
		{
			std::cerr << "Error : ConstantBuffer that you try add to VertexShader is already exist. ConstantBufferName : " << _Name << std::endl;
			return;
		}

		ConstantBuffers[UpperName] = _Buffer;
	}

	MSComPtr<ID3D11VertexShader> VertexShader;
	MSComPtr<ID3D11InputLayout> InputLayOut;

	//이름, 바이트 크기, 바인드 포인트, void* 총 4개.
	std::unordered_map<std::string, SConstantBuffer> ConstantBuffers;
};


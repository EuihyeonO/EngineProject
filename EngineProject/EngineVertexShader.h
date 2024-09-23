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


	void AddConstantBuffer(std::string _Name, const SConstantBuffer& _Buffer);
	bool HasConstantBuffer(std::string_view _Name);
	const SConstantBuffer& GetConstantBuffer(std::string_view _Name);

	const std::unordered_map<std::string, SConstantBuffer>& GetAllConstantBuffer() const
	{
		return ConstantBuffers;
	}

	const MSComPtr<ID3D11InputLayout> GetInputLayout() const
	{
		return InputLayOut;
	}

	template<typename DataType>
	void SetConstantBuffer(std::string_view _Name, DataType* _Data)
	{
		if (ConstantBuffers.find(_Name.data()) == ConstantBuffers.end())
		{
			std::cerr << "Error : ConstantBuffer that you try to set is invalid." << std::endl;
			return;
		}

		if (ConstantBuffers[_Name.data()].Size != sizeof(DataType))
		{
			std::cerr << "Error : Size of constantBuffer data that you try to set is not same size of shader constant." << std::endl;
			return;
		}

		ConstantBuffers[_Name.data()].Data = reinterpret_cast<void*>(_Data);
	}

protected:

private:


	MSComPtr<ID3D11VertexShader> VertexShader;
	MSComPtr<ID3D11InputLayout> InputLayOut;

	//이름, 바이트 크기, 바인드 포인트, void* 총 4개.
	std::unordered_map<std::string, SConstantBuffer> ConstantBuffers;
};


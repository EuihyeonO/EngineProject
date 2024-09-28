#pragma once
#include "DirectXHeader.h"
#include "EngineString.h"
#include "EngineDebug.h"

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

	MSComPtr<ID3D11VertexShader> GetVertexShader()
	{
		return VertexShader;
	}

	MSComPtr<ID3D11InputLayout> GetInputLayOut()
	{
		return InputLayOut;
	}

	void SetVertexShader(MSComPtr<ID3D11VertexShader> _VertexShader)
	{
		VertexShader = _VertexShader;
	}

	void SetInputLayOut(MSComPtr<ID3D11InputLayout> _InputLayOut)
	{
		InputLayOut = _InputLayOut;
	}

protected:

private:
	MSComPtr<ID3D11VertexShader> VertexShader;
	MSComPtr<ID3D11InputLayout> InputLayOut;

	//이름, 바이트 크기, 바인드 포인트, void* 총 4개.
	std::unordered_map<std::string, SConstantBuffer> ConstantBuffers;
};


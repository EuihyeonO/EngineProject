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
			EngineDebug::LogErrorMsg(L"�����ϰ��� �ϴ� ������� �̸��� ���̴� ���� �������� �ʽ��ϴ�.");
			return;
		}

		if (ConstantBuffers[_Name.data()].Size != sizeof(DataType))
		{
			EngineDebug::LogErrorMsg(L"�����ϰ��� �ϴ� ������� ũ�Ⱑ ���̴� ������ ���� ũ��� ��ġ���� �ʽ��ϴ�.");
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

	//�̸�, ����Ʈ ũ��, ���ε� ����Ʈ, void* �� 4��.
	std::unordered_map<std::string, SConstantBuffer> ConstantBuffers;
};


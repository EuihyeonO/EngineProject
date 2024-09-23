#pragma once
#include "BaseHeader.h"

class EngineDebug
{

public:
	static void CheckResult(HRESULT _Result)
	{

		if (_Result != S_OK)
		{
			_com_error Error(_Result);
			std::wstring ErrMsg = Error.ErrorMessage();

			std::wcerr << L"Error : " << ErrMsg << std::endl;
			return;
		}
	}

	EngineDebug();
	~EngineDebug();

	EngineDebug(const EngineDebug& _Other) = delete;
	EngineDebug(EngineDebug&& _Other) noexcept = delete;
	EngineDebug& operator=(const EngineDebug& _Other) = delete;
	EngineDebug& operator=(EngineDebug&& _Other) noexcept = delete;

protected:

private:

};


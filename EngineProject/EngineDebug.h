#pragma once
#include "BaseHeader.h"
#include <source_location>

class EngineDebug
{

public:
	static void CheckResult(HRESULT _Result, const std::source_location& location = std::source_location::current())
	{
		if (_Result != S_OK)
		{
			_com_error Error(_Result);
			std::wstring ErrMsg = Error.ErrorMessage();

			std::wcerr << L"에러 발생 : " << ErrMsg << std::endl;
			std::wcerr << L"File : " << location.file_name() << "\nFunction : " << location.function_name() << "\nLine : " << location.line() << std::endl;
			std::wcerr << "\033[31m" << L"--------------------------------------------------------------" << "\033[0m" << std::endl;

			return;
		}
	}

	static void LogErrorMsg(std::wstring_view _Msg, const std::source_location& location = std::source_location::current())
	{
			std::wcerr << L"에러 발생 : " << _Msg.data() << std::endl;
			std::wcerr << L"File : " << location.file_name() << "\nFunction : " << location.function_name() << "\nLine : " << location.line() << std::endl;
			std::wcerr << "\033[31m" << L"--------------------------------------------------------------" << "\033[0m" << std::endl;
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


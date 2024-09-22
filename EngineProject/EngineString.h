#pragma once
#include <string>
#include <algorithm>
#include <Windows.h>

class EngineString
{

public:
	static void ToUpper(std::string& _String)
	{
		if (_String.size() == 0)
		{
			return;
		}

		std::transform(_String.begin(), _String.end(), _String.begin(), ::toupper);
	}

	static std::string ToUpperReturn(const std::string& _String)
	{
		if (_String.size() == 0)
		{
			return "";
		}

		std::string ReturnStr = _String;
		std::transform(ReturnStr.begin(), ReturnStr.end(), ReturnStr.begin(), ::toupper);

		return ReturnStr;
	}

	static std::wstring StringToWString(const std::string& _string)
	{
		int StrSize = MultiByteToWideChar(CP_UTF8, 0, _string.c_str(), (int)_string.size(), NULL, 0);
		std::wstring Wstr(StrSize, 0);

		MultiByteToWideChar(CP_UTF8, 0, _string.c_str(), (int)_string.size(), &Wstr[0], StrSize);

		return Wstr;
	}


protected:

private:

};


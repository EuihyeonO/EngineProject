#pragma once
#include <string>
#include <algorithm>

class EngineString
{

public:

	EngineString();
	~EngineString();

	EngineString(const EngineString& _Other) = delete;
	EngineString(EngineString&& _Other) noexcept = delete;
	EngineString& operator=(const EngineString& _Other) = delete;
	EngineString& operator=(EngineString&& _Other) noexcept = delete;

	static void ToUpper(std::string& _String)
	{
		if (_String.size() == 0)
		{
			return;
		}

		std::transform(_String.begin(), _String.end(), _String.begin(), ::toupper);
	}

protected:

private:

};


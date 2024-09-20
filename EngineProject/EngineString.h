#pragma once
#include <string>
#include <algorithm>

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

protected:

private:

};


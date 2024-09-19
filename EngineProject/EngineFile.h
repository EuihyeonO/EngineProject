#pragma once
#include <string>

class EngineFile
{
	friend class EnginePath;
public:

	EngineFile();
	~EngineFile();

	EngineFile(const EngineFile& _Other) = delete;

	EngineFile(EngineFile&& _Other) noexcept
	{
		Extension = std::move(_Other.Extension);
		FileName = std::move(_Other.FileName);
		AbsolutePath = std::move(_Other.AbsolutePath);
		RelativePath = std::move(_Other.RelativePath);
	}

	EngineFile& operator=(const EngineFile& _Other) = delete;
	EngineFile& operator=(EngineFile&& _Other) noexcept = delete;

protected:

private:
	std::string FileName = "";
	std::string Extension = "";
	std::string AbsolutePath = "";
	std::string RelativePath = "";
};


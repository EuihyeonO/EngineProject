#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include "EngineDebug.h"

class EngineFile
{
	friend class EnginePath;
public:

	EngineFile();
	~EngineFile();

	EngineFile(const EngineFile& _Other);

	EngineFile(EngineFile&& _Other) noexcept
	{
		Extension = std::move(_Other.Extension);
		FileName = std::move(_Other.FileName);
		AbsolutePath = std::move(_Other.AbsolutePath);
		RelativePath = std::move(_Other.RelativePath);
	}

	EngineFile& operator=(const EngineFile& _Other) = delete;
	EngineFile& operator=(EngineFile&& _Other) noexcept = delete;

	//Getter
public:
	inline const std::string& GetFileName() const
	{
		return FileName;
	}

	inline const std::string& GetExtension() const
	{
		return Extension;
	}

	inline const std::string& GetAbsolutePath() const
	{
		return AbsolutePath;
	}

	inline const std::string& GetRelativePath() const
	{
		return RelativePath;
	}

public:
	//파일 내부에 담긴 내용을 문자열로 반환해줍니다.
	std::string GetFileString() const;

protected:

private:
	std::string FileName = "";
	std::string Extension = "";
	std::string AbsolutePath = "";
	std::string RelativePath = "";
};


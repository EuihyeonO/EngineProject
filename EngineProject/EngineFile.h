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

public:
	//파일 내부에 담긴 내용을 문자열로 반환해줍니다.
	std::string GetFileString() const
	{
		FILE* FilePtr = nullptr;
		std::string PathString = GetAbsolutePath();

		fopen_s(&FilePtr, PathString.c_str(), "rt");

		if (nullptr == FilePtr)
		{
			EngineDebug::LogErrorMsg(L"문자열로 읽고자 하는 파일이 nullptr 입니다.");
			return "";
		}

		size_t FileSize = std::filesystem::file_size(std::filesystem::path(PathString));
		std::vector<unsigned char> Buffer(FileSize);

		fread_s(&Buffer[0], Buffer.size(), FileSize, 1, FilePtr);

		if (nullptr != FilePtr)
		{
			fclose(FilePtr);
		}

		const char* Return = reinterpret_cast<const char*>(&Buffer[0]);
		return Return;
	}

	const std::string& GetFileName() const
	{
		return FileName;
	}

	const std::string& GetExtension() const
	{
		return Extension;
	}

	const std::string& GetAbsolutePath() const
	{
		return AbsolutePath;
	}

	const std::string& GetRelativePath() const
	{
		return RelativePath;
	}

protected:

private:
	std::string FileName = "";
	std::string Extension = "";
	std::string AbsolutePath = "";
	std::string RelativePath = "";
};


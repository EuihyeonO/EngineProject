#include "EngineFile.h"

EngineFile::EngineFile()
{
}

EngineFile::~EngineFile()
{
}

std::string EngineFile::GetFileString() const
{
	FILE* FilePtr = nullptr;
	std::string PathString = GetAbsolutePath();

	fopen_s(&FilePtr, PathString.c_str(), "rt");

	if (nullptr == FilePtr)
	{
		EngineDebug::LogErrorMsg(L"���ڿ��� �а��� �ϴ� ������ nullptr �Դϴ�.");
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
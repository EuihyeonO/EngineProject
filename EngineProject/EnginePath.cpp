#include <filesystem>

#include "EnginePath.h"
#include "EngineDebug.h"
#include "EngineString.h"

EnginePath::EnginePath()
{
}

EnginePath::~EnginePath()
{
}

bool EnginePath::FindFile(std::string_view _FileName, __out EngineFile& _FileData)
{
	_FileData.FileName = "";
	_FileData.AbsolutePath = "";
	_FileData.RelativePath = "";

	//CurrentPath를 Resources로 이동
	std::filesystem::path CurrentPath = std::filesystem::current_path();
	CurrentPath = CurrentPath.parent_path();
	CurrentPath += "\\Resources";

	//재귀적으로 파일 탐색
	std::filesystem::recursive_directory_iterator FindIter(CurrentPath);
	std::filesystem::recursive_directory_iterator EndIter = std::filesystem::end(FindIter);

	while (FindIter != EndIter)
	{
		if (FindIter->path().has_filename() == true && FindIter->path().filename() == _FileName)
		{
			_FileData.FileName = FindIter->path().filename().string();
			_FileData.AbsolutePath = FindIter->path().string();
			_FileData.RelativePath = FindIter->path().relative_path().string();

			_FileData.Extension = GetExtension(_FileData.FileName);
			EngineString::ToUpper(_FileData.Extension);
			
			return true;
		}

		FindIter++;
	}

	return false;
}

void EnginePath::FindAllFile(std::string_view _Extension, __out std::vector<EngineFile>& _AllFileData)
{
	_AllFileData.clear();

	//CurrentPath를 Resources로 이동
	std::filesystem::path CurrentPath = std::filesystem::current_path();
	CurrentPath = CurrentPath.parent_path();
	CurrentPath += "\\Resources";

	//재귀적으로 파일 탐색
	std::filesystem::recursive_directory_iterator FindIter(CurrentPath);
	std::filesystem::recursive_directory_iterator EndIter = std::filesystem::end(FindIter);

	while (FindIter != EndIter)
	{
		if (FindIter->path().has_filename() == true)
		{
			const std::string FileName = FindIter->path().filename().string();

			if (FileName.find(".") == std::string::npos)
			{
				FindIter++;
				continue;
			}

			std::string FileExtension = GetExtension(FileName).data();
			EngineString::ToUpper(FileExtension);
			
			std::string InputExtension = GetExtension(_Extension).data();
			EngineString::ToUpper(InputExtension);

			if (FileExtension == InputExtension)
			{
				std::filesystem::path FindPath = FindIter->path();
				_AllFileData.emplace_back();

				EngineFile& FindFile = _AllFileData.back();

				FindFile.Extension = FileExtension;
				FindFile.FileName = FindPath.filename().string();
				FindFile.AbsolutePath = FindPath.string();
				FindFile.RelativePath = FindPath.relative_path().string();
			}
		}

		FindIter++;
	}
}

std::string EnginePath::GetFileName(std::string_view _Path)
{
	std::filesystem::path Path = std::filesystem::path(_Path.data());

	if (Path.has_filename() == false)
	{
		return "";
	}

	std::string FileName = Path.filename().string();
	return FileName;
}

std::string EnginePath::GetExtension(std::string_view _FileName)
{
	std::filesystem::path Path = std::filesystem::path(_FileName.data());
	
	if (Path.has_extension() == false)
	{
		return "";
	}

	std::string FileExtension = Path.extension().string();
	return FileExtension;
}

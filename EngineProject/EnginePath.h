#pragma once
#include <vector>
#include <string_view>

#include "EngineFile.h"

class EnginePath
{

public:

	EnginePath();
	~EnginePath();

	EnginePath(const EnginePath& _Other) = delete;
	EnginePath(EnginePath&& _Other) noexcept = delete;
	EnginePath& operator=(const EnginePath& _Other) = delete;
	EnginePath& operator=(EnginePath&& _Other) noexcept = delete;

	//파일은 반드시 Resources 폴더 내부에 있어야 한다. 파일을 찾지 못하면 _FileData의 값이 모두 ""이고, false를 반환한다.
	static bool FindFile(std::string_view _FileName, __out EngineFile& _FileData);

	//인자로 받은 확장자 파일을 모두 _AllFileData에 삽입해준다. 인자에 대입하는 확장자 문자열은 .까지 붙여야 한다.
	static void FindAllFile(std::string_view _Extension, __out std::vector<EngineFile>& _AllFileData);

	//경로를 대입하면 파일 이름만 잘라서 반환
	static std::string GetFileName(std::string_view _Path);

	//파일 이름을 대입하면, 확장자만 잘라서 반환
	static std::string GetExtension(std::string_view _FileName);
protected:

private:
};


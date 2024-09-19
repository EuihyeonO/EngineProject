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

	//������ �ݵ�� Resources ���� ���ο� �־�� �Ѵ�. ������ ã�� ���ϸ� _FileData�� ���� ��� ""�̰�, false�� ��ȯ�Ѵ�.
	static bool FindFile(std::string_view _FileName, __out EngineFile& _FileData);

	//���ڷ� ���� Ȯ���� ������ ��� _AllFileData�� �������ش�. ���ڿ� �����ϴ� Ȯ���� ���ڿ��� .���� �ٿ��� �Ѵ�.
	static void FindAllFile(std::string_view _Extension, __out std::vector<EngineFile>& _AllFileData);

	//��θ� �����ϸ� ���� �̸��� �߶� ��ȯ
	static std::string GetFileName(std::string_view _Path);

	//���� �̸��� �����ϸ�, Ȯ���ڸ� �߶� ��ȯ
	static std::string GetExtension(std::string_view _FileName);
protected:

private:
};


#pragma once

enum ExtensionType
{
	FBX,
	DDS,
	PNG,
};

class EngineLoader
{

public:

	EngineLoader();
	~EngineLoader();

	EngineLoader(const EngineLoader& _Other) = delete;
	EngineLoader(EngineLoader&& _Other) noexcept = delete;
	EngineLoader& operator=(const EngineLoader& _Other) = delete;
	EngineLoader& operator=(EngineLoader&& _Other) noexcept = delete;

	void LoadAllFile(ExtensionType _Extension);
protected:

private:
	void LoadAllFBX();
};


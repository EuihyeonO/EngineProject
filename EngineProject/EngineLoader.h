#pragma once

class EngineLoader
{

public:

	EngineLoader();
	~EngineLoader();

	EngineLoader(const EngineLoader& _Other) = delete;
	EngineLoader(EngineLoader&& _Other) noexcept = delete;
	EngineLoader& operator=(const EngineLoader& _Other) = delete;
	EngineLoader& operator=(EngineLoader&& _Other) noexcept = delete;

	void Test();
protected:

private:

};


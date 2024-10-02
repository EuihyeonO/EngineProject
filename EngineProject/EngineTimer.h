#pragma once
#include <chrono>

class EngineTimer
{
	friend class Engine;
public:
	static EngineTimer* GetInstance()
	{
		static EngineTimer Instance;
		return &Instance;
	}

	EngineTimer& operator=(const EngineTimer& _Other) = delete;
	EngineTimer& operator=(EngineTimer&& _Other) noexcept = delete;

public:
	static inline float GetDeltaTime()
	{
		return GetInstance()->DeltaTime;
	}

protected:

private:
	EngineTimer();
	~EngineTimer();

	EngineTimer(const EngineTimer& _Other) = delete;
	EngineTimer(EngineTimer&& _Other) noexcept = delete;

private:
	static void DeltaTimeUpdate();

private:
	std::chrono::high_resolution_clock::time_point CurFrameTime = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point PrevFrameTime = std::chrono::high_resolution_clock::now();

	float DeltaTime;
};


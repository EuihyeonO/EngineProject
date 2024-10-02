#include "EngineTimer.h"

EngineTimer::EngineTimer()
{
}

EngineTimer::~EngineTimer()
{
}

void EngineTimer::DeltaTimeUpdate()
{
	EngineTimer* Timer = GetInstance();

	Timer->CurFrameTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> Delta = Timer->CurFrameTime - Timer->PrevFrameTime;
	
	Timer->PrevFrameTime = Timer->CurFrameTime;
	
	Timer->DeltaTime = Delta.count();
}

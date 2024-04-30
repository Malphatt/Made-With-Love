#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Update()
{
	double temp = SDL_GetTicks();

	currentTickCount = temp;
	DeltaTicks = currentTickCount - lastTickCount;

	currentFrameCount = temp;
	DeltaFrames = currentFrameCount - lastFrameCount;
}

void Timer::ResetTickCount()
{
	DeltaFrames = 0;
	lastTickCount = currentTickCount;
}

void Timer::ResetFrameCount()
{
	DeltaFrames = 0;
	lastFrameCount = currentFrameCount;
}

void Timer::Tick()
{
	ticks++;
}
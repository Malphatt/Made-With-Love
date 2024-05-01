#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Update()
{
	// Get the current time
	double temp = SDL_GetTicks();

	// Calculate the number of SDL Ticks (ms) since last tick (1/60th of a second)
	currentTickCount = temp;
	DeltaTicks = currentTickCount - lastTickCount;

	// Calculate the number of SDL Ticks (ms) since last frame (1/120th of a second)
	currentFrameCount = temp;
	DeltaFrames = currentFrameCount - lastFrameCount;
}

void Timer::ResetTickCount()
{
	// Reset the tick count
	DeltaTicks = 0;
	lastTickCount = currentTickCount;
}

void Timer::ResetFrameCount()
{
	// Reset the frame count
	DeltaFrames = 0;
	lastFrameCount = currentFrameCount;
}

void Timer::Tick()
{
	// Increment the tick count
	ticks++;
}
#include "SDL.h"

#ifndef Timer_h
#define Timer_h

class Timer
{
public:
	Timer();
	~Timer();

	void Update();

	void ResetTickCount();
	void ResetFrameCount();

	double DeltaTicks = 0;
	double DeltaFrames = 0;

	void Tick();
	int GetTicks() const { return ticks; }
private:
	double currentTickCount = 0;
	double lastTickCount = 0;

	double currentFrameCount = 0;
	double lastFrameCount = 0;

	int ticks = 0;
};

#endif // !Timer_h

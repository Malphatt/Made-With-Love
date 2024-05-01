#include "SDL.h"

#ifndef Timer_h
#define Timer_h

class Timer
{
public:
	/// <summary>
	/// Constructor for the Timer class
	/// </summary>
	Timer();
	/// <summary>
	/// Destructor for the Timer class
	/// </summary>
	~Timer();

	/// <summary>
	/// Updates the timer
	/// </summary>
	void Update();

	/// <summary>
	/// Resets the tick count to 0
	/// </summary>
	void ResetTickCount();
	/// <summary>
	/// Resets the frame count to 0
	/// </summary>
	void ResetFrameCount();

	double DeltaTicks = 0; // The delta time between ticks
	double DeltaFrames = 0; // The delta time between frames

	/// <summary>
	/// Increments the tick count by 1
	/// </summary>
	void Tick();
	/// <summary>
	/// Returns the current tick count
	/// </summary>
	/// <returns>int</returns>
	int GetTicks() const { return ticks; }
private:
	double currentTickCount = 0; // The current tick count
	double lastTickCount = 0; // The last tick count

	double currentFrameCount = 0; // The current frame count
	double lastFrameCount = 0; // The last frame count

	int ticks = 0; // The elapsed ticks of the engine
};

#endif // !Timer_h

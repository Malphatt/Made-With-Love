#include "Window.h"
#include "GO_Rect.h"

#include <vector>

#ifndef Column_h
#define Column_h

class Column : public GO_Rect
{
public:
	/// <summary>
	/// Constructor for the Column class
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="colour"></param>
	Column(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour);
	/// <summary>
	/// Destructor for the Column class
	/// </summary>
	~Column();

	/// <summary>
	/// Updates the Column object (animation)
	/// </summary>
	/// <param name="Ticks"></param>
	void Update(int Ticks);

	/// <summary>
	/// Shows the Column object (starts animation)
	/// </summary>
	/// <param name="Ticks"></param>
	void Show(int Ticks);
	/// <summary>
	/// Hides the Column object (starts animation)
	/// </summary>
	/// <param name="Ticks"></param>
	void Hide(int Ticks);
private:
	bool ShowColumn; // Whether the column is currently being shown

	int currentTicks; // The current number of ticks

	int startTicks; // The number of ticks when the animation started
	int ticksElapsed; // The number of ticks since the animation started
	int ticksSinceLastFrame; // The number of ticks since the last frame

	int animationSpeed; // The speed of the animation

	int maxAlpha; // The maximum alpha value
	int minAlpha; // The minimum alpha value
	int alphaIncrement; // The increment of the alpha value
};

#endif // !Column_h
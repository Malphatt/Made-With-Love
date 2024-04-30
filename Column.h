#include "Window.h"
#include "GO_Rect.h"

#include <vector>

#ifndef Column_h
#define Column_h

class Column : public GO_Rect
{
public:
	Column(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour);
	~Column();

	void Update(int Ticks);

	void Show(int Ticks);
	void Hide(int Ticks);

	bool ShowColumn = false;
private:
	int currentTicks = 0;

	int startTicks = 0;
	int ticksElapsed = 0;
	int ticksSinceLastFrame = 0;

	int animationSpeed = 1;

	int maxAlpha = 50;
	int minAlpha = 0;
	int alphaIncrement = 1;
};

#endif // !Column_h
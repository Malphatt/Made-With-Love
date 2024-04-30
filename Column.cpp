#include "Column.h"

Column::Column(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour) : GO_Rect(isLoggingEnabled, "Column", x, y, width, height, colour)
{
}

Column::~Column()
{
}

void Column::Update(int Ticks)
{
	this->currentTicks = Ticks;
	this->ticksElapsed = Ticks - this->startTicks;

	if (this->ShowColumn)
	{
		if (this->ticksElapsed % this->animationSpeed == 0)
		{
			if (colour->a < this->maxAlpha)
			{
				colour->a += this->alphaIncrement;
				this->ticksSinceLastFrame = 0;
			}
			else this->ticksSinceLastFrame++;
		}
	}
	else
	{
		if (this->ticksElapsed % this->animationSpeed == 0)
		{
			if (colour->a > this->minAlpha)
			{
				colour->a -= this->alphaIncrement;
				this->ticksSinceLastFrame = 0;
			}
			else this->ticksSinceLastFrame++;
		}
	}
}

void Column::Show(int Ticks)
{
	if (this->ShowColumn) return;

	this->startTicks = Ticks;
	this->ShowColumn = true;
}

void Column::Hide(int Ticks)
{
	if (!this->ShowColumn) return;

	this->startTicks = Ticks;
	this->ShowColumn = false;
}
#include "Column.h"

Column::Column(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour) : GO_Rect(isLoggingEnabled, "Column", x, y, width, height, colour)
{
	this->ShowColumn = false;
	this->currentTicks = 0;
	this->startTicks = 0;
	this->ticksElapsed = 0;
	this->ticksSinceLastFrame = 0;
	this->animationSpeed = 1;
	this->maxAlpha = 50;
	this->minAlpha = 0;
	this->alphaIncrement = 1;
}

Column::~Column()
{
}

void Column::Update(int Ticks)
{
	// Set the currentTicks and ticksElapsed
	this->currentTicks = Ticks;
	this->ticksElapsed = Ticks - this->startTicks;

	// If the column is showing, update the alpha value (fade in animation)
	if (this->ShowColumn)
	{
		if (this->ticksElapsed % this->animationSpeed == 0)
		{
			// If the alpha value is less than the maxAlpha, increment the alpha value
			if (colour->a < this->maxAlpha)
			{
				colour->a += this->alphaIncrement;
				this->ticksSinceLastFrame = 0;
			}
			// If the alpha value is greater than or equal to the maxAlpha, increment the ticksSinceLastFrame
			else this->ticksSinceLastFrame++;
		}
	}
	// If the column is hiding, update the alpha value (fade out animation)
	else
	{
		if (this->ticksElapsed % this->animationSpeed == 0)
		{
			// If the alpha value is greater than the minAlpha, decrement the alpha value
			if (colour->a > this->minAlpha)
			{
				colour->a -= this->alphaIncrement;
				this->ticksSinceLastFrame = 0;
			}
			// If the alpha value is less than or equal to the minAlpha, increment the ticksSinceLastFrame
			else this->ticksSinceLastFrame++;
		}
	}
}

void Column::Show(int Ticks)
{
	// If the column is already showing, return
	if (this->ShowColumn) return;

	// Set the startTicks to the current Ticks and set ShowColumn to true
	this->startTicks = Ticks;
	this->ShowColumn = true;
}

void Column::Hide(int Ticks)
{
	// If the column is already hidden, return
	if (!this->ShowColumn) return;

	// Set the startTicks to the current Ticks and set ShowColumn to false
	this->startTicks = Ticks;
	this->ShowColumn = false;
}
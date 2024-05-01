#include "ArrowType.h"

ArrowType::ArrowType(int direction)
{
	// 0 = normal arrow
	this->Type = 0;
	this->Direction = direction;
	this->Worth = 1;

	this->holdDuration = -1;
	this->holdWorth = 0;

	this->endArrowType = nullptr;
	this->delay = -1;
}

ArrowType::ArrowType(int direction, int holdDuration)
{
	// 1 = hold arrow
	this->Type = 1;
	this->Direction = direction;
	this->Worth = 1;

	this->holdDuration = holdDuration;
	this->holdWorth = 1;

	this->endArrowType = nullptr;
	this->delay = -1;
}

ArrowType::ArrowType(int direction, ArrowType* endArrowType, int delay)
{
	// 2 = end arrow
	this->Type = 2;
	this->Direction = direction;
	this->Worth = 3;

	this->holdDuration = -1;
	this->holdWorth = 0;

	this->endArrowType = endArrowType;
	this->delay = delay;
}

ArrowType::~ArrowType()
{
}
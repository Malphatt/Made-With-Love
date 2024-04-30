#include "ArrowType.h"

ArrowType::ArrowType(int direction)
{
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
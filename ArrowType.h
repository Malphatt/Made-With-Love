#ifndef ArrowType_h
#define ArrowType_h

class ArrowType
{
public:
	ArrowType(int startDirection);
	ArrowType(int startDirection, int holdDuration);
	ArrowType(int startDirection, ArrowType* endArrowType, int delay);
	~ArrowType();

	int GetHoldDuration() const { return holdDuration; }
	int GetHoldWorth() const { return holdWorth; }

	ArrowType* GetEndArrowType() const { return endArrowType; }
	int GetEndDirection() const { return endArrowType->Direction; }
	int GetDelay() const { return delay; }

	int Type;
	int Direction;
	int Worth = 1;
private:
	int holdDuration;
	int holdWorth;

	ArrowType* endArrowType;
	int delay;
};

#endif // !ArrowType_h


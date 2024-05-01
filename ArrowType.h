#ifndef ArrowType_h
#define ArrowType_h

class ArrowType
{
public:
	/// <summary>
	/// Constructor for the ArrowType class (type 0)
	/// </summary>
	/// <param name="startDirection"></param>
	ArrowType(int startDirection);
	/// <summary>
	/// Constructor for the ArrowType class (type 1)
	/// </summary>
	/// <param name="startDirection"></param>
	/// <param name="holdDuration"></param>
	ArrowType(int startDirection, int holdDuration);
	/// <summary>
	/// Constructor for the ArrowType class (type 2)
	/// </summary>
	/// <param name="startDirection"></param>
	/// <param name="endArrowType"></param>
	/// <param name="delay"></param>
	ArrowType(int startDirection, ArrowType* endArrowType, int delay);
	/// <summary>
	/// Destructor for the ArrowType class
	/// </summary>
	~ArrowType();

	/// <summary>
	/// Returns the hold duration of the arrow type
	/// </summary>
	/// <returns>int</returns>
	int GetHoldDuration() const { return holdDuration; }
	/// <summary>
	/// Returns the worth of the arrow type
	/// </summary>
	/// <returns>int</returns>
	int GetHoldWorth() const { return holdWorth; }

	/// <summary>
	/// Returns the end arrow type of the arrow type
	/// </summary>
	/// <returns>ArrorType*</returns>
	ArrowType* GetEndArrowType() const { return endArrowType; }
	/// <summary>
	/// Returns the end direction of the arrow type
	/// </summary>
	/// <returns>int</returns>
	int GetEndDirection() const { return endArrowType->Direction; }
	/// <summary>
	/// Returns the delay of the arrow type
	/// </summary>
	/// <returns></returns>
	int GetDelay() const { return delay; }

	int Type; // 0 = normal, 1 = hold, 2 = delay
	int Direction; // 0 = left, 1 = down, 2 = up, 3 = right
	int Worth = 1; // The worth of the arrow type
private:
	int holdDuration; // The hold duration of the arrow type
	int holdWorth; // The worth of the hold arrow type

	ArrowType* endArrowType; // The end arrow type of the arrow type
	int delay; // The delay of the arrow type
};

#endif // !ArrowType_h


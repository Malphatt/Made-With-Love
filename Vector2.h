#ifndef Vector2_h
#define Vector2_h

class Vector2
{
public:
	/// <summary>
	/// Constructor for Vector2
	/// </summary>
	Vector2();
	/// <summary>
	/// Constructor for Vector2 with x and y values
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	Vector2(int x, int y);
	/// <summary>
	/// Destructor for Vector2
	/// </summary>
	~Vector2();

	int x, y; // x and y values for the vector
};

#endif // !Vector2_h

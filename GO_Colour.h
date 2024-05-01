#ifndef GO_Colour_h
#define GO_Colour_h

class GO_Colour
{
public:
	/// <summary>
	/// Constructor for GO_Colour
	/// </summary>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <param name="a"></param>
	GO_Colour(int r, int g, int b, int a);
	/// <summary>
	/// Destructor for GO_Colour
	/// </summary>
	~GO_Colour();

	int r, g, b, a; // Red, Green, Blue, Alpha
};

#endif // GO_Colour_h
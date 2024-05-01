#include "SDL.h"
#include "GameObject.h"

#ifndef GO_Rect_h
#define GO_Rect_h

class GO_Rect : public GameObject
{
public:
	/// <summary>
	/// Constructor for a rectangle game object
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height);
	/// <summary>
	/// Constructor for a rectangle game object with a colour
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="colour"></param>
	GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour);
	/// <summary>
	/// Constructor for a rectangle game object with a velocity
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="velocity"></param>
	GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height, Vector2* velocity);
	/// <summary>
	/// Constructor for a rectangle game object with a colour and velocity
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="colour"></param>
	/// <param name="velocity"></param>
	GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour, Vector2* velocity);

	/// <summary>
	/// Destructor for a rectangle game object
	/// </summary>
	~GO_Rect();

	/// <summary>
	/// Constructor for a rectangle game object with a game object type (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height);
	/// <summary>
	/// Constructor for a rectangle game object with a game object type and colour (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="colour"></param>
	GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height, GO_Colour* colour);
	/// <summary>
	/// Constructor for a rectangle game object with a game object type and velocity (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="velocity"></param>
	GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height, Vector2* velocity);
	/// <summary>
	/// Constructor for a rectangle game object with a game object type, colour and velocity (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="colour"></param>
	/// <param name="velocity"></param>
	GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height, GO_Colour* colour, Vector2* velocity);

	/// <summary>
	/// Move the game object by a specified amount
	/// </summary>
	/// <param name="x_dir"></param>
	/// <param name="y_dir"></param>
	void MovePosition(int x_dir, int y_dir);
	/// <summary>
	/// Set the game object's position and size
	/// </summary>
	/// <param name="new_x"></param>
	/// <param name="new_y"></param>
	/// <param name="new_width"></param>
	/// <param name="new_height"></param>
	void SetConstructs(int new_x, int new_y, int new_width, int new_height);

	/// <summary>
	/// Sets the game object's height
	/// </summary>
	/// <param name="new_height"></param>
	void SetHeight(int new_height) { this->rect.h = new_height; this->height = new_height; }
	/// <summary>
	/// Returns the game object's height
	/// </summary>
	/// <returns>int</returns>
	int GetHeight() const { return rect.h; }
	/// <summary>
	/// Sets the game object's width
	/// </summary>
	/// <param name="new_width"></param>
	void SetWidth(int new_width) { this->rect.w = new_width; this->width = new_width; }
	/// <summary>
	/// Returns the game object's width
	/// </summary>
	/// <returns>int</returns>
	int GetWidth() const { return rect.w; }

	/// <summary>
	/// Updates the game object
	/// </summary>
	void Update();
	/// <summary>
	/// Draws the game object
	/// </summary>
	/// <param name="renderer"></param>
	void Draw(SDL_Renderer* renderer);
protected:
	SDL_Rect rect; // The rectangle object
};

#endif // GO_Rect_h
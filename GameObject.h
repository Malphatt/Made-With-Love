#include "SDL.h"
#include "GO_Colour.h"
#include "Vector2.h"

#include <iostream>

using namespace std;

#ifndef GameObject_h
#define GameObject_h

class GameObject
{
public:
	/// <summary>
	/// Constructor for GameObject
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	GameObject(bool* isLoggingEnabled, int x, int y);
	/// <summary>
	/// Constructor for GameObject with colour
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="colour"></param>
	GameObject(bool* isLoggingEnabled, int x, int y, GO_Colour* colour);
	/// <summary>
	/// Constructor for GameObject with velocity
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="velocity"></param>
	GameObject(bool* isLoggingEnabled, int x, int y, Vector2* velocity);
	/// <summary>
	/// Constructor for GameObject with colour and velocity
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="colour"></param>
	/// <param name="velocity"></param>
	GameObject(bool* isLoggingEnabled, int x, int y, GO_Colour* colour, Vector2* velocity);

	/// <summary>
	/// Destructor for GameObject
	/// </summary>
	~GameObject();

	/// <summary>
	/// Constructor for GameObject with type (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	GameObject(bool* isLoggingEnabled, string gameObjectType, int x, int y);
	/// <summary>
	/// Constructor for GameObject with type and colour (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="colour"></param>
	GameObject(bool* isLoggingEnabled, string gameObjectType, int x, int y, GO_Colour* colour);
	/// <summary>
	/// Constructor for GameObject with type and velocity (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="velocity"></param>
	GameObject(bool* isLoggingEnabled, string gameObjectType, int x, int y, Vector2* velocity);
	/// <summary>
	/// Constructor for GameObject with type, colour and velocity (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="colour"></param>
	/// <param name="velocity"></param>
	GameObject(bool* isLoggingEnabled, string gameObjectType, int x, int y, GO_Colour* colour, Vector2* velocity);

	/// <summary>
	/// Log function for GameObject
	/// </summary>
	/// <param name="logType"></param>
	void Log(int logType);

	/// <summary>
	/// Virtual function for moving the position of the GameObject
	/// </summary>
	/// <param name="x_dir"></param>
	/// <param name="y_dir"></param>
	virtual void MovePosition(int x_dir, int y_dir);
	/// <summary>
	/// Virtual function for setting the position of the GameObject
	/// </summary>
	/// <param name="new_x"></param>
	/// <param name="new_y"></param>
	virtual void SetConstructs(int new_x, int new_y);

	/// <summary>
	/// Returns the render layer of the GameObject
	/// </summary>
	/// <returns>size_t</returns>
	size_t GetRenderLayer() const { return renderLayer; }
	/// <summary>
	/// Sets the render layer of the GameObject
	/// </summary>
	/// <param name="renderLayer"></param>
	void SetRenderLayer(size_t renderLayer);

	/// <summary>
	/// Returns the draw index of the GameObject
	/// </summary>
	/// <returns>size_t</returns>
	size_t GetDrawIndex() const { return drawIndex; }
	/// <summary>
	/// Sets the draw index of the GameObject
	/// </summary>
	/// <param name="drawIndex"></param>
	void SetDrawIndex(size_t drawIndex);

	/// <summary>
	/// Virtual function for updating the GameObject
	/// </summary>
	virtual void Update();
	/// <summary>
	/// Virtual function for drawing the GameObject
	/// </summary>
	/// <param name="renderer"></param>
	virtual void Draw(SDL_Renderer* renderer) = 0;

	/// <summary>
	/// Sets the GameObject to be destroyed
	/// </summary>
	void DestroyObject();
	bool Destroy = false; // If the GameObject is to be destroyed

	int x, y, width, height; // Position and size of the GameObject
	GO_Colour* colour = new GO_Colour(255, 255, 255, 255); // Colour of the GameObject
	Vector2* velocity = new Vector2(0, 0); // Velocity of the GameObject

	string GameObjectType; // Type of the GameObject
protected:
	size_t renderLayer; // Render layer of the GameObject
	size_t drawIndex; // Draw index of the GameObject

	bool* isLoggingEnabled; // If logging is enabled
};

#endif // GameObject_h
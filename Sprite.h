#include "GO_Rect.h"

#include <vector>

#ifndef Sprite_h
#define Sprite_h

class Sprite : public GO_Rect
{
public:
	/// <summary>
	/// Constructor for Sprite
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="spritePath"></param>
	Sprite(bool* isLoggingEnabled, int x, int y, int w, int h, string spritePath);
	/// <summary>
	/// Constructor for Sprite with velocity
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="velocity"></param>
	/// <param name="spritePath"></param>
	Sprite(bool* isLoggingEnabled, int x, int y, int w, int h, Vector2* velocity, string spritePath);

	/// <summary>
	/// Destructor for Sprite
	/// </summary>
	~Sprite();

	/// <summary>
	/// Constructor for Sprite (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="spritePath"></param>
	Sprite(bool* isLoggingEnabled, string gameObjectType, int x, int y, int w, int h, string spritePath);
	/// <summary>
	/// Constructor for Sprite with velocity (For Inheritance)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="gameObjectType"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="velocity"></param>
	/// <param name="spritePath"></param>
	Sprite(bool* isLoggingEnabled, string gameObjectType, int x, int y, int w, int h, Vector2* velocity, string spritePath);

	/// <summary>
	/// Initializes the Sprite
	/// </summary>
	/// <param name="renderer"></param>
	void Init(SDL_Renderer* renderer);

	/// <summary>
	/// Changes the Sprite Texture to the specified path
	/// </summary>
	/// <param name="spritePath"></param>
	void ChangeSpritePath(string spritePath);

	/// <summary>
	/// Draws the Sprite
	/// </summary>
	/// <param name="renderer"></param>
	void Draw(SDL_Renderer* renderer);

	SDL_Texture* SpriteTexture; // The Texture of the Sprite
protected:
	SDL_Renderer* renderer; // The Renderer

	string spritePath; // The Path to the Sprite
};

#endif // !Sprite_h

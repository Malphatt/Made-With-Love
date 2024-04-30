#include "GO_Rect.h"

#include <vector>

#ifndef Sprite_h
#define Sprite_h

class Sprite : public GO_Rect
{
public:
	Sprite(bool* isLoggingEnabled, int x, int y, int w, int h, string spritePath);
	Sprite(bool* isLoggingEnabled, int x, int y, int w, int h, Vector2* velocity, string spritePath);

	~Sprite();

	Sprite(bool* isLoggingEnabled, string gameObjectType, int x, int y, int w, int h, string spritePath);
	Sprite(bool* isLoggingEnabled, string gameObjectType, int x, int y, int w, int h, Vector2* velocity, string spritePath);

	void Init(SDL_Renderer* renderer);

	void ChangeSpritePath(string spritePath);

	void Draw(SDL_Renderer* renderer);

	SDL_Texture* SpriteTexture;
protected:
	SDL_Renderer* renderer;

	string spritePath;
};

#endif // !Sprite_h

#include "Sprite.h"

#include <SDL_image.h>

Sprite::Sprite(bool* isLoggingEnabled, int x, int y, int w, int h, string spritePath) : GO_Rect(isLoggingEnabled, "Sprite", x, y, w, h)
{
	this->SpriteTexture = nullptr;

	this->renderer = nullptr;
	this->spritePath = spritePath;
}

Sprite::Sprite(bool* isLoggingEnabled, int x, int y, int w, int h, Vector2* velocity, string spritePath) : GO_Rect(isLoggingEnabled, "Sprite", x, y, w, h, velocity)
{
	this->SpriteTexture = nullptr;

	this->renderer = nullptr;
	this->spritePath = spritePath;
}

Sprite::~Sprite()
{
}

Sprite::Sprite(bool* isLoggingEnabled, string gameObjectType, int x, int y, int w, int h, string spritePath) : GO_Rect(isLoggingEnabled, gameObjectType, x, y, w, h)
{
	this->SpriteTexture = nullptr;

	this->renderer = nullptr;
	this->spritePath = spritePath;
}

Sprite::Sprite(bool* isLoggingEnabled, string gameObjectType, int x, int y, int w, int h, Vector2* velocity, string spritePath) : GO_Rect(isLoggingEnabled, gameObjectType, x, y, w, h, velocity)
{
	this->SpriteTexture = nullptr;

	this->renderer = nullptr;
	this->spritePath = spritePath;
}

void Sprite::Init(SDL_Renderer* renderer)
{
	SDL_Surface* SpriteSurface = IMG_Load(this->spritePath.c_str());
	this->SpriteTexture = SDL_CreateTextureFromSurface(renderer, SpriteSurface);
	SDL_FreeSurface(SpriteSurface);

	this->renderer = renderer;
}

void Sprite::ChangeSpritePath(string spritePath)
{
	this->spritePath = spritePath;

	SDL_Surface* SpriteSurface = IMG_Load(this->spritePath.c_str());
	this->SpriteTexture = SDL_CreateTextureFromSurface(this->renderer, SpriteSurface);
	SDL_FreeSurface(SpriteSurface);
}

void Sprite::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, this->SpriteTexture, NULL, &rect);
}
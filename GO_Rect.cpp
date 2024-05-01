#include "GO_Rect.h"
#include "Logger.h"

GO_Rect::GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height) : GameObject(isLoggingEnabled, "GO_Rect", x, y)
{
	this->rect = { x, y, width, height };
	this->width = width;
	this->height = height;
}

GO_Rect::GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour) : GameObject(isLoggingEnabled, "GO_Rect", x, y, colour)
{
	this->rect = { x, y, width, height };
	this->width = width;
	this->height = height;
}

GO_Rect::GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height, Vector2* velocity) : GameObject(isLoggingEnabled, "GO_Rect", x, y, velocity)
{
	this->rect = { x, y, width, height };
	this->width = width;
	this->height = height;
}

GO_Rect::GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour, Vector2* velocity) : GameObject(isLoggingEnabled, "GO_Rect", x, y, colour, velocity)
{
	this->rect = { x, y, width, height };
	this->width = width;
	this->height = height;
}

GO_Rect::~GO_Rect()
{
}

GO_Rect::GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height) : GameObject(isLoggingEnabled, gameObjectType, x, y)
{
	this->rect = { x, y, width, height };
	this->width = width;
	this->height = height;
}

GO_Rect::GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height, GO_Colour* colour) : GameObject(isLoggingEnabled, gameObjectType, x, y, colour)
{
	this->rect = { x, y, width, height };
	this->width = width;
	this->height = height;
}

GO_Rect::GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height, Vector2* velocity) : GameObject(isLoggingEnabled, gameObjectType, x, y, velocity)
{
	this->rect = { x, y, width, height };
	this->width = width;
	this->height = height;
}

GO_Rect::GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height, GO_Colour* colour, Vector2* velocity) : GameObject(isLoggingEnabled, gameObjectType, x, y, colour, velocity)
{
	this->rect = { x, y, width, height };
	this->width = width;
	this->height = height;
}

void GO_Rect::MovePosition(int x_dir, int y_dir)
{
	// Move the rectangle
	this->rect.x += x_dir;
	this->rect.y += y_dir;

	this->x = this->rect.x;
	this->y = this->rect.y;
}

void GO_Rect::SetConstructs(int new_x, int new_y, int new_width, int new_height)
{
	// Set the rectangle position and size
	this->rect = { new_x, new_y, new_width, new_height };

	this->x = this->rect.x;
	this->y = this->rect.y;
	this->width = new_width;
	this->height = new_height;
}

void GO_Rect::Update()
{
	// Move the rectangle
	MovePosition(velocity->x, velocity->y);

	// Destroy the object if it goes off the top of the screen
	if (rect.y < 0 - rect.h) DestroyObject();
}

void GO_Rect::Draw(SDL_Renderer* renderer)
{
	// Set the colour of the rectangle and draw it
	SDL_SetRenderDrawColor(renderer, colour->r, colour->g, colour->b, colour->a);
	SDL_RenderFillRect(renderer, &rect);
}
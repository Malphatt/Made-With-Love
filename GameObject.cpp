#include "GameObject.h"
#include "Logger.h"

GameObject::GameObject(bool* isLoggingEnabled, int x, int y)
{
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;
	this->colour = new GO_Colour(255, 255, 255, 255);
	this->velocity = new Vector2(0, 0);
	this->drawIndex = -1;
	this->GameObjectType = "GameObject";
	this->isLoggingEnabled = isLoggingEnabled;

	Log(0);
}

GameObject::GameObject(bool* isLoggingEnabled, int x, int y, GO_Colour* colour)
{
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;
	this->colour = colour;
	this->velocity = new Vector2(0, 0);
	this->drawIndex = -1;
	this->GameObjectType = "GameObject";
	this->isLoggingEnabled = isLoggingEnabled;

	Log(0);
}

GameObject::GameObject(bool* isLoggingEnabled, int x, int y, Vector2* velocity)
{
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;
	this->colour = new GO_Colour(255, 255, 255, 255);
	this->velocity = velocity;
	this->drawIndex = -1;
	this->GameObjectType = "GameObject";
	this->isLoggingEnabled = isLoggingEnabled;

	Log(0);
}

GameObject::GameObject(bool* isLoggingEnabled, int x, int y, GO_Colour* colour, Vector2* velocity)
{
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;
	this->colour = colour;
	this->velocity = velocity;
	this->drawIndex = -1;
	this->GameObjectType = "GameObject";
	this->isLoggingEnabled = isLoggingEnabled;

	Log(0);
}

GameObject::GameObject(bool* isLoggingEnabled, string GameObjectType, int x, int y)
{
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;
	this->colour = new GO_Colour(255, 255, 255, 255);
	this->velocity = new Vector2(0, 0);
	this->drawIndex = -1;
	this->GameObjectType = GameObjectType;
	this->isLoggingEnabled = isLoggingEnabled;

	Log(0);
}

GameObject::GameObject(bool* isLoggingEnabled, string GameObjectType, int x, int y, GO_Colour* colour)
{
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;
	this->colour = colour;
	this->velocity = new Vector2(0, 0);
	this->drawIndex = -1;
	this->GameObjectType = GameObjectType;
	this->isLoggingEnabled = isLoggingEnabled;

	Log(0);
}

GameObject::GameObject(bool* isLoggingEnabled, string GameObjectType, int x, int y, Vector2* velocity)
{
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;
	this->colour = new GO_Colour(255, 255, 255, 255);
	this->velocity = velocity;
	this->drawIndex = -1;
	this->GameObjectType = GameObjectType;
	this->isLoggingEnabled = isLoggingEnabled;

	Log(0);
}

GameObject::GameObject(bool* isLoggingEnabled, string GameObjectType, int x, int y, GO_Colour* colour, Vector2* velocity)
{
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;
	this->colour = colour;
	this->velocity = velocity;
	this->drawIndex = -1;
	this->GameObjectType = GameObjectType;
	this->isLoggingEnabled = isLoggingEnabled;

	// Log the creation of the object
	Log(0);
}

GameObject::~GameObject()
{
	delete colour;
	delete velocity;

	// Log the destruction of the object
	Log(1);
}

void GameObject::Log(int logType)
{
	// If logging is disabled, return
	if (!*isLoggingEnabled) return;

	// Log the creation or destruction of the object
	switch (logType)
	{
	case 0:
		SDL_Log("%s %s created (%p)", Logger::GetTimestamp().c_str(), GameObjectType.c_str(), this);
		break;
	case 1:
		SDL_Log("%s %s destroyed (%p)", Logger::GetTimestamp().c_str(), GameObjectType.c_str(), this);
		break;
	}
}

void GameObject::MovePosition(int x_dir, int y_dir)
{
	// Move the object by the specified amount
	this->x += x_dir;
	this->y += y_dir;
}

void GameObject::SetConstructs(int new_x, int new_y)
{
	// Set the object's position to the specified coordinates
	this->x = new_x;
	this->y = new_y;
}

void GameObject::SetRenderLayer(size_t renderLayer)
{
	// Set the object's render layer
	this->renderLayer = renderLayer;
}

void GameObject::SetDrawIndex(size_t drawIndex)
{
	// Set the object's draw index
	this->drawIndex = drawIndex;
}

void GameObject::Update()
{
	// Update the object's position
	MovePosition(velocity->x, velocity->y);

	// If the object is off the top of the screen, destroy it
	if (y < 0) DestroyObject();
}

void GameObject::DestroyObject()
{
	// Set the object's destroy flag to true
	Destroy = true;
}
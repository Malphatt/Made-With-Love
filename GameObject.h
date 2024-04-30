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
	GameObject(bool* isLoggingEnabled, int x, int y);
	GameObject(bool* isLoggingEnabled, int x, int y, GO_Colour* colour);
	GameObject(bool* isLoggingEnabled, int x, int y, Vector2* velocity);
	GameObject(bool* isLoggingEnabled, int x, int y, GO_Colour* colour, Vector2* velocity);

	~GameObject();

	GameObject(bool* isLoggingEnabled, string gameObjectType, int x, int y);
	GameObject(bool* isLoggingEnabled, string gameObjectType, int x, int y, GO_Colour* colour);
	GameObject(bool* isLoggingEnabled, string gameObjectType, int x, int y, Vector2* velocity);
	GameObject(bool* isLoggingEnabled, string gameObjectType, int x, int y, GO_Colour* colour, Vector2* velocity);

	void Log(int logType);

	virtual void MovePosition(int x_dir, int y_dir);
	virtual void SetConstructs(int new_x, int new_y);

	size_t GetRenderLayer() const { return renderLayer; }
	void SetRenderLayer(size_t renderLayer);

	size_t GetDrawIndex() const { return drawIndex; }
	void SetDrawIndex(size_t drawIndex);

	virtual void Update();
	virtual void Draw(SDL_Renderer* renderer) = 0;

	void DestroyObject();
	bool Destroy = false;

	int x, y, width, height;
	GO_Colour* colour = new GO_Colour(255, 255, 255, 255);
	Vector2* velocity = new Vector2(0, 0);

	string GameObjectType;
protected:
	size_t renderLayer;
	size_t drawIndex;

	bool* isLoggingEnabled;
};

#endif // GameObject_h
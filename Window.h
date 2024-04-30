#include "SDL.h"
#include "GameObject.h"

#include <iostream>
#include <vector>

using namespace std;

#ifndef Window_h
#define Window_h

class Window
{
public:
	Window(string windowName, int x, int y, int width, int height, int logicalWidth, int logicalHeight, bool* gKeys);
	~Window();

	void SetWindowName(string windowName);
	void SetResolution(int width, int height);

	SDL_Window* GetWindow() { return window; }
	SDL_Renderer* GetRenderer() { return renderer; }

	vector<vector<GameObject*>> GetGameObjectsToDraw() const { return gameObjects; }
	size_t AddGameObject(GameObject* gameObject, size_t renderLayer);
	GameObject* RemoveGameObject(size_t renderLayer, size_t drawIndex);

	void HandleInput(SDL_Event* event);
	void Clear();
	void Draw();
	void Render();

	bool GameObjectIsOnScreen(int renderLayer, int drawIndex);
	bool GameObjectIsOnTopPercentScreen(int renderLayer, int drawIndex, double percent);
	bool GameObjectIsOnBottomPercentScreen(int renderLayer, int drawIndex, double percent);

	string windowName;
	int x, y,
		width, height,
		screenWidth, screenHeight,
		smallWindowWidth, smallWindowHeight,
		logicalWidth, logicalHeight;
	int mouseX, mouseY;
	bool fullScreen = false;
	GO_Colour backgroundColour = { 0, 0, 0, 255 };

	int FrameRate = 60;
	bool renderWindowContents = true;
	bool* IsLoggingEnabled = new bool(true);
private:
	void toggleLogging() { *IsLoggingEnabled = !*IsLoggingEnabled; }
	void toggleFullScreen();

	vector<vector<GameObject*>> gameObjects;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* icon;
	SDL_Surface* windowSurface;

	bool* gKeys;

};

#endif // Window_h
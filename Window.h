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
	/// <summary>
	/// Constructor for the Window class
	/// </summary>
	/// <param name="windowName"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="logicalWidth"></param>
	/// <param name="logicalHeight"></param>
	/// <param name="gKeys"></param>
	Window(string windowName, int x, int y, int width, int height, int logicalWidth, int logicalHeight, bool* gKeys);
	/// <summary>
	/// Destructor for the Window class
	/// </summary>
	~Window();

	/// <summary>
	/// Sets the name of the window
	/// </summary>
	/// <param name="windowName"></param>
	void SetWindowName(string windowName);
	/// <summary>
	/// Sets the resolution of the window
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	void SetResolution(int width, int height);

	/// <summary>
	/// Returns the window
	/// </summary>
	/// <returns>SDL_Window*</returns>
	SDL_Window* GetWindow() { return window; }
	/// <summary>
	/// Returns the renderer
	/// </summary>
	/// <returns>SDL_Renderer*</returns>
	SDL_Renderer* GetRenderer() { return renderer; }

	/// <summary>
	/// Returns the game objects to draw
	/// </summary>
	/// <returns>vector<vector<GameObject*>> </returns>
	vector<vector<GameObject*>> GetGameObjectsToDraw() const { return gameObjects; }
	/// <summary>
	/// Adds a game object to the game objects to draw and returns the draw index
	/// </summary>
	/// <param name="gameObject"></param>
	/// <param name="renderLayer"></param>
	/// <returns>size_t</returns>
	size_t AddGameObject(GameObject* gameObject, size_t renderLayer);
	/// <summary>
	/// Removes a game object from the game objects to draw and returns it
	/// </summary>
	/// <param name="renderLayer"></param>
	/// <param name="drawIndex"></param>
	/// <returns>GameObject*</returns>
	GameObject* RemoveGameObject(size_t renderLayer, size_t drawIndex);

	/// <summary>
	/// Handles the keyboard input
	/// </summary>
	/// <param name="event"></param>
	void HandleInput(SDL_Event* event);
	/// <summary>
	/// Clears the renderer
	/// </summary>
	void Clear();
	/// <summary>
	/// Draws the game objects to the renderer
	/// </summary>
	void Draw();
	/// <summary>
	/// Presents the drawn game objects to the renderer
	/// </summary>
	void Render();

	/// <summary>
	/// Returns whether a game object is within the bounds of the screen
	/// </summary>
	/// <param name="renderLayer"></param>
	/// <param name="drawIndex"></param>
	/// <returns>bool</returns>
	bool GameObjectIsOnScreen(int renderLayer, int drawIndex);
	/// <summary>
	/// Returns whether a game object is within the top section of the screen by a certain percentage
	/// </summary>
	/// <param name="renderLayer"></param>
	/// <param name="drawIndex"></param>
	/// <param name="percent"></param>
	/// <returns>bool</returns>
	bool GameObjectIsOnTopPercentScreen(int renderLayer, int drawIndex, double percent);
	/// <summary>
	/// Returns whether a game object is within the bottom section of the screen by a certain percentage
	/// </summary>
	/// <param name="renderLayer"></param>
	/// <param name="drawIndex"></param>
	/// <param name="percent"></param>
	/// <returns>bool</returns>
	bool GameObjectIsOnBottomPercentScreen(int renderLayer, int drawIndex, double percent);

	string windowName; // Name of the window
	int x, y, // Constraint of the window
		width, height,
		screenWidth, screenHeight,
		smallWindowWidth, smallWindowHeight,
		logicalWidth, logicalHeight;
	int mouseX, mouseY; // Mouse position
	bool fullScreen = false; // Whether the window is in full screen mode
	GO_Colour backgroundColour = { 0, 0, 0, 255 }; // Background colour of the window

	int FrameRate = 60; // Frame rate of the window
	bool renderWindowContents = true; // Whether the window contents should be rendered
	bool* IsLoggingEnabled = new bool(true); // Whether logging is enabled
private:
	/// <summary>
	/// Toggles logging
	/// </summary>
	void toggleLogging() { *IsLoggingEnabled = !*IsLoggingEnabled; }
	/// <summary>
	/// Toggles full screen
	/// </summary>
	void toggleFullScreen();

	vector<vector<GameObject*>> gameObjects; // Game objects to draw

	SDL_Window* window; // Window
	SDL_Renderer* renderer; // Renderer
	SDL_Surface* icon; // Window Icon
	SDL_Surface* windowSurface; // Window surface

	bool* gKeys; // Keyboard input
};

#endif // Window_h
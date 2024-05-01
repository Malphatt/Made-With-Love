#include "SDL.h"
#include "SDL_image.h"

#include "Window.h"
#include "Timer.h"
#include "Score.h"
#include "Spawner.h"
#include "PlayerSprite.h"

#include <iostream>
#include <vector>

using namespace std;

#ifndef GameWorld_h
#define GameWorld_h

class GameWorld
{
public:
	/// <summary>
	/// Constructor for the GameWorld class
	/// </summary>
	GameWorld();
	/// <summary>
	/// Destructor for the GameWorld class
	/// </summary>
	~GameWorld();

	/// <summary>
	/// Main game loop
	/// </summary>
	void HandleEvents();
	/// <summary>
	/// Handles input from the user
	/// </summary>
	void Input();
	/// <summary>
	/// Updates everything in the game
	/// </summary>
	void Update();
	/// <summary>
	/// Renders everything in the game
	/// </summary>
	void Render();

	bool* gKeys; // Array of keys that are pressed
	Window* window; // Window object
	Uint32 tickRate = 60; // Tick rate of the game
private:
	bool W_Primed = true; // Boolean for if the W key is ready to be pressed
	bool W_R_Primed = false; // Boolean for if the W key is ready to be released
	bool A_Primed = true; // Boolean for if the A key is ready to be pressed
	bool A_R_Primed = false; // Boolean for if the A key is ready to be released
	bool S_Primed = true; // Boolean for if the S key is ready to be pressed
	bool S_R_Primed = false; // Boolean for if the S key is ready to be released
	bool D_Primed = true; // Boolean for if the D key is ready to be pressed
	bool D_R_Primed = false; // Boolean for if the D key is ready to be released

	bool running = true; // Boolean for if the game is running
	Timer* Clock; // Timer object for the game

	PlayerSprite* Player; // Player object
	Score* PlayerScore; // Score object

	Spawner* ObjectSpawner; // Spawner object
};

#endif // !GameWorld_h


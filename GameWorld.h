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
	GameWorld();
	~GameWorld();

	void HandleEvents();
	void Input();
	void Update();
	void Render();

	bool* gKeys;
	Window* window;
	Uint32 tickRate = 60;
private:
	bool W_Primed = true;
	bool W_R_Primed = false;
	bool A_Primed = true;
	bool A_R_Primed = false;
	bool S_Primed = true;
	bool S_R_Primed = false;
	bool D_Primed = true;
	bool D_R_Primed = false;

	bool running = true;
	Timer* Clock;

	PlayerSprite* Player;
	Score* PlayerScore;

	Spawner* ObjectSpawner;
};

#endif // !GameWorld_h


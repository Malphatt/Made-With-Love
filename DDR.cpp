#include "GameWorld.h"

int main(int argc, char* argv[])
{
	//Try to initialise SDL:
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return 1;

	//Create a new GameWorld object:
	GameWorld _gameWorld0;
	_gameWorld0.HandleEvents();

	return 0;
}
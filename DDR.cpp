#include "GameWorld.h"

int main(int argc, char* argv[])
{
	//Try to initialise.. if we can't, then exit this program:
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return 1;

	//Create a new GameWorld object:
	GameWorld _gameWorld0;
	_gameWorld0.HandleEvents();

	return 0;
}
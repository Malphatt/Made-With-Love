#include "GameWorld.h"
#include "Logger.h"

#include <future>

GameWorld::GameWorld()
{
	// Initialize variables
	gKeys = new bool[512];
	window = new Window("Matthew Freeman - CGP2015 Game Programming - 26470281 - Made With Love", 100, 100, 1280, 720, 1920, 1080, gKeys);

	Clock = new Timer();
	Player = new PlayerSprite(window->IsLoggingEnabled, window->logicalWidth / 2, window->logicalHeight / 2);
	Player->SetConstructs((window->logicalWidth / 4 * 3) - (Player->GetWidth() / 2), (window->logicalHeight / 2) - (Player->GetHeight() / 2), Player->GetWidth(), Player->GetHeight());
	Player->Init(window->GetRenderer());
	window->AddGameObject(Player, 3);
	PlayerScore = new Score();
	PlayerScore->Init(window);
	ObjectSpawner = new Spawner(window, Clock, PlayerScore);
}

GameWorld::~GameWorld()
{
	delete[] gKeys;
	delete window;
}
void GameWorld::HandleEvents()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		running = false;
	}

	// Initialize Object Spawner
	if (ObjectSpawner->Init() == false)
	{
		printf("Failed to initialize!\n");
		running = false;
	}

	// Main game loop
	SDL_Event _gameWorld0Event;
	while (running)
	{
		Clock->Update();

		// Input
		if (SDL_PollEvent(&_gameWorld0Event))
		{
			if (_gameWorld0Event.type == SDL_QUIT) running = false;

			if (_gameWorld0Event.type == SDL_WINDOWEVENT)
			{
				if (_gameWorld0Event.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
				if (_gameWorld0Event.window.event == SDL_WINDOWEVENT_MOVED) ObjectSpawner->Seek(Clock->GetTicks());
			}

			window->HandleInput(&_gameWorld0Event);
			Input();
		}

		// Update
		if (Clock->DeltaTicks >= static_cast<double>(1000) / tickRate)
			async(&GameWorld::Update, this);

		// Render
		if (Clock->DeltaFrames >= static_cast<double>(1000) / window->FrameRate)
			Render();
	}
}

void GameWorld::Input()
{
	// Esc
	if (gKeys[SDLK_ESCAPE] == true)
		running = false;

	// W
	if (gKeys[SDLK_w] == true)
		// Pressed
		if (W_Primed == true)
		{
			// Add score
			PlayerScore->AddScore(ObjectSpawner->CheckCollision(2, Clock->GetTicks()));
			// Set player sprite state
			Player->SetPlayerState(PlayerSprite::Up, Clock->GetTicks());
			//if (Clock->GetTicks() < 3900) cout << "Ticks: " << Clock->GetTicks() - 132 << " | Type: 2" << endl; // Speed = 8
			//else cout << "Ticks: " << Clock->GetTicks() - 88 << " | Type: 2" << endl; // Speed = 12
			W_Primed = false;
			W_R_Primed = true;
		}
		// Held
		else // Add score
			PlayerScore->AddScore(ObjectSpawner->CheckHoldCollision(2, Clock->GetTicks()));
	if (gKeys[SDLK_w] == false) // Released (Prime the key to check for next press)
	{
		if (W_R_Primed == true)
		{
			// Add score
			PlayerScore->AddScore(ObjectSpawner->CheckReleaseCollision(2, Clock->GetTicks()));
			W_Primed = true;
			W_R_Primed = false;
		}
	}

	// A
	if (gKeys[SDLK_a] == true)
		// Pressed
		if (A_Primed == true)
		{
			// Add score
			PlayerScore->AddScore(ObjectSpawner->CheckCollision(0, Clock->GetTicks()));
			// Set player sprite state
			Player->SetPlayerState(PlayerSprite::Left, Clock->GetTicks());
			//if (Clock->GetTicks() < 3900) cout << "Ticks: " << Clock->GetTicks() - 132 << " | Type: 0" << endl; // Speed = 8
			//else cout << "Ticks: " << Clock->GetTicks() - 88 << " | Type: 0" << endl; // Speed = 12
			A_Primed = false;
			A_R_Primed = true;
		}
		// Held
		else // Add score
			PlayerScore->AddScore(ObjectSpawner->CheckHoldCollision(0, Clock->GetTicks()));
	if (gKeys[SDLK_a] == false) // Released (Prime the key to check for next press)
	{
		if (A_R_Primed == true)
		{
			// Add score
			PlayerScore->AddScore(ObjectSpawner->CheckReleaseCollision(0, Clock->GetTicks()));
			A_Primed = true;
			A_R_Primed = false;
		}
	}

	// S
	if (gKeys[SDLK_s] == true)
		// Pressed
		if (S_Primed == true)
		{
			// Add score
			PlayerScore->AddScore(ObjectSpawner->CheckCollision(1, Clock->GetTicks()));
			// Set player sprite state
			Player->SetPlayerState(PlayerSprite::Down, Clock->GetTicks());
			//if (Clock->GetTicks() < 3900) cout << "Ticks: " << Clock->GetTicks() - 132 << " | Type: 1" << endl; // Speed = 8
			//else cout << "Ticks: " << Clock->GetTicks() - 88 << " | Type: 1" << endl; // Speed = 12
			S_Primed = false;
			S_R_Primed = true;
		}
		// Held
		else // Add score
			PlayerScore->AddScore(ObjectSpawner->CheckHoldCollision(1, Clock->GetTicks()));
	if (gKeys[SDLK_s] == false) // Released (Prime the key to check for next press)
	{
		if (S_R_Primed == true)
		{
			// Add score
			PlayerScore->AddScore(ObjectSpawner->CheckReleaseCollision(1, Clock->GetTicks()));
			S_Primed = true;
			S_R_Primed = false;
		}
	}

	// D
	if (gKeys[SDLK_d] == true)
		// Pressed
		if (D_Primed == true)
		{
			// Add score
			PlayerScore->AddScore(ObjectSpawner->CheckCollision(3, Clock->GetTicks()));
			// Set player sprite state
			Player->SetPlayerState(PlayerSprite::Right, Clock->GetTicks());
			//if (Clock->GetTicks() < 3900) cout << "Ticks: " << Clock->GetTicks() - 132 << " | Type: 3" << endl; // Speed = 8
			//else cout << "Ticks: " << Clock->GetTicks() - 88 << " | Type: 3" << endl; // Speed = 12
			D_Primed = false;
			D_R_Primed = true;
		}
		// Held
		else // Add score
			PlayerScore->AddScore(ObjectSpawner->CheckHoldCollision(3, Clock->GetTicks()));
	if (gKeys[SDLK_d] == false) // Released (Prime the key to check for next press)
	{
		if (D_R_Primed == true)
		{
			// Add score
			PlayerScore->AddScore(ObjectSpawner->CheckReleaseCollision(3, Clock->GetTicks()));
			D_Primed = true;
			D_R_Primed = false;
		}
	}
}

void GameWorld::Update()
{
	// Spawn arrows
	running = ObjectSpawner->Update(Clock->GetTicks());
	vector<GameObject*> newArrows = ObjectSpawner->GetNewArrows();
	for (size_t i = 0; i < newArrows.size(); i++) window->AddGameObject(newArrows[i], 2);

	// Update player
	Player->Update(Clock->GetTicks(), PlayerScore->GetMultiplier());

	// Update game objects
	vector<vector<GameObject*>> gameObjects = window->GetGameObjectsToDraw();
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		for (size_t j = 0; j < gameObjects[i].size(); j++)
		{
			// Update game object
			gameObjects[i][j]->Update();

			// Check if Object needs to be destroyed (Memory Management)
			if (gameObjects[i][j]->Destroy)
			{
				GameObject* ObjectToDelete = window->RemoveGameObject(gameObjects[i][j]->GetRenderLayer(), gameObjects[i][j]->GetDrawIndex());
				if (ObjectToDelete->y + ObjectToDelete->height < 0) ObjectSpawner->ShowMissText(ObjectToDelete->x, Clock->GetTicks());
				ObjectSpawner->RemoveArrow(ObjectToDelete);
				delete ObjectToDelete;
			}
		}
	}

	// Tick Clock
	Clock->Tick();
	// Reset Tick Count
	Clock->ResetTickCount();
}

void GameWorld::Render()
{
	// Clear, Draw, and Render
	window->Clear();
	window->Draw();
	window->Render();

	// Reset Frame Count
	Clock->ResetFrameCount();
}
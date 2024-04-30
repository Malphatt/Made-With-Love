#include "Window.h"
#include "Logger.h"
#include "SDL_image.h"

Window::Window(string windowName, int x, int y, int width, int height, int logicalWidth, int logicalHeight, bool* gKeys)
{
	this->windowName = windowName;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->smallWindowWidth = width;
	this->smallWindowHeight = height;
	this->logicalWidth = logicalWidth;
	this->logicalHeight = logicalHeight;

	// Get the screen width and height
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	this->screenWidth = DM.w;
	this->screenHeight = DM.h;

	this->gameObjects = vector<vector<GameObject*>>();

	// Create the window
	this->window = SDL_CreateWindow(windowName.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//this->windowSurface = SDL_GetWindowSurface(window);
	this->icon = IMG_Load("Assets/icon.png");
	SDL_SetWindowIcon(window, icon);
	SDL_BlitSurface(icon, NULL, windowSurface, NULL);
	SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeight);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	toggleFullScreen();

	this->gKeys = gKeys;

	this->mouseX = 0;
	this->mouseY = 0;

	if (*IsLoggingEnabled == true)
		SDL_Log("%s Created window \"%s\"", Logger::GetTimestamp().c_str(), windowName.c_str());
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	if (*IsLoggingEnabled == true)
		SDL_Log("%s Destroyed window %s", Logger::GetTimestamp().c_str(), windowName.c_str());
}

void Window::SetWindowName(string windowName)
{
	this->windowName = windowName;
	SDL_SetWindowTitle(window, windowName.c_str());
}

void Window::SetResolution(int width, int height)
{
	this->width = width;
	this->height = height;

	SDL_SetWindowSize(window, width, height);
	windowSurface = SDL_GetWindowSurface(window);
	SDL_BlitSurface(icon, NULL, windowSurface, NULL);
	SDL_UpdateWindowSurface(window);

	if (*IsLoggingEnabled == true)
		SDL_Log("%s Set resolution of window %s to %dx%d", Logger::GetTimestamp().c_str(), windowName.c_str(), width, height);
}

void Window::HandleInput(SDL_Event* event)
{
	if (event->key.repeat == NULL)
	{
		switch (event->type)
		{
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym)
			{
			case SDLK_w:
				gKeys[SDLK_w] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s W key pressed", Logger::GetTimestamp().c_str());
				break;
			case SDLK_a:
				gKeys[SDLK_a] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s A key pressed", Logger::GetTimestamp().c_str());
				break;
			case SDLK_s:
				gKeys[SDLK_s] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s S key pressed", Logger::GetTimestamp().c_str());
				break;
			case SDLK_d:
				gKeys[SDLK_d] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s D key pressed", Logger::GetTimestamp().c_str());
				break;
			case SDLK_UP:
				gKeys[SDLK_w] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Up key pressed", Logger::GetTimestamp().c_str());
				break;
			case SDLK_LEFT:
				gKeys[SDLK_a] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Left key pressed", Logger::GetTimestamp().c_str());
				break;
			case SDLK_DOWN:
				gKeys[SDLK_s] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Down key pressed", Logger::GetTimestamp().c_str());
				break;
			case SDLK_RIGHT:
				gKeys[SDLK_d] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Right key pressed", Logger::GetTimestamp().c_str());
				break;
			case SDLK_ESCAPE:
				gKeys[SDLK_ESCAPE] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Escape key pressed", Logger::GetTimestamp().c_str());
				break;
			case SDLK_F11:
				toggleFullScreen();
				break;
			case SDLK_F12:
				toggleLogging();
				SDL_Log("%s Toggled logging", Logger::GetTimestamp().c_str());
				break;
			}
			break;

		case SDL_KEYUP:
			switch (event->key.keysym.sym)
			{
			case SDLK_w:
				gKeys[SDLK_w] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s W key released", Logger::GetTimestamp().c_str());
				break;
			case SDLK_a:
				gKeys[SDLK_a] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s A key released", Logger::GetTimestamp().c_str());
				break;
			case SDLK_s:
				gKeys[SDLK_s] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s S key released", Logger::GetTimestamp().c_str());
				break;
			case SDLK_d:
				gKeys[SDLK_d] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s D key released", Logger::GetTimestamp().c_str());
				break;
			case SDLK_UP:
				gKeys[SDLK_w] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Up key released", Logger::GetTimestamp().c_str());
				break;
			case SDLK_LEFT:
				gKeys[SDLK_a] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Left key released", Logger::GetTimestamp().c_str());
				break;
			case SDLK_DOWN:
				gKeys[SDLK_s] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Down key released", Logger::GetTimestamp().c_str());
				break;
			case SDLK_RIGHT:
				gKeys[SDLK_d] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Right key released", Logger::GetTimestamp().c_str());
				break;
			case SDLK_ESCAPE:
				gKeys[SDLK_ESCAPE] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Escape key released", Logger::GetTimestamp().c_str());
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event->button.button)
			{
			case SDL_BUTTON_LEFT:
				gKeys[SDL_BUTTON_LEFT] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Left mouse button pressed", Logger::GetTimestamp().c_str());
				break;
			case SDL_BUTTON_RIGHT:
				gKeys[SDL_BUTTON_RIGHT] = true;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Right mouse button pressed", Logger::GetTimestamp().c_str());
				break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (event->button.button)
			{
			case SDL_BUTTON_LEFT:
				gKeys[SDL_BUTTON_LEFT] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Left mouse button released", Logger::GetTimestamp().c_str());
				break;
			case SDL_BUTTON_RIGHT:
				gKeys[SDL_BUTTON_RIGHT] = false;
				if (*IsLoggingEnabled == true)
					SDL_Log("%s Right mouse button released", Logger::GetTimestamp().c_str());
				break;
			}
			break;

		case SDL_MOUSEMOTION:
			mouseX = event->motion.x;
			mouseY = event->motion.y;
			break;
		}
	}
}

size_t Window::AddGameObject(GameObject* gameObject, size_t renderLayer)
{
	// If the render layer is greater than the size of the vector, resize the vector
	if (renderLayer >= gameObjects.size()) gameObjects.resize(renderLayer + 1);
	// If the render layer is less than 0, set it to 0
	if (renderLayer < 0) renderLayer = 0;

	gameObjects[renderLayer].push_back(gameObject);
	gameObject->SetRenderLayer(renderLayer);
	gameObject->SetDrawIndex(gameObjects[renderLayer].size() - 1);

	return gameObjects[renderLayer].size() - 1;
}

GameObject* Window::RemoveGameObject(size_t renderLayer, size_t drawIndex)
{
	GameObject* gameObject = gameObjects[renderLayer][drawIndex];
	gameObjects[renderLayer].erase(gameObjects[renderLayer].begin() + drawIndex);

	for (size_t i = drawIndex; i < gameObjects[renderLayer].size(); i++)
		gameObjects[renderLayer][i]->SetDrawIndex(i);

	return gameObject;
}

void Window::Clear()
{
	SDL_SetRenderDrawColor(renderer, backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a);
	SDL_RenderClear(renderer);
}

void Window::Draw()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		for (size_t j = 0; j < gameObjects[i].size(); j++)
		{
			if (gameObjects[i][j]->Destroy == true)
			{
				RemoveGameObject(i, j);
				continue;
			}
			if (GameObjectIsOnScreen(i, j) == false) continue;
			gameObjects[i][j]->Draw(renderer);
		}
	}
}

void Window::Render()
{
	if (renderWindowContents == true)
	{
		SDL_RenderPresent(renderer);
	}
}

bool Window::GameObjectIsOnScreen(int renderLayer, int drawIndex)
{
	if (renderLayer < 0) return false;
	if (renderLayer >= gameObjects.size()) return false;
	if (drawIndex < 0) return false;
	if (drawIndex >= gameObjects[renderLayer].size()) return false;

	if (gameObjects[renderLayer][drawIndex]->x + gameObjects[renderLayer][drawIndex]->width < 0 || gameObjects[renderLayer][drawIndex]->x > logicalWidth) return false;
	if (gameObjects[renderLayer][drawIndex]->y + gameObjects[renderLayer][drawIndex]->height < 0 || gameObjects[renderLayer][drawIndex]->y > logicalHeight) return false;

	return true;
}

bool Window::GameObjectIsOnTopPercentScreen(int renderLayer, int drawIndex, double percent)
{
	if (renderLayer < 0) return false;
	if (renderLayer >= gameObjects.size()) return false;
	if (drawIndex < 0) return false;
	if (drawIndex >= gameObjects[renderLayer].size()) return false;

	if (gameObjects[renderLayer][drawIndex]->y < logicalHeight * percent) return true;
	else return false;
}

bool Window::GameObjectIsOnBottomPercentScreen(int renderLayer, int drawIndex, double percent)
{
	if (renderLayer < 0) return false;
	if (renderLayer >= gameObjects.size()) return false;
	if (drawIndex < 0) return false;
	if (drawIndex >= gameObjects[renderLayer].size()) return false;

	if (gameObjects[renderLayer][drawIndex]->y + gameObjects[renderLayer][drawIndex]->height > logicalHeight * percent) return true;
	else return false;
}

void Window::toggleFullScreen()
{
	if (fullScreen)
	{
		SDL_SetWindowFullscreen(window, 0);
		SetResolution(smallWindowWidth, smallWindowHeight);
	}
	else
	{
		SetResolution(screenWidth, screenHeight);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

	fullScreen = !fullScreen;
	if (*IsLoggingEnabled == true)
		SDL_Log("%s Toggled fullscreen mode", Logger::GetTimestamp().c_str());
}
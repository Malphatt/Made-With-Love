#include "Window.h"
#include "Logger.h"
#include "SDL_image.h"

Window::Window(string windowName, int x, int y, int width, int height, int logicalWidth, int logicalHeight, bool* gKeys)
{
	// Set the window properties
	this->windowName = windowName;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->smallWindowWidth = width;
	this->smallWindowHeight = height;
	this->logicalWidth = logicalWidth;
	this->logicalHeight = logicalHeight;

	this->gKeys = gKeys;

	this->mouseX = 0;
	this->mouseY = 0;

	// Get the screen width and height
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	this->screenWidth = DM.w;
	this->screenHeight = DM.h;

	// Create the window
	this->window = SDL_CreateWindow(windowName.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//this->windowSurface = SDL_GetWindowSurface(window);
	this->icon = IMG_Load("Assets/icon.png");
	SDL_SetWindowIcon(window, icon);
	SDL_BlitSurface(icon, NULL, windowSurface, NULL);
	SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeight);

	// Set the Blend Mode
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Set the window to fullscreen
	toggleFullScreen();

	// Log the creation of the window
	if (*IsLoggingEnabled == true)
		SDL_Log("%s Created window \"%s\"", Logger::GetTimestamp().c_str(), windowName.c_str());
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Log the destruction of the window
	if (*IsLoggingEnabled == true)
		SDL_Log("%s Destroyed window %s", Logger::GetTimestamp().c_str(), windowName.c_str());
}

void Window::SetWindowName(string windowName)
{
	// Set the window name
	this->windowName = windowName;
	SDL_SetWindowTitle(window, windowName.c_str());
}

void Window::SetResolution(int width, int height)
{
	// Update the window properties
	this->width = width;
	this->height = height;

	// Set the resolution of the window
	SDL_SetWindowSize(window, width, height);
	windowSurface = SDL_GetWindowSurface(window);
	SDL_BlitSurface(icon, NULL, windowSurface, NULL);
	SDL_UpdateWindowSurface(window);

	// Log the resolution change
	if (*IsLoggingEnabled == true)
		SDL_Log("%s Set resolution of window %s to %dx%d", Logger::GetTimestamp().c_str(), windowName.c_str(), width, height);
}

void Window::HandleInput(SDL_Event* event)
{
	if (event->key.repeat == NULL)
	{
		switch (event->type)
		{
		// If the event is a key press
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

		// If the event is a key release
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

		//// If the event is a mouse press (unused)
		//case SDL_MOUSEBUTTONDOWN:
		//	switch (event->button.button)
		//	{
		//	case SDL_BUTTON_LEFT:
		//		gKeys[SDL_BUTTON_LEFT] = true;
		//		if (*IsLoggingEnabled == true)
		//			SDL_Log("%s Left mouse button pressed", Logger::GetTimestamp().c_str());
		//		break;
		//	case SDL_BUTTON_RIGHT:
		//		gKeys[SDL_BUTTON_RIGHT] = true;
		//		if (*IsLoggingEnabled == true)
		//			SDL_Log("%s Right mouse button pressed", Logger::GetTimestamp().c_str());
		//		break;
		//	}
		//	break;

		//// If the event is a mouse release (unused)
		//case SDL_MOUSEBUTTONUP:
		//	switch (event->button.button)
		//	{
		//	case SDL_BUTTON_LEFT:
		//		gKeys[SDL_BUTTON_LEFT] = false;
		//		if (*IsLoggingEnabled == true)
		//			SDL_Log("%s Left mouse button released", Logger::GetTimestamp().c_str());
		//		break;
		//	case SDL_BUTTON_RIGHT:
		//		gKeys[SDL_BUTTON_RIGHT] = false;
		//		if (*IsLoggingEnabled == true)
		//			SDL_Log("%s Right mouse button released", Logger::GetTimestamp().c_str());
		//		break;
		//	}
		//	break;

		//// If the event is a mouse motion (unused)
		//case SDL_MOUSEMOTION:
		//	mouseX = event->motion.x;
		//	mouseY = event->motion.y;
		//	break;
		}
	}
}

size_t Window::AddGameObject(GameObject* gameObject, size_t renderLayer)
{
	// If the render layer is greater than the size of the vector, resize the vector
	if (renderLayer >= gameObjects.size()) gameObjects.resize(renderLayer + 1);
	// If the render layer is less than 0, set it to 0
	if (renderLayer < 0) renderLayer = 0;

	// Add the game object to the draw vector
	gameObjects[renderLayer].push_back(gameObject);
	gameObject->SetRenderLayer(renderLayer);
	gameObject->SetDrawIndex(gameObjects[renderLayer].size() - 1);

	return gameObjects[renderLayer].size() - 1;
}

GameObject* Window::RemoveGameObject(size_t renderLayer, size_t drawIndex)
{
	// If the render layer is greater than the size of the vector, return nullptr
	if (renderLayer >= gameObjects.size()) return nullptr;
	// If the render layer is less than 0, return nullptr
	if (renderLayer < 0) return nullptr;
	// If the draw index is greater than the size of the vector, return nullptr
	if (drawIndex >= gameObjects[renderLayer].size()) return nullptr;
	// If the draw index is less than 0, return nullptr
	if (drawIndex < 0) return nullptr;

	// Remove the game object from the draw vector
	GameObject* gameObject = gameObjects[renderLayer][drawIndex];
	gameObjects[renderLayer].erase(gameObjects[renderLayer].begin() + drawIndex);

	// Update the draw index of the game objects that appear after the removed game object in the vector
	for (size_t i = drawIndex; i < gameObjects[renderLayer].size(); i++)
		gameObjects[renderLayer][i]->SetDrawIndex(i);

	return gameObject;
}

void Window::Clear()
{
	// Clear the window
	SDL_SetRenderDrawColor(renderer, backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a);
	SDL_RenderClear(renderer);
}

void Window::Draw()
{
	// Draw the game objects within the window which are also in the draw vector
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		for (size_t j = 0; j < gameObjects[i].size(); j++)
		{
			if (gameObjects[i][j]->Destroy == true)
			{
				RemoveGameObject(i, j);
				continue;
			}

			// Check if the game object is not on the screen
			if (GameObjectIsOnScreen(i, j) == false) continue;
			
			gameObjects[i][j]->Draw(renderer);
		}
	}
}

void Window::Render()
{
	// Render the drawn output to the window
	if (renderWindowContents == true)
		SDL_RenderPresent(renderer);
}

bool Window::GameObjectIsOnScreen(int renderLayer, int drawIndex)
{
	// If the render layer is less than 0, return false
	if (renderLayer < 0) return false;
	// If the render layer is greater than the size of the vector, return false
	if (renderLayer >= gameObjects.size()) return false;
	// If the draw index is less than 0, return false
	if (drawIndex < 0) return false;
	// If the draw index is greater than the size of the vector, return false
	if (drawIndex >= gameObjects[renderLayer].size()) return false;

	// Check if the game object is on the screen
	if (gameObjects[renderLayer][drawIndex]->x + gameObjects[renderLayer][drawIndex]->width < 0 || gameObjects[renderLayer][drawIndex]->x > logicalWidth) return false;
	if (gameObjects[renderLayer][drawIndex]->y + gameObjects[renderLayer][drawIndex]->height < 0 || gameObjects[renderLayer][drawIndex]->y > logicalHeight) return false;

	return true;
}

bool Window::GameObjectIsOnTopPercentScreen(int renderLayer, int drawIndex, double percent)
{
	// If the render layer is less than 0, return false
	if (renderLayer < 0) return false;
	// If the render layer is greater than the size of the vector, return false
	if (renderLayer >= gameObjects.size()) return false;
	// If the draw index is less than 0, return false
	if (drawIndex < 0) return false;
	// If the draw index is greater than the size of the vector, return false
	if (drawIndex >= gameObjects[renderLayer].size()) return false;

	// Check if the game object is on the top percent of the screen
	if (gameObjects[renderLayer][drawIndex]->y < logicalHeight * percent) return true;
	else return false;
}

bool Window::GameObjectIsOnBottomPercentScreen(int renderLayer, int drawIndex, double percent)
{
	// If the render layer is less than 0, return false
	if (renderLayer < 0) return false;
	// If the render layer is greater than the size of the vector, return false
	if (renderLayer >= gameObjects.size()) return false;
	// If the draw index is less than 0, return false
	if (drawIndex < 0) return false;
	// If the draw index is greater than the size of the vector, return false
	if (drawIndex >= gameObjects[renderLayer].size()) return false;

	// Check if the game object is on the bottom percent of the screen
	if (gameObjects[renderLayer][drawIndex]->y + gameObjects[renderLayer][drawIndex]->height > logicalHeight * percent) return true;
	else return false;
}

void Window::toggleFullScreen()
{
	// Check if the window is in fullscreen mode
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

	// Toggle the fullscreen mode
	fullScreen = !fullScreen;

	// Log the fullscreen mode change
	if (*IsLoggingEnabled == true)
		SDL_Log("%s Toggled fullscreen mode", Logger::GetTimestamp().c_str());
}
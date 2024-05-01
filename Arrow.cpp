#include "Arrow.h"
#include "Sprite.h"

#include <SDL_image.h>

#include <vector>

Arrow::Arrow(bool* isLoggingEnabled, int x, int y, Vector2* startingVelocity, ArrowType* arrowType) : GO_Rect(isLoggingEnabled, "Arrow", x, y, 100, 100, new GO_Colour(255, 255, 0, 255), startingVelocity)
{
	this->startingVelocity = startingVelocity;
	this->Type = arrowType;
	this->SpriteTexture = nullptr;
	this->window = nullptr;
}

Arrow::~Arrow()
{
	SDL_DestroyTexture(this->SpriteTexture);

	for (int i = 0; i < tail.size(); i++) tail[i]->DestroyObject();
}

void Arrow::Init(Window* window)
{
	// Set the sprite path
	vector<string> sprites;
	switch (Type->Type)
	{
	case 0:
		sprites = { "Assets/Sprites/Arrows/ArrowLeft.png", "Assets/Sprites/Arrows/ArrowDown.png", "Assets/Sprites/Arrows/ArrowUp.png", "Assets/Sprites/Arrows/ArrowRight.png" };
		break;
	case 1:
		sprites = { "Assets/Sprites/Arrows/ArrowLeft.png", "Assets/Sprites/Arrows/ArrowDown.png", "Assets/Sprites/Arrows/ArrowUp.png", "Assets/Sprites/Arrows/ArrowRight.png" };
		break;
	case 2:
		sprites = { "Assets/Sprites/Arrows/ArrowLeft_Type2.png", "Assets/Sprites/Arrows/ArrowDown_Type2.png", "Assets/Sprites/Arrows/ArrowUp_Type2.png", "Assets/Sprites/Arrows/ArrowRight_Type2.png" };
		break;
	}

	// Set the sprite
	this->spritePath = sprites[Type->Direction];
	SDL_Surface* SpriteSurface = IMG_Load(this->spritePath.c_str());
	this->SpriteTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), SpriteSurface);
	SDL_FreeSurface(SpriteSurface);

	// Type 1 arrows have tails
	if (this->Type->Type == 1)
	{
		// Set the tail sprite paths
		vector<vector<string>> tailSprites =
		{
			{ "Assets/Sprites/Tails/TailLeft/TailLeft2.png", "Assets/Sprites/Tails/TailLeft/TailLeft1.png", "Assets/Sprites/Tails/TailLeft/TailLeft0.png" },
			{ "Assets/Sprites/Tails/TailDown/TailDown2.png", "Assets/Sprites/Tails/TailDown/TailDown1.png", "Assets/Sprites/Tails/TailDown/TailDown0.png" },
			{ "Assets/Sprites/Tails/TailUp/TailUp2.png", "Assets/Sprites/Tails/TailUp/TailUp1.png", "Assets/Sprites/Tails/TailUp/TailUp0.png" },
			{ "Assets/Sprites/Tails/TailRight/TailRight2.png", "Assets/Sprites/Tails/TailRight/TailRight1.png", "Assets/Sprites/Tails/TailRight/TailRight0.png" }
		};

		// Spawn the tail
		int tailLength = (Type->GetHoldDuration() * -velocity->y) + (rect.h / 2);
		for (int i = (rect.h / 2); i < tailLength; i += 5)
		{
			Sprite* tailSection = nullptr;
			if (i >= tailLength - 5)
			{
				tailSection = new Sprite(isLoggingEnabled, rect.x, rect.y + i, rect.w, 5, new Vector2(0, startingVelocity->y), "Assets/Sprites/Tails/TailEnd.png");
			}
			else if (i >= tailLength - 10)
			{
				tailSection = new Sprite(isLoggingEnabled, rect.x, rect.y + i, rect.w, 5, new Vector2(0, startingVelocity->y), tailSprites[Type->Direction][0]);
			}
			else if (i >= tailLength - 15)
			{
				tailSection = new Sprite(isLoggingEnabled, rect.x, rect.y + i, rect.w, 5, new Vector2(0, startingVelocity->y), tailSprites[Type->Direction][1]);
			}
			else
			{
				tailSection = new Sprite(isLoggingEnabled, rect.x, rect.y + i, rect.w, 5, new Vector2(0, startingVelocity->y), tailSprites[Type->Direction][2]);
			}

			// Init the tail section
			tailSection->Init(window->GetRenderer());
			// Add the tail section to the tail
			tail.push_back(tailSection);
			// Add the tail section to the window
			window->AddGameObject(tailSection, 1);
		}
	}

	this->window = window;
}

void Arrow::ChangeSpritePath(string spritePath)
{
	this->spritePath = spritePath;

	// Load the new sprite
	SDL_Surface* SpriteSurface = IMG_Load(this->spritePath.c_str());
	this->SpriteTexture = SDL_CreateTextureFromSurface(this->window->GetRenderer(), SpriteSurface);
	SDL_FreeSurface(SpriteSurface);
}

void Arrow::Hit()
{
	// Set the sprites to the hit sprites
	vector<string> sprites;
	switch (Type->Type)
	{
	case 0:
		sprites = { "Assets/Sprites/Arrows/ArrowLeft_Hit.png", "Assets/Sprites/Arrows/ArrowDown_Hit.png", "Assets/Sprites/Arrows/ArrowUp_Hit.png", "Assets/Sprites/Arrows/ArrowRight_Hit.png" };
		break;
	case 1:
		sprites = { "Assets/Sprites/Arrows/ArrowLeft_Hit.png", "Assets/Sprites/Arrows/ArrowDown_Hit.png", "Assets/Sprites/Arrows/ArrowUp_Hit.png", "Assets/Sprites/Arrows/ArrowRight_Hit.png" };
		break;
	case 2:
		sprites = { "Assets/Sprites/Arrows/ArrowLeft_Type2_Hit.png", "Assets/Sprites/Arrows/ArrowDown_Type2_Hit.png", "Assets/Sprites/Arrows/ArrowUp_Type2_Hit.png", "Assets/Sprites/Arrows/ArrowRight_Type2_Hit.png" };
		break;
	}

	// Change the sprite to the hit sprite
	this->spritePath = sprites[Type->Direction];
	SDL_Surface* SpriteSurface = IMG_Load(this->spritePath.c_str());
	this->SpriteTexture = SDL_CreateTextureFromSurface(this->window->GetRenderer(), SpriteSurface);
	SDL_FreeSurface(SpriteSurface);

	if (Type->Type == 1)
	{
		// Set the tail sprites to the hit tail sprites
		vector<vector<string>> tailSprites =
		{
			{ "Assets/Sprites/Tails/TailLeft/TailLeft2_Hit.png", "Assets/Sprites/Tails/TailLeft/TailLeft1_Hit.png", "Assets/Sprites/Tails/TailLeft/TailLeft0_Hit.png" },
			{ "Assets/Sprites/Tails/TailDown/TailDown2_Hit.png", "Assets/Sprites/Tails/TailDown/TailDown1_Hit.png", "Assets/Sprites/Tails/TailDown/TailDown0_Hit.png" },
			{ "Assets/Sprites/Tails/TailUp/TailUp2_Hit.png", "Assets/Sprites/Tails/TailUp/TailUp1_Hit.png", "Assets/Sprites/Tails/TailUp/TailUp0_Hit.png" },
			{ "Assets/Sprites/Tails/TailRight/TailRight2_Hit.png", "Assets/Sprites/Tails/TailRight/TailRight1_Hit.png", "Assets/Sprites/Tails/TailRight/TailRight0_Hit.png" }
		};

		// Change the tail sprites to the hit tail sprites
		for (int i = 0; i < tail.size(); i++)
		{
			if (tail[i]->Destroy) continue;
			if (i >= tail.size() - 1)
			{
			}
			else if (i >= tail.size() - 2)
			{
				tail[i]->ChangeSpritePath(tailSprites[Type->Direction][0]);
			}
			else if (i >= tail.size() - 3)
			{
				tail[i]->ChangeSpritePath(tailSprites[Type->Direction][1]);
			}
			else
			{
				tail[i]->ChangeSpritePath(tailSprites[Type->Direction][2]);
			}
		}
	}
}

void Arrow::Freeze(int Ticks)
{
	// Set the velocity to 0 and set the start hold ticks
	this->velocity->y = 0;
	this->StartHoldTicks = Ticks;
}

double Arrow::Unfreeze(int Ticks)
{
	// Set the velocity to the starting velocity and update the held for
	this->velocity->y = startingVelocity->y;
	UpdateHeldFor(Ticks);

	// Return the accuracy as a multiple of 0.1
	return trunc(static_cast<double>(this->HeldFor) / this->Type->GetHoldDuration() * 10) / 10;
}

void Arrow::UpdateHeldFor(int Ticks)
{
	// Update the held for
	this->HeldFor = Ticks - this->StartHoldTicks;
	if (this->HeldFor > this->Type->GetHoldDuration())
		this->HeldFor = this->Type->GetHoldDuration();

	// Update the tail if the arrow is a type 1 arrow
	if (this->Type->Type == 1) UpdateTail(Ticks);
}

void Arrow::UpdateTail(int Ticks)
{
	// Calculate the tail length
	int tailLength = (Type->GetHoldDuration() * -velocity->y) + (rect.h / 2);

	// Update the tail
	for (int i = 0; i < tail.size(); i++)
	{
		// If the tail section is destroyed, skip it
		if (tail[i]->Destroy) continue;
		// If the tail section section is above the arrow, destroy it
		if (tail[i]->y < rect.y + (rect.h / 2))
		{
			tail[i]->DestroyObject();
			tail.erase(tail.begin() + i);
		}
	}
}

void Arrow::Draw(SDL_Renderer* renderer)
{
	// Draw the tail
	SDL_RenderCopy(renderer, this->SpriteTexture, NULL, &rect);
}
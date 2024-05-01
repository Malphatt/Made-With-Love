#include "AnimatedSprite.h"
#include "Logger.h"

#include <string>
#include <SDL_image.h>

AnimatedSprite::AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, string spritePathPrefix, int frameCount, int animationSpeed) : Sprite(isLoggingEnabled, "AnimatedSprite", x, y, w, h, spritePathPrefix + ".png")
{
	this->spritePathPrefix = spritePathPrefix;

	this->animationSpeed = animationSpeed;
	this->startFrameTicks = 0;
	this->totalAnimationTicks = 0;
	this->currentFrame = 0;

	this->frameCount = frameCount;
	this->isAnimating = false;

	this->loop = false;
}

AnimatedSprite::AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, Vector2* velocity, string spritePathPrefix, int frameCount, int animationSpeed) : Sprite(isLoggingEnabled, "AnimatedSprite", x, y, w, h, velocity, spritePathPrefix + ".png")
{
	this->spritePathPrefix = spritePathPrefix;

	this->animationSpeed = animationSpeed;
	this->startFrameTicks = 0;
	this->totalAnimationTicks = 0;
	this->currentFrame = 0;

	this->frameCount = frameCount;
	this->isAnimating = false;

	this->loop = false;
}

AnimatedSprite::AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, string spritePathPrefix, int frameCount, int animationSpeed, bool loop) : Sprite(isLoggingEnabled, "AnimatedSprite", x, y, w, h, spritePathPrefix + ".png")
{
	this->spritePathPrefix = spritePathPrefix;

	this->animationSpeed = animationSpeed;
	this->startFrameTicks = 0;
	this->totalAnimationTicks = 0;
	this->currentFrame = 0;

	this->frameCount = frameCount;
	this->isAnimating = false;

	this->loop = loop;
}

AnimatedSprite::AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, Vector2* velocity, string spritePathPrefix, int frameCount, int animationSpeed, bool loop) : Sprite(isLoggingEnabled, "AnimatedSprite", x, y, w, h, velocity, spritePathPrefix + ".png")
{
	this->spritePathPrefix = spritePathPrefix;

	this->animationSpeed = animationSpeed;
	this->startFrameTicks = 0;
	this->totalAnimationTicks = 0;
	this->currentFrame = 0;

	this->frameCount = frameCount;
	this->isAnimating = false;

	this->loop = loop;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Init(SDL_Renderer* renderer)
{
	Sprite::Init(renderer);

	// Load all the frames of the animation
	for (int i = 0; i < frameCount; i++)
	{
		string path = spritePathPrefix + to_string(i) + ".png";
		SDL_Surface* SpriteSurface = IMG_Load(path.c_str());
		this->animationFrames.push_back(SDL_CreateTextureFromSurface(this->renderer, SpriteSurface));
		SDL_FreeSurface(SpriteSurface);
	}
}

void AnimatedSprite::ChangeSpritePath()
{
	// Change the sprite to the current frame
	this->SpriteTexture = this->animationFrames[this->currentFrame];
}

void AnimatedSprite::Draw(SDL_Renderer* renderer)
{
	// Draw the current frame
	Sprite::Draw(renderer);
}

void AnimatedSprite::StartAnimation(int Ticks)
{
	// Start the animation from the beginning
	this->isAnimating = true;
	this->startFrameTicks = Ticks;

	// Log the start
	if (*isLoggingEnabled)
		SDL_Log("%s Started Animation (%p)", Logger::GetTimestamp().c_str(), this);
}

void AnimatedSprite::PauseAnimation()
{
	this->isAnimating = false;
}

void AnimatedSprite::ResumeAnimation(int Ticks)
{
	// Resume the animation from the current frame
	this->isAnimating = true;
	this->startFrameTicks = Ticks - this->totalAnimationTicks;
}

void AnimatedSprite::StopAnimation()
{
	// Stop the animation and reset the current frame
	this->currentFrame = 0;
	this->isAnimating = false;

	// Log the stop
	if (*isLoggingEnabled)
		SDL_Log("%s Stopped Animation (%p)", Logger::GetTimestamp().c_str(), this);
}

void AnimatedSprite::UpdateAnimation(int Ticks)
{
	// Check if the animation is playing and the object is not destroyed
	if (this->isAnimating && !this->Destroy)
	{
		// Calculate the total ticks the animation has been playing for
		this->totalAnimationTicks = Ticks - this->startFrameTicks;

		// Calculate the current frame
		int newFrame = trunc(this->totalAnimationTicks / this->animationSpeed);

		// Check if the frame has changed
		if (newFrame != this->currentFrame)
		{
			// Check if the animation has reached the end
			if (newFrame >= this->animationFrames.size())
			{
				// Check if the animation should loop
				if (this->loop)
				{
					// Restart the animation
					this->currentFrame = 1;
					this->startFrameTicks = Ticks;
					UpdateAnimation(Ticks);
				}
				// Stop the animation
				else StopAnimation();
			}
			// Change the frame
			else
			{
				this->currentFrame = newFrame;
				ChangeSpritePath();
			}
		}
	}
}
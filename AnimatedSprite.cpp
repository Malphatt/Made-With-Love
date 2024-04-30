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
	this->SpriteTexture = this->animationFrames[this->currentFrame];
}

void AnimatedSprite::Draw(SDL_Renderer* renderer)
{
	Sprite::Draw(renderer);
}

void AnimatedSprite::StartAnimation(int Ticks)
{
	this->isAnimating = true;
	this->startFrameTicks = Ticks;

	if (*isLoggingEnabled)
		SDL_Log("%s Started Animation (%p)", Logger::GetTimestamp().c_str(), this);
}

void AnimatedSprite::PauseAnimation()
{
	this->isAnimating = false;
}

void AnimatedSprite::ResumeAnimation(int Ticks)
{
	this->isAnimating = true;
	this->startFrameTicks = Ticks - this->totalAnimationTicks;
}

void AnimatedSprite::StopAnimation()
{
	this->currentFrame = 0;
	this->isAnimating = false;

	if (*isLoggingEnabled)
		SDL_Log("%s Stopped Animation (%p)", Logger::GetTimestamp().c_str(), this);
}

void AnimatedSprite::UpdateAnimation(int Ticks)
{
	if (this->isAnimating && !this->Destroy)
	{
		this->totalAnimationTicks = Ticks - this->startFrameTicks;

		int newFrame = trunc(this->totalAnimationTicks / this->animationSpeed);

		if (newFrame != this->currentFrame)
		{
			if (newFrame >= this->animationFrames.size())
			{
				if (this->loop)
				{
					this->currentFrame = 1;
					this->startFrameTicks = Ticks;
					UpdateAnimation(Ticks);
				}
				else StopAnimation();
			}
			else
			{
				this->currentFrame = newFrame;
				ChangeSpritePath();
			}
		}
	}
}
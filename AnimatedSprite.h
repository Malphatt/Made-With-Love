#include "Sprite.h"

#ifndef AnimatedSprite_h
#define AnimatedSprite_h

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, string spritePathPrefix, int frameCount, int animationSpeed);
	AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, Vector2* velocity, string spritePathPrefix, int frameCount, int animationSpeed);
	AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, string spritePathPrefix, int frameCount, int animationSpeed, bool loop);
	AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, Vector2* velocity, string spritePathPrefix, int frameCount, int animationSpeed, bool loop);
	~AnimatedSprite();

	void Init(SDL_Renderer* renderer);

	void ChangeSpritePath();

	void Draw(SDL_Renderer* renderer);

	void StartAnimation(int Ticks);
	void PauseAnimation();
	void ResumeAnimation(int Ticks);
	void StopAnimation();

	void UpdateAnimation(int Ticks);
private:
	string spritePathPrefix;
	vector<SDL_Texture*> animationFrames;

	int animationSpeed = 1; // speed of the animation in ticks per frame
	int startFrameTicks; // ticks when the animation started
	int totalAnimationTicks; // ticks since the animation started
	int currentFrame; // index of the current frame

	int frameCount; // number of frames in the animation
	bool isAnimating; // is the animation playing

	bool loop;
};

#endif // !AnimatedSprite_h





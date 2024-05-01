#include "Sprite.h"

#ifndef AnimatedSprite_h
#define AnimatedSprite_h

class AnimatedSprite : public Sprite
{
public:
	/// <summary>
	/// Constructor for AnimatedSprite
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="spritePathPrefix"></param>
	/// <param name="frameCount"></param>
	/// <param name="animationSpeed"></param>
	AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, string spritePathPrefix, int frameCount, int animationSpeed);
	/// <summary>
	/// Constructor for AnimatedSprite with velocity
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="velocity"></param>
	/// <param name="spritePathPrefix"></param>
	/// <param name="frameCount"></param>
	/// <param name="animationSpeed"></param>
	AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, Vector2* velocity, string spritePathPrefix, int frameCount, int animationSpeed);
	/// <summary>
	/// Constructor for AnimatedSprite (with loop)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="spritePathPrefix"></param>
	/// <param name="frameCount"></param>
	/// <param name="animationSpeed"></param>
	/// <param name="loop"></param>
	AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, string spritePathPrefix, int frameCount, int animationSpeed, bool loop);
	/// <summary>
	/// Constructor for AnimatedSprite with velocity (with loop)
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="velocity"></param>
	/// <param name="spritePathPrefix"></param>
	/// <param name="frameCount"></param>
	/// <param name="animationSpeed"></param>
	/// <param name="loop"></param>
	AnimatedSprite(bool* isLoggingEnabled, int x, int y, int w, int h, Vector2* velocity, string spritePathPrefix, int frameCount, int animationSpeed, bool loop);
	/// <summary>
	/// Destructor for AnimatedSprite
	/// </summary>
	~AnimatedSprite();

	/// <summary>
	/// Initializes the AnimatedSprite
	/// </summary>
	/// <param name="renderer"></param>
	void Init(SDL_Renderer* renderer);

	/// <summary>
	/// Changes the sprite path
	/// </summary>
	void ChangeSpritePath();

	/// <summary>
	/// Draws the AnimatedSprite
	/// </summary>
	/// <param name="renderer"></param>
	void Draw(SDL_Renderer* renderer);

	/// <summary>
	/// Starts the animation
	/// </summary>
	/// <param name="Ticks"></param>
	void StartAnimation(int Ticks);
	/// <summary>
	/// Pauses the animation
	/// </summary>
	void PauseAnimation();
	/// <summary>
	/// Resumes the animation
	/// </summary>
	/// <param name="Ticks"></param>
	void ResumeAnimation(int Ticks);
	/// <summary>
	/// Stops the animation
	/// </summary>
	void StopAnimation();

	/// <summary>
	/// Updates the animation
	/// </summary>
	/// <param name="Ticks"></param>
	void UpdateAnimation(int Ticks);
private:
	string spritePathPrefix; // prefix of the sprite path
	vector<SDL_Texture*> animationFrames; // vector of textures for the animation frames

	int animationSpeed = 1; // speed of the animation in ticks per frame
	int startFrameTicks; // ticks when the animation started
	int totalAnimationTicks; // ticks since the animation started
	int currentFrame; // index of the current frame

	int frameCount; // number of frames in the animation
	bool isAnimating; // is the animation playing

	bool loop; // should the animation loop
};

#endif // !AnimatedSprite_h





#include "Sprite.h"

#ifndef PlayerSprite_h
#define PlayerSprite_h


class PlayerSprite : public Sprite
{
public:
	/// <summary>
	/// Constructor for the PlayerSprite class
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	PlayerSprite(bool* isLoggingEnabled, int x, int y);
	/// <summary>
	/// Destructor for the PlayerSprite class
	/// </summary>
	~PlayerSprite();

	// Enum for the player state
	enum State
	{
		Idle,
		Left,
		Down,
		Up,
		Right
	};

	/// <summary>
	/// Updates the player sprite (animation)
	/// </summary>
	/// <param name="Ticks"></param>
	/// <param name="combo"></param>
	void Update(int Ticks, int combo);
	/// <summary>
	/// Sets the player state
	/// </summary>
	/// <param name=""></param>
	/// <param name="Ticks"></param>
	void SetPlayerState(enum State playerState, int Ticks);
private:
	enum State State = Idle; // The current state of the player
	enum State previousState = Idle; // The previous state of the player

	bool StateChanged = false; // If the state has changed
	int StateChangeTicks = 0; // The ticks when the state changed
	int ticksSinceStateChange = 0; // The ticks since the state has changed
	int maxTicksSinceStateChange = 150; // The max ticks since the state has changed

	int ticksSinceLastIdleFrame = 0; // The ticks since the last idle frame
	int currentIdleFrame = 0; // The current idle frame
	int totalIdleFrames = 4; // The total idle frames
	int idleFrameRate = 12; // The idle frame rate
};

#endif // !PlayerSprite_h
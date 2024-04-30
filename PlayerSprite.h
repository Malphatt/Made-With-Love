#include "Sprite.h"

#ifndef PlayerSprite_h
#define PlayerSprite_h


class PlayerSprite : public Sprite
{
public:
	PlayerSprite(bool* isLoggingEnabled, int x, int y);
	~PlayerSprite();

	enum State
	{
		Idle,
		Left,
		Down,
		Up,
		Right
	};

	void Update(int Ticks, int combo);
	void SetPlayerState(enum State playerState, int Ticks);

private:
	enum State State = Idle;
	enum State previousState = Idle;

	bool StateChanged = false;
	int StateChangeTicks = 0;
	int ticksSinceStateChange = 0;
	int maxTicksSinceStateChange = 150;

	int ticksSinceLastIdleFrame = 0;
	int currentIdleFrame = 0;
	int totalIdleFrames = 4;
	int idleFrameRate = 12; // 75 BPM
};

#endif // !PlayerSprite_h
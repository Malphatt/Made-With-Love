#include "PlayerSprite.h"
#include <string>

PlayerSprite::PlayerSprite(bool* isLoggingEnabled, int x, int y) : Sprite(isLoggingEnabled, "PlayerSprite", x, y, 450, 600, "Assets/Sprites/Player/Idle/PlayerSprite_Idle0.png")
{
}

PlayerSprite::~PlayerSprite()
{
}

void PlayerSprite::Update(int Ticks, int combo)
{
	this->ticksSinceStateChange = Ticks - this->StateChangeTicks;

	if (this->ticksSinceStateChange > this->maxTicksSinceStateChange) SetPlayerState(Idle, Ticks);

	// Update the idle animation (even if the player is moving, this is so the idle animation syncs up with the music)
	if (this->ticksSinceLastIdleFrame >= this->idleFrameRate)
	{
		this->ticksSinceLastIdleFrame = 0;
		this->currentIdleFrame++;
		if (this->currentIdleFrame >= this->totalIdleFrames) this->currentIdleFrame = 0;
	}
	else
	{
		this->ticksSinceLastIdleFrame++;
	}

	switch (this->State)
	{
	case Idle:
			this->ChangeSpritePath("Assets/Sprites/Player/Idle/PlayerSprite_Idle" + to_string(this->currentIdleFrame) + ".png");
		break;
	case Left:
		if (this->StateChanged) this->ChangeSpritePath("Assets/Sprites/Player/Left/PlayerSprite_Left" + to_string(combo - 1) + ".png");
		break;
	case Down:
		if (this->StateChanged) this->ChangeSpritePath("Assets/Sprites/Player/Down/PlayerSprite_Down" + to_string(combo - 1) + ".png");
		break;
	case Up:
		if (this->StateChanged) this->ChangeSpritePath("Assets/Sprites/Player/Up/PlayerSprite_Up" + to_string(combo - 1) + ".png");
		break;
	case Right:
		if (this->StateChanged) this->ChangeSpritePath("Assets/Sprites/Player/Right/PlayerSprite_Right" + to_string(combo - 1) + ".png");
		break;
	}

	this->StateChanged = false;
}

void PlayerSprite::SetPlayerState(enum State playerState, int Ticks)
{
	this->previousState = this->State;
	this->StateChanged = true;
	this->StateChangeTicks = Ticks;

	switch (playerState)
	{
	case Idle:
		this->State = playerState;
		break;
	case Left:
		if (this->previousState == Left) this->State = Right;
		else this->State = playerState;
		break;
	case Down:
		if (this->previousState == Down) this->State = Up;
		else this->State = playerState;
		break;
	case Up:
		if (this->previousState == Up) this->State = Down;
		else this->State = playerState;
		break;
	case Right:
		if (this->previousState == Right) this->State = Left;
		else this->State = playerState;
		break;
	}
}
#include "Score.h"
#include <string>

Score::Score()
{
	this->score = 0;
	this->concurrentScore = 0;
	this->multiplier = 1;

	this->ScoreText = nullptr;
	this->ComboSprite = nullptr;
}

Score::~Score()
{
	delete this->ScoreText;
	for (int i = 0; i < ScoreNumbers.size(); i++)
	{
		delete ScoreNumbers[i];
	}
}

void Score::Init(Window* window)
{
	this->ComboSprite = new Sprite(window->IsLoggingEnabled, window->logicalWidth / 2 - 150, 29, 100, 100, "Assets/Sprites/Score/Combo1.png");
	this->ComboSprite->Init(window->GetRenderer());
	window->AddGameObject(this->ComboSprite, 3);

	this->ScoreText = new Sprite(window->IsLoggingEnabled, this->ComboSprite->x + this->ComboSprite->GetWidth() + 24, 24, 200, 60, "Assets/Sprites/Score/ScoreText.png");
	this->ScoreText->Init(window->GetRenderer());
	window->AddGameObject(this->ScoreText, 3);
	for (int i = ScoreNumbers.size() - 1; i >= 0; i--)
	{
		ScoreNumbers[i] = new Sprite(window->IsLoggingEnabled, ScoreText->x + (i * 50), ScoreText->y + ScoreText->GetHeight(), 50, 50, "Assets/Sprites/Score/0.png");
		ScoreNumbers[i]->Init(window->GetRenderer());
		window->AddGameObject(ScoreNumbers[i], 3);
	}
}

void Score::SetSpritesLocation(int x, int y)
{
	this->ComboSprite->SetConstructs(x, y, this->ComboSprite->GetWidth(), this->ComboSprite->GetHeight());
	this->ScoreText->SetConstructs(x + this->ComboSprite->GetWidth() + 24, y, this->ScoreText->GetWidth(), this->ScoreText->GetHeight());
	for (int i = 0; i < ScoreNumbers.size(); i++)
	{
		ScoreNumbers[i]->SetConstructs(x + (i * ScoreNumbers[i]->GetWidth()), y + this->ScoreText->GetHeight(), ScoreNumbers[i]->GetWidth(), ScoreNumbers[i]->GetHeight());
	}
}

void Score::AddScore(int value)
{
	if (value == -1) return;

	if (value == 0)
	{
		this->concurrentScore = 0;
		ResetMultiplier();
	}

	this->score += value * this->multiplier;
	this->concurrentScore += value;

	if (this->concurrentScore / 1000 >= this->multiplier && this->multiplier < this->maxMultiplier)
		IncreaseMultiplier();

	UpdateSprites();
}

void Score::UpdateSprites()
{
	string scoreString = to_string(this->score);
	for (int i = ScoreNumbers.size() - 1; i >= 0; i--)
	{
		int ScoreStringIndex = scoreString.length() - (ScoreNumbers.size() - i);
		if (ScoreStringIndex < 0) ScoreNumbers[i]->ChangeSpritePath("Assets/Sprites/Score/0.png");
		else ScoreNumbers[i]->ChangeSpritePath("Assets/Sprites/Score/" + scoreString.substr(ScoreStringIndex, 1) + ".png");
	}

	ComboSprite->ChangeSpritePath("Assets/Sprites/Score/Combo" + to_string(this->multiplier) + ".png");
}
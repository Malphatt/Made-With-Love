#include "Window.h"

#include "Sprite.h"

#include <vector>

#ifndef Score_h
#define Score_h

class Score
{
public:
	Score();
	~Score();

	void Init(Window* window);

	void SetSpritesLocation(int x, int y);

	int GetScore() const { return score; }
	void AddScore(int score);
	void ResetScore() { this->score = 0; }

	int GetMultiplier() const { return multiplier; }

	Sprite* ScoreText;
	vector<Sprite*> ScoreNumbers = vector<Sprite*>(6);
	Sprite* ComboSprite;
private:
	void IncreaseMultiplier() { this->multiplier++; }
	void ResetMultiplier() { this->multiplier = 1; }

	void UpdateSprites();

	int score;
	int concurrentScore;
	int multiplier;
	int maxMultiplier = 8;
};

#endif // !Score_h


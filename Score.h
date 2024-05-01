#include "Window.h"

#include "Sprite.h"

#include <vector>

#ifndef Score_h
#define Score_h

class Score
{
public:
	/// <summary>
	/// Constructor for the Score class
	/// </summary>
	Score();
	/// <summary>
	/// Destructor for the Score class
	/// </summary>
	~Score();

	/// <summary>
	/// Initializes the score class
	/// </summary>
	/// <param name="window"></param>
	void Init(Window* window);

	/// <summary>
	/// Sets the location of the score sprites
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void SetSpritesLocation(int x, int y);

	/// <summary>
	/// Returns the current score
	/// </summary>
	/// <returns>int</returns>
	int GetScore() const { return score; }
	/// <summary>
	/// Adds a score to the current score
	/// </summary>
	/// <param name="score"></param>
	void AddScore(int score);
	/// <summary>
	/// Resets the score to 0
	/// </summary>
	void ResetScore() { this->score = 0; }

	/// <summary>
	/// Returns the current multiplier
	/// </summary>
	/// <returns>int</returns>
	int GetMultiplier() const { return multiplier; }

	Sprite* ScoreText; // Score text sprite
	vector<Sprite*> ScoreNumbers = vector<Sprite*>(6); // Score number sprites
	Sprite* ComboSprite; // Combo sprite
private:
	/// <summary>
	/// Increases the multiplier by 1
	/// </summary>
	void IncreaseMultiplier() { this->multiplier++; }
	/// <summary>
	/// Resets the multiplier to 1
	/// </summary>
	void ResetMultiplier() { this->multiplier = 1; }

	/// <summary>
	/// Updates the sprites to display the current score
	/// </summary>
	void UpdateSprites();

	int score; // Current score
	int concurrentScore; // Concurrent score without any misses
	int multiplier; // Current multiplier
	int maxMultiplier = 8; // Maximum multiplier
};

#endif // !Score_h


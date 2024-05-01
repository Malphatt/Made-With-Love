#include "Window.h"

#include "GO_Rect.h"
#include "Sprite.h"
#include "ArrowType.h"
#include "Column.h"

#include <vector>

#ifndef Arrow_h
#define Arrow_h

class Arrow : public GO_Rect
{
public:
	/// <summary>
	/// Constructor for Arrow
	/// </summary>
	/// <param name="isLoggingEnabled"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="startingVelocity"></param>
	/// <param name="type"></param>
	Arrow(bool* isLoggingEnabled, int x, int y, Vector2* startingVelocity, ArrowType* type);
	/// <summary>
	/// Destructor for Arrow
	/// </summary>
	~Arrow();

	/// <summary>
	/// Initializes the Arrow
	/// </summary>
	/// <param name="window"></param>
	virtual void Init(Window* window);

	/// <summary>
	/// Changes the sprite path of the Arrow
	/// </summary>
	/// <param name="spritePath"></param>
	void ChangeSpritePath(string spritePath);

	/// <summary>
	/// Declares the Arrow as hit
	/// </summary>
	void Hit();

	/// <summary>
	/// Freezes the Arrow's position
	/// </summary>
	/// <param name="Ticks"></param>
	void Freeze(int Ticks);
	/// <summary>
	/// Unfreezes the Arrow's position and returns the worth of the Arrow
	/// </summary>
	/// <param name="Ticks"></param>
	/// <returns>double</returns>
	double Unfreeze(int Ticks);

	/// <summary>
	/// Updates the length of time the Arrow has been held for
	/// </summary>
	/// <param name="Ticks"></param>
	void UpdateHeldFor(int Ticks);
	/// <summary>
	/// Returns the length of time the Arrow has been held for
	/// </summary>
	/// <returns>int</returns>
	int GetHeldFor() const { return HeldFor; }

	/// <summary>
	/// Updates the Arrow's tail
	/// </summary>
	/// <param name="Ticks"></param>
	void UpdateTail(int Ticks);

	/// <summary>
	/// Draws the Arrow
	/// </summary>
	/// <param name="renderer"></param>
	void Draw(SDL_Renderer* renderer);

	/// <summary>
	/// Returns the worth of the Arrow
	/// </summary>
	/// <returns>int</returns>
	int GetWorth() const { return 100 * Type->Worth; }

	ArrowType* Type; // The type of Arrow
	SDL_Texture* SpriteTexture; // The texture of the Arrow's sprite

	double HitAccuracy = 0; // The accuracy of the hit
private:
	Window* window; // The window the Arrow is in

	int StartHoldTicks = 0; // The starting ticks of the hold
	int HeldFor = 0; // The length of time the Arrow has been held for

	Vector2* startingVelocity; // The starting velocity of the Arrow
	string spritePath; // The path of the Arrow's sprite

	vector<Sprite*> tail; // The Arrow's tail sprites
};
#endif // !Arrow_h

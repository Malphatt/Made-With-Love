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
	Arrow(bool* isLoggingEnabled, int x, int y, Vector2* startingVelocity, ArrowType* type);
	~Arrow();

	virtual void Init(Window* window);

	void ChangeSpritePath(string spritePath);

	void Hit();

	void Freeze(int Ticks);
	double Unfreeze(int Ticks);

	void UpdateHeldFor(int Ticks);
	int GetHeldFor() const { return HeldFor; }

	void UpdateTail(int Ticks);

	void Draw(SDL_Renderer* renderer);

	int GetWorth() const { return 100 * Type->Worth; }

	ArrowType* Type;
	SDL_Texture* SpriteTexture;

	double HitAccuracy = 0;
private:
	Window* window;

	int StartHoldTicks = 0;
	int HeldFor = 0;

	Vector2* startingVelocity;
	string spritePath;

	vector<Sprite*> tail;
};
#endif // !Arrow_h

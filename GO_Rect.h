#include "SDL.h"
#include "GameObject.h"

#ifndef GO_Rect_h
#define GO_Rect_h

class GO_Rect : public GameObject
{
public:
	GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height);
	GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour);
	GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height, Vector2* velocity);
	GO_Rect(bool* isLoggingEnabled, int x, int y, int width, int height, GO_Colour* colour, Vector2* velocity);

	~GO_Rect();

	GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height);
	GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height, GO_Colour* colour);
	GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height, Vector2* velocity);
	GO_Rect(bool* isLoggingEnabled, string gameObjectType, int x, int y, int width, int height, GO_Colour* colour, Vector2* velocity);

	void MovePosition(int x_dir, int y_dir);
	void SetConstructs(int new_x, int new_y, int new_width, int new_height);

	void SetHeight(int new_height) { this->rect.h = new_height; this->height = new_height; }
	int GetHeight() const { return rect.h; }
	void SetWidth(int new_width) { this->rect.w = new_width; this->width = new_width; }
	int GetWidth() const { return rect.w; }

	void Update();
	void Draw(SDL_Renderer* renderer);
protected:
	SDL_Rect rect;
};

#endif // GO_Rect_h
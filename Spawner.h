#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Window.h"
#include "Timer.h"
#include "Score.h"

#include "GameObject.h"
#include "Arrow.h"
#include "ArrowType.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Column.h"

#include <vector>

#ifndef Spawner_h
#define Spawner_h

class Spawner
{
public:
	Spawner(Window* window, Timer* Clock, Score* PlayerScore);
	~Spawner();

	bool Init();

	void Seek(int totalTicks);

	void CheckDesync(int totalTicks);
	void SwitchSong(int songNumber);

	bool Update(int totalTicks);

	void ShowMissText(int x, int Ticks);

	vector<GameObject*> GetNewArrows();
	int CheckCollision(int direction, int Ticks);
	int CheckHoldCollision(int direction, int Ticks);
	int CheckReleaseCollision(int direction, int Ticks);

	void RemoveArrow(GameObject* arrow);
private:
	void SpawnArrow(SDL_Renderer* renderer, int Ticks, ArrowType* arrowType);
	void SpawnBONUSArrow(SDL_Renderer* renderer, int Ticks, ArrowType* arrowType);

	Arrow* GetCollision(int direction, int Ticks);
	int collisionTicks = 0;
	int ticksSinceLastCollision = 0;

	int songNumber = 0;

	Window* window;
	Timer* Clock;
	Score* PlayerScore;

	vector<GameObject*> newArrows;

	// Game Objects
	// Foreground Fade
	GameObject* ForegroundFade;
	
	// Splash Screen
	AnimatedSprite* SplashImage;
	AnimatedSprite* SplashText;
	GameObject* SplashBackground;

	// Song Info
	Sprite* SongText;
	AnimatedSprite* SongNote;

	// Arrows
	Sprite* LeftArrow;
	Sprite* DownArrow;
	Sprite* UpArrow;
	Sprite* RightArrow;

	AnimatedSprite* LeftArrowAnim;
	AnimatedSprite* DownArrowAnim;
	AnimatedSprite* UpArrowAnim;
	AnimatedSprite* RightArrowAnim;

	Arrow* LastLeftArrow;
	Arrow* LastDownArrow;
	Arrow* LastUpArrow;
	Arrow* LastRightArrow;

	// Hit Text
	vector<AnimatedSprite*> MissText;
	vector<AnimatedSprite*> OkText;
	vector<AnimatedSprite*> GoodText;
	vector<AnimatedSprite*> NiceText;
	vector<AnimatedSprite*> GreatText;
	AnimatedSprite* PerfectText;

	// Type 2 Columns
	vector<Column*> Type2Columns;

	// Type 2 Arrows
	vector<Arrow*> Type2Arrows;
	vector<int> Type2ArrowDirections;

	// Vectors for each arrow
	vector<Arrow*> LeftArrows;
	vector<Arrow*> DownArrows;
	vector<Arrow*> UpArrows;
	vector<Arrow*> RightArrows;

	vector<AnimatedSprite*> animatedSprites;

	// Music
	Mix_Music* Song;
	double differentTrackMultiplier = 1.05;
};

#endif // !ArrowSpawner_h

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
	/// <summary>
	/// Constructor for the Spawner class
	/// </summary>
	/// <param name="window"></param>
	/// <param name="Clock"></param>
	/// <param name="PlayerScore"></param>
	Spawner(Window* window, Timer* Clock, Score* PlayerScore);
	/// <summary>
	/// Destructor for the Spawner class
	/// </summary>
	~Spawner();

	/// <summary>
	/// Initializes the Spawner class
	/// </summary>
	/// <returns>bool</returns>
	bool Init();

	/// <summary>
	/// Sets the song position to the game time (in ticks)
	/// </summary>
	/// <param name="totalTicks"></param>
	void Seek(int totalTicks);

	/// <summary>
	/// Checks if the song is desynced from the game time
	/// </summary>
	/// <param name="totalTicks"></param>
	void CheckDesync(int totalTicks);
	/// <summary>
	/// Switches the song to the song number specified (If the game is desynced)
	/// </summary>
	/// <param name="songNumber"></param>
	void SwitchSong(int songNumber);

	/// <summary>
	/// Updates the Objects in the Spawner class and returns a bool whether the game has ended or not
	/// </summary>
	/// <param name="totalTicks"></param>
	/// <returns>bool</returns>
	bool Update(int totalTicks);

	/// <summary>
	/// Public function to show the Miss Text
	/// </summary>
	/// <param name="x"></param>
	/// <param name="Ticks"></param>
	void ShowMissText(int x, int Ticks);

	/// <summary>
	/// Returns the new arrows that have been created
	/// </summary>
	/// <returns>vector<GameObject*></returns>
	vector<GameObject*> GetNewArrows();

	/// <summary>
	/// Returns the value of the hit by the player
	/// </summary>
	/// <param name="direction"></param>
	/// <param name="Ticks"></param>
	/// <returns>int</returns>
	int CheckCollision(int direction, int Ticks);
	/// <summary>
	/// Returns the value of the hold hit by the player
	/// </summary>
	/// <param name="direction"></param>
	/// <param name="Ticks"></param>
	/// <returns>int</returns>
	int CheckHoldCollision(int direction, int Ticks);
	/// <summary>
	/// Returns the value of the release hit by the player
	/// </summary>
	/// <param name="direction"></param>
	/// <param name="Ticks"></param>
	/// <returns>int</returns>
	int CheckReleaseCollision(int direction, int Ticks);

	/// <summary>
	/// Removes an arrow from the game
	/// </summary>
	/// <param name="arrow"></param>
	void RemoveArrow(GameObject* arrow);
private:
	/// <summary>
	/// Spawns an arrow in the game at the specified time and arrow type
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="Ticks"></param>
	/// <param name="arrowType"></param>
	void SpawnArrow(SDL_Renderer* renderer, int Ticks, ArrowType* arrowType);
	/// <summary>
	/// Spawns a BONUS arrow in the game at the specified time and arrow type
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="Ticks"></param>
	/// <param name="arrowType"></param>
	void SpawnBONUSArrow(SDL_Renderer* renderer, int Ticks, ArrowType* arrowType);

	/// <summary>
	/// Returns the arrow that the player has hit
	/// </summary>
	/// <param name="direction"></param>
	/// <param name="Ticks"></param>
	/// <returns>Arrow*</returns>
	Arrow* GetCollision(int direction, int Ticks);
	int collisionTicks = 0; // The time of the last collision
	int ticksSinceLastCollision = 0; // The time since the last collision

	int songNumber = 0; // The current song number

	Window* window; // The window that the game is running in
	Timer* Clock; // The game clock
	Score* PlayerScore; // The player's score (class)

	vector<GameObject*> newArrows; // The new arrows that have been created

	// Game Objects
	// Foreground Fade
	GameObject* ForegroundFade; // The foreground fade object
	
	// Splash Screen
	AnimatedSprite* SplashImage; // The splash image
	AnimatedSprite* SplashText; // The splash text
	GameObject* SplashBackground; // The splash background

	// Song Info
	Sprite* SongText; // The song text
	AnimatedSprite* SongNote; // The song note

	// Arrows
	Sprite* LeftArrow; // The left arrow
	Sprite* DownArrow; // The down arrow
	Sprite* UpArrow; // The up arrow
	Sprite* RightArrow; // The right arrow

	AnimatedSprite* LeftArrowAnim; // The left arrow animation
	AnimatedSprite* DownArrowAnim; // The down arrow animation
	AnimatedSprite* UpArrowAnim; // The up arrow animation
	AnimatedSprite* RightArrowAnim; // The right arrow animation

	Arrow* LastLeftArrow; // The last left arrow
	Arrow* LastDownArrow; // The last down arrow
	Arrow* LastUpArrow; // The last up arrow
	Arrow* LastRightArrow; // The last right arrow

	// Hit Text
	vector<AnimatedSprite*> MissText; // The miss text
	vector<AnimatedSprite*> OkText; // The ok text
	vector<AnimatedSprite*> GoodText; // The good text
	vector<AnimatedSprite*> NiceText; // The nice text
	vector<AnimatedSprite*> GreatText; // The great text
	AnimatedSprite* PerfectText; // The perfect text

	// Type 2 Columns
	vector<Column*> Type2Columns; // The type 2 columns

	// Type 2 Arrows
	vector<Arrow*> Type2Arrows; // The type 2 arrows
	vector<int> Type2ArrowDirections; // The type 2 arrow directions

	// Vectors for each arrow
	vector<Arrow*> LeftArrows; // The left arrows
	vector<Arrow*> DownArrows; // The down arrows
	vector<Arrow*> UpArrows; // The up arrows
	vector<Arrow*> RightArrows; // The right arrows

	vector<AnimatedSprite*> animatedSprites; // The animated sprites

	// Music
	Mix_Music* Song; // The song(s)
	double differentTrackMultiplier = 1.05; // The multiplier for the different track
};

#endif // !ArrowSpawner_h

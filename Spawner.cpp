#include "Spawner.h"
#include "Vector2.h"
#include "Logger.h"

Spawner::Spawner(Window* window, Timer* Clock, Score* PlayerScore)
{
	this->window = window;
	this->Clock = Clock;
	this->PlayerScore = PlayerScore;

	this->newArrows = vector<GameObject*>();

	// Game objects
	// Foreground Fade
	this->ForegroundFade = nullptr;

	// Splash Screen
	this->SplashImage = nullptr;
	this->SplashText = nullptr;
	this->SplashBackground = nullptr;

	// Song Info
	this->SongNote = nullptr;
	this->SongText = nullptr;

	// Arrows
	this->LeftArrow = nullptr;
	this->UpArrow = nullptr;
	this->DownArrow = nullptr;
	this->RightArrow = nullptr;

	this->LeftArrowAnim = nullptr;
	this->UpArrowAnim = nullptr;
	this->DownArrowAnim = nullptr;
	this->RightArrowAnim = nullptr;

	this->LastLeftArrow = nullptr;
	this->LastUpArrow = nullptr;
	this->LastDownArrow = nullptr;
	this->LastRightArrow = nullptr;

	// Hit Text
	this->PerfectText = nullptr;

	// Music
	this->Song = nullptr;
}

Spawner::~Spawner()
{
}

bool Spawner::Init()
{
	// INIT
	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}
	//Initialize SDL_mixer
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	// Initialize GameObjects
	// Song Info
	int cornerSpacing = 20;

	SongText = new Sprite(window->IsLoggingEnabled, window->logicalWidth - (650 + cornerSpacing), window->logicalHeight - (100 + cornerSpacing), 650, 100, "Assets/Sprites/SongInfo/SongText.png");
	SongText->Init(window->GetRenderer());
	window->AddGameObject(SongText, 3);
	SongNote = new AnimatedSprite(window->IsLoggingEnabled, SongText->x - (100 + cornerSpacing), window->logicalHeight - (100 + cornerSpacing), 100, 100, "Assets/Sprites/SongInfo/SongNote", 12, 6, true);
	SongNote->Init(window->GetRenderer());
	animatedSprites.push_back(SongNote);
	window->AddGameObject(SongNote, 3);
	SongNote->StartAnimation(Clock->GetTicks());

	// Arrows
	int arrowWidth = 100;
	int arrowSpacing = 44;
	int arrowTopSpacing = 24;

	LeftArrow = new Sprite(window->IsLoggingEnabled, (window->logicalWidth / 4) - (arrowWidth + arrowSpacing + arrowWidth + (arrowSpacing / 2)), arrowTopSpacing, arrowWidth, arrowWidth, "Assets/Sprites/Arrows/ArrowLeft_Base.png");
	LeftArrow->Init(window->GetRenderer());
	DownArrow = new Sprite(window->IsLoggingEnabled, (window->logicalWidth / 4) - (arrowWidth + (arrowSpacing / 2)), arrowTopSpacing, arrowWidth, arrowWidth, "Assets/Sprites/Arrows/ArrowDown_Base.png");
	DownArrow->Init(window->GetRenderer());
	UpArrow = new Sprite(window->IsLoggingEnabled, (window->logicalWidth / 4) + (arrowSpacing / 2), arrowTopSpacing, arrowWidth, arrowWidth, "Assets/Sprites/Arrows/ArrowUp_Base.png");
	UpArrow->Init(window->GetRenderer());
	RightArrow = new Sprite(window->IsLoggingEnabled, (window->logicalWidth / 4) + ((arrowSpacing / 2) + arrowWidth + arrowSpacing), arrowTopSpacing, arrowWidth, arrowWidth, "Assets/Sprites/Arrows/ArrowRight_Base.png");
	RightArrow->Init(window->GetRenderer());

	// Animated Arrows
	int arrowAnimWidth = arrowWidth + 40;
	int arrowAnimSpacing = arrowSpacing - 40;
	int arrowAnimTopSpacing = arrowTopSpacing - 20;

	LeftArrowAnim = new AnimatedSprite(window->IsLoggingEnabled, (window->logicalWidth / 4) - (arrowAnimWidth + arrowAnimSpacing + arrowAnimWidth + (arrowAnimSpacing / 2)), arrowAnimTopSpacing, arrowAnimWidth, arrowAnimWidth, "Assets/Sprites/Arrows/ArrowLeft_Anim/ArrowLeft_Anim", 7, 2);
	LeftArrowAnim->Init(window->GetRenderer());
	animatedSprites.push_back(LeftArrowAnim);
	DownArrowAnim = new AnimatedSprite(window->IsLoggingEnabled, (window->logicalWidth / 4) - (arrowAnimWidth + (arrowAnimSpacing / 2)), arrowAnimTopSpacing, arrowAnimWidth, arrowAnimWidth, "Assets/Sprites/Arrows/ArrowDown_Anim/ArrowDown_Anim", 7, 2);
	DownArrowAnim->Init(window->GetRenderer());
	animatedSprites.push_back(DownArrowAnim);
	UpArrowAnim = new AnimatedSprite(window->IsLoggingEnabled, (window->logicalWidth / 4) + (arrowAnimSpacing / 2), arrowAnimTopSpacing, arrowAnimWidth, arrowAnimWidth, "Assets/Sprites/Arrows/ArrowUp_Anim/ArrowUp_Anim", 7, 2);
	UpArrowAnim->Init(window->GetRenderer());
	animatedSprites.push_back(UpArrowAnim);
	RightArrowAnim = new AnimatedSprite(window->IsLoggingEnabled, (window->logicalWidth / 4) + ((arrowAnimSpacing / 2) + arrowAnimWidth + arrowAnimSpacing), arrowAnimTopSpacing, arrowAnimWidth, arrowAnimWidth, "Assets/Sprites/Arrows/ArrowRight_Anim/ArrowRight_Anim", 7, 2);
	RightArrowAnim->Init(window->GetRenderer());
	animatedSprites.push_back(RightArrowAnim);


	// Hit Text
	int textSpacing = 25;

	MissText.push_back(new AnimatedSprite(window->IsLoggingEnabled, LeftArrow->x, LeftArrow->y + arrowWidth + arrowTopSpacing, 100, 100, "Assets/Sprites/HitText/Miss/Miss0_", 10, 5));
	MissText[0]->Init(window->GetRenderer());
	animatedSprites.push_back(MissText[0]);
	MissText.push_back(new AnimatedSprite(window->IsLoggingEnabled, DownArrow->x, DownArrow->y + arrowWidth + arrowTopSpacing, 100, 100, "Assets/Sprites/HitText/Miss/Miss1_", 10, 5));
	MissText[1]->Init(window->GetRenderer());
	animatedSprites.push_back(MissText[1]);
	MissText.push_back(new AnimatedSprite(window->IsLoggingEnabled, UpArrow->x, UpArrow->y + arrowWidth + arrowTopSpacing, 100, 100, "Assets/Sprites/HitText/Miss/Miss2_", 10, 5));
	MissText[2]->Init(window->GetRenderer());
	animatedSprites.push_back(MissText[2]);
	MissText.push_back(new AnimatedSprite(window->IsLoggingEnabled, RightArrow->x, RightArrow->y + arrowWidth + arrowTopSpacing, 100, 100, "Assets/Sprites/HitText/Miss/Miss3_", 10, 5));
	MissText[3]->Init(window->GetRenderer());
	animatedSprites.push_back(MissText[3]);

	OkText.push_back(new AnimatedSprite(window->IsLoggingEnabled, LeftArrow->x, MissText[0]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Ok/Ok0_", 10, 5));
	OkText[0]->Init(window->GetRenderer());
	animatedSprites.push_back(OkText[0]);
	OkText.push_back(new AnimatedSprite(window->IsLoggingEnabled, DownArrow->x, MissText[1]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Ok/Ok1_", 10, 5));
	OkText[1]->Init(window->GetRenderer());
	animatedSprites.push_back(OkText[1]);
	OkText.push_back(new AnimatedSprite(window->IsLoggingEnabled, UpArrow->x, MissText[2]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Ok/Ok2_", 10, 5));
	OkText[2]->Init(window->GetRenderer());
	animatedSprites.push_back(OkText[2]);
	OkText.push_back(new AnimatedSprite(window->IsLoggingEnabled, RightArrow->x, MissText[3]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Ok/Ok3_", 10, 5));
	OkText[3]->Init(window->GetRenderer());
	animatedSprites.push_back(OkText[3]);

	GoodText.push_back(new AnimatedSprite(window->IsLoggingEnabled, LeftArrow->x, OkText[0]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Good/Good0_", 10, 5));
	GoodText[0]->Init(window->GetRenderer());
	animatedSprites.push_back(GoodText[0]);
	GoodText.push_back(new AnimatedSprite(window->IsLoggingEnabled, DownArrow->x, OkText[1]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Good/Good1_", 10, 5));
	GoodText[1]->Init(window->GetRenderer());
	animatedSprites.push_back(GoodText[1]);
	GoodText.push_back(new AnimatedSprite(window->IsLoggingEnabled, UpArrow->x, OkText[2]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Good/Good2_", 10, 5));
	GoodText[2]->Init(window->GetRenderer());
	animatedSprites.push_back(GoodText[2]);
	GoodText.push_back(new AnimatedSprite(window->IsLoggingEnabled, RightArrow->x, OkText[3]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Good/Good3_", 10, 5));
	GoodText[3]->Init(window->GetRenderer());
	animatedSprites.push_back(GoodText[3]);

	NiceText.push_back(new AnimatedSprite(window->IsLoggingEnabled, LeftArrow->x, GoodText[0]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Nice/Nice0_", 10, 5));
	NiceText[0]->Init(window->GetRenderer());
	animatedSprites.push_back(NiceText[0]);
	NiceText.push_back(new AnimatedSprite(window->IsLoggingEnabled, DownArrow->x, GoodText[1]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Nice/Nice1_", 10, 5));
	NiceText[1]->Init(window->GetRenderer());
	animatedSprites.push_back(NiceText[1]);
	NiceText.push_back(new AnimatedSprite(window->IsLoggingEnabled, UpArrow->x, GoodText[2]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Nice/Nice2_", 10, 5));
	NiceText[2]->Init(window->GetRenderer());
	animatedSprites.push_back(NiceText[2]);
	NiceText.push_back(new AnimatedSprite(window->IsLoggingEnabled, RightArrow->x, GoodText[3]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Nice/Nice3_", 10, 5));
	NiceText[3]->Init(window->GetRenderer());
	animatedSprites.push_back(NiceText[3]);

	GreatText.push_back(new AnimatedSprite(window->IsLoggingEnabled, LeftArrow->x, NiceText[0]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Great/Great0_", 10, 5));
	GreatText[0]->Init(window->GetRenderer());
	animatedSprites.push_back(GreatText[0]);
	GreatText.push_back(new AnimatedSprite(window->IsLoggingEnabled, DownArrow->x, NiceText[1]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Great/Great1_", 10, 5));
	GreatText[1]->Init(window->GetRenderer());
	animatedSprites.push_back(GreatText[1]);
	GreatText.push_back(new AnimatedSprite(window->IsLoggingEnabled, UpArrow->x, NiceText[2]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Great/Great2_", 10, 5));
	GreatText[2]->Init(window->GetRenderer());
	animatedSprites.push_back(GreatText[2]);
	GreatText.push_back(new AnimatedSprite(window->IsLoggingEnabled, RightArrow->x, NiceText[3]->y + textSpacing, 100, 100, "Assets/Sprites/HitText/Great/Great3_", 10, 5));
	GreatText[3]->Init(window->GetRenderer());
	animatedSprites.push_back(GreatText[3]);

	PerfectText = new AnimatedSprite(window->IsLoggingEnabled, (window->logicalWidth / 4) - 200, (window->logicalHeight / 4) - 100, 400, 200, "Assets/Sprites/HitText/Perfect/Perfect", 10, 5);
	PerfectText->Init(window->GetRenderer());
	animatedSprites.push_back(PerfectText);

	// Type 2 Columns
	Type2Columns.push_back(new Column(window->IsLoggingEnabled, (window->logicalWidth / 4) - (arrowWidth + arrowSpacing + arrowWidth + (arrowSpacing / 2)), 0, arrowWidth, window->logicalHeight, new GO_Colour(226, 226, 6, 0)));
	window->AddGameObject(Type2Columns[0], 0);
	Type2Columns.push_back(new Column(window->IsLoggingEnabled, (window->logicalWidth / 4) - (arrowWidth + (arrowSpacing / 2)), 0, arrowWidth, window->logicalHeight, new GO_Colour(226, 226, 6, 0)));
	window->AddGameObject(Type2Columns[1], 0);
	Type2Columns.push_back(new Column(window->IsLoggingEnabled, (window->logicalWidth / 4) + (arrowSpacing / 2), 0, arrowWidth, window->logicalHeight, new GO_Colour(226, 226, 6, 0)));
	window->AddGameObject(Type2Columns[2], 0);
	Type2Columns.push_back(new Column(window->IsLoggingEnabled, (window->logicalWidth / 4) + ((arrowSpacing / 2) + arrowWidth + arrowSpacing), 0, arrowWidth, window->logicalHeight, new GO_Colour(226, 226, 6, 0)));
	window->AddGameObject(Type2Columns[3], 0);

	Song = Mix_LoadMUS("Assets/Music/Decimate_100.mp3");

	// Spawn the arrows
		//
	SpawnArrow(window->GetRenderer(), 244, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 257, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 268, new ArrowType(0)); // short note

		//
	SpawnArrow(window->GetRenderer(), 339, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 352, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 362, new ArrowType(0)); // short note

		//
	SpawnArrow(window->GetRenderer(), 435, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 448, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 460, new ArrowType(0, 60)); // long note

		//
	SpawnArrow(window->GetRenderer(), 533, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 545, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 555, new ArrowType(0)); // short note

		//
	SpawnArrow(window->GetRenderer(), 631, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 641, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 653, new ArrowType(0)); // short note

		//
	SpawnArrow(window->GetRenderer(), 725, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 736, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 747, new ArrowType(0)); // short note

		//
		//
	SpawnArrow(window->GetRenderer(), 847, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 865, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 883, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 900, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 918, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 932, new ArrowType(0, 60)); // long note
	SpawnArrow(window->GetRenderer(), 932, new ArrowType(3, 60)); // long note

		//
		//
	SpawnArrow(window->GetRenderer(), 1038, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1056, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1073, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1090, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1108, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1122, new ArrowType(0, 60)); // long note
	SpawnArrow(window->GetRenderer(), 1122, new ArrowType(3, 60)); // long note

		//
	SpawnArrow(window->GetRenderer(), 1230, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1248, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1266, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1284, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1302, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1315, new ArrowType(0, 60)); // long note
	SpawnArrow(window->GetRenderer(), 1315, new ArrowType(3, 60)); // long note

		//
		//
	SpawnArrow(window->GetRenderer(), 1412, new ArrowType(1, 24)); // long note
	SpawnArrow(window->GetRenderer(), 1459, new ArrowType(1, 24)); // long note
	SpawnArrow(window->GetRenderer(), 1496, new ArrowType(2, 24)); // long note
	SpawnArrow(window->GetRenderer(), 1529, new ArrowType(2, 24)); // long note
	SpawnArrow(window->GetRenderer(), 1564, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 1576, new ArrowType(0)); // short note
	SpawnArrow(window->GetRenderer(), 1589, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1600, new ArrowType(3)); // short note

		//
		//
	SpawnArrow(window->GetRenderer(), 1625, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 1636, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 1647, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1659, new ArrowType(0, 300)); // long note

		//
	SpawnArrow(window->GetRenderer(), 1703, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 1723, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 1763, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 1787, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 1815, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1860, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 1895, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 1919, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 1955, new ArrowType(2)); // short note

		//
		//
	SpawnArrow(window->GetRenderer(), 2011, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2021, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2032, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 2047, new ArrowType(0, 300)); // long note

		//
	SpawnArrow(window->GetRenderer(), 2086, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 2108, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 2144, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2166, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 2195, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 2242, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2278, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 2315, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 2338, new ArrowType(3)); // short note

		//
		//
	SpawnArrow(window->GetRenderer(), 2396, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2407, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2415, new ArrowType(1)); // short note

		//
	SpawnArrow(window->GetRenderer(), 2442, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2452, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2463, new ArrowType(1)); // short note

		//
	SpawnArrow(window->GetRenderer(), 2489, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2500, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2512, new ArrowType(1)); // short note

		//
	SpawnArrow(window->GetRenderer(), 2538, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2550, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2561, new ArrowType(1)); // short note

		//
	SpawnArrow(window->GetRenderer(), 2584, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2597, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2609, new ArrowType(1)); // short note

		//
	SpawnArrow(window->GetRenderer(), 2634, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2645, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2656, new ArrowType(1)); // short note

		//
	SpawnArrow(window->GetRenderer(), 2682, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2692, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2704, new ArrowType(1)); // short note

		//
	SpawnArrow(window->GetRenderer(), 2730, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2741, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2754, new ArrowType(1)); // short note

		//
	SpawnArrow(window->GetRenderer(), 2766, new ArrowType(0, new ArrowType(1), 72)); // short notes
	SpawnArrow(window->GetRenderer(), 2793, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 2815, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 2862, new ArrowType(1, new ArrowType(2), 74)); // short notes
	SpawnArrow(window->GetRenderer(), 2886, new ArrowType(0)); // short note
	SpawnArrow(window->GetRenderer(), 2910, new ArrowType(3)); // short note

		//
		//
	SpawnArrow(window->GetRenderer(), 3180, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 3205, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 3229, new ArrowType(0)); // short note
	SpawnArrow(window->GetRenderer(), 3277, new ArrowType(2, 30)); // short note
	SpawnArrow(window->GetRenderer(), 3300, new ArrowType(1)); // short note
	SpawnArrow(window->GetRenderer(), 3321, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 3347, new ArrowType(0, new ArrowType(2, 20), 68)); // short note
	SpawnArrow(window->GetRenderer(), 3369, new ArrowType(3)); // short note
	SpawnArrow(window->GetRenderer(), 3394, new ArrowType(0)); // short note
	//SpawnArrow(window->GetRenderer(), 3415, new ArrowType(2)); // short note
	SpawnArrow(window->GetRenderer(), 3440, new ArrowType(3)); // short note


	// BONUS ARROWS
		//
	SpawnBONUSArrow(window->GetRenderer(), 4050, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4070, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4092, new ArrowType(3)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4115, new ArrowType(0, 20)); // long note

		//
	SpawnBONUSArrow(window->GetRenderer(), 4138, new ArrowType(1)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4160, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4186, new ArrowType(0, 30)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4186, new ArrowType(3, 30)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4205, new ArrowType(2)); // short note

		//
	SpawnBONUSArrow(window->GetRenderer(), 4230, new ArrowType(1)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4253, new ArrowType(1)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4278, new ArrowType(0, 30)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4278, new ArrowType(3, 30)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4302, new ArrowType(2)); // short note

		//
	SpawnBONUSArrow(window->GetRenderer(), 4332, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4354, new ArrowType(3)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4376, new ArrowType(2, 30)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4376, new ArrowType(3, 30)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4402, new ArrowType(0)); // short note

		//
	SpawnBONUSArrow(window->GetRenderer(), 4425, new ArrowType(0)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4429, new ArrowType(3)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4436, new ArrowType(0)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4452, new ArrowType(0)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4452, new ArrowType(3)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4475, new ArrowType(0, 30)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4475, new ArrowType(3, 30)); // long note

		//
	SpawnBONUSArrow(window->GetRenderer(), 4549, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4574, new ArrowType(1, 30)); // long note

		//
	SpawnBONUSArrow(window->GetRenderer(), 4624, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4648, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4671, new ArrowType(1, 30)); // long note

		//
	SpawnBONUSArrow(window->GetRenderer(), 4718, new ArrowType(0)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4742, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4765, new ArrowType(1, 30)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4765, new ArrowType(3, 30)); // long note


		// Final Section
	SpawnBONUSArrow(window->GetRenderer(), 4837, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4849, new ArrowType(1)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4861, new ArrowType(2)); // short note
	SpawnBONUSArrow(window->GetRenderer(), 4882, new ArrowType(0, 56)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4882, new ArrowType(3, 56)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4906, new ArrowType(1, 30)); // long note
	SpawnBONUSArrow(window->GetRenderer(), 4906, new ArrowType(2, 30)); // long note

	return true;
}

void Spawner::Seek(int totalTicks)
{
	double seconds = (totalTicks / 60.0);

	// If the game is after 65 seconds, the song is the bonus version (Adjust the time)
	if (Clock->GetTicks() >= 3900) seconds -= static_cast<double>(3960) / 60;

	Mix_SetMusicPosition(seconds);
}

void Spawner::CheckDesync(int totalTicks)
{
	double songPosition = Mix_GetMusicPosition(Song);
	double gamePosition = (totalTicks / 60.0);

	// If the game is after 65 seconds, the song is the bonus version (Adjust the time)
	if (Clock->GetTicks() >= 3900) gamePosition -= static_cast<double>(3960) / 60;

	switch (songNumber)
	{
	case 0:
		if (songPosition - gamePosition > 0.1)
		{
			// Switch the song
			SwitchSong(1);
		}
		break;
	case 1:
		if ((songPosition / differentTrackMultiplier) - gamePosition <= 0)
		{
			// Switch the song
			SwitchSong(0);
		}
		break;
	}


}

void Spawner::SwitchSong(int songNumber)
{
	this->songNumber = songNumber;

	double songPosition = Mix_GetMusicPosition(Song);

	switch (songNumber)
	{
	case 0:
		songPosition /= differentTrackMultiplier;

		Mix_FreeMusic(Song);

		// If the song is before 65 seconds, play the normal version
		if (Clock->GetTicks() < 3900) Song = Mix_LoadMUS("Assets/Music/Decimate_100.mp3");
		else Song = Mix_LoadMUS("Assets/Music/DecimateBONUS_100.mp3");

		Mix_FadeOutMusic(500);
		Mix_FadeInMusic(Song, 1, 500);
		Mix_FadeInMusicPos(Song, 1, 500, songPosition);
		break;
	case 1:
		songPosition *= differentTrackMultiplier;

		Mix_FreeMusic(Song);

		// If the song is before 65 seconds, play the normal version
		if (Clock->GetTicks() < 3900) Song = Mix_LoadMUS("Assets/Music/Decimate_105.mp3");
		else Song = Mix_LoadMUS("Assets/Music/DecimateBONUS_105.mp3");

		Mix_FadeOutMusic(500);
		Mix_FadeInMusic(Song, 1, 500);
		Mix_FadeInMusicPos(Song, 1, 500, songPosition);
		break;
	}

}

bool Spawner::Update(int totalTicks)
{
	if (LastLeftArrow != nullptr) LastLeftArrow->UpdateHeldFor(totalTicks);
	if (LastDownArrow != nullptr) LastDownArrow->UpdateHeldFor(totalTicks);
	if (LastUpArrow != nullptr) LastUpArrow->UpdateHeldFor(totalTicks);
	if (LastRightArrow != nullptr) LastRightArrow->UpdateHeldFor(totalTicks);

	if (Type2Columns[0] != nullptr) Type2Columns[0]->Update(totalTicks);
	if (Type2Columns[1] != nullptr) Type2Columns[1]->Update(totalTicks);
	if (Type2Columns[2] != nullptr) Type2Columns[2]->Update(totalTicks);
	if (Type2Columns[3] != nullptr) Type2Columns[3]->Update(totalTicks);

	// Update Animated Sprites
	for (int i = 0; i < animatedSprites.size(); i++)
	{
		// Check if the sprite is a nullptr
		if (animatedSprites[i] == nullptr)
		{
			// Remove the sprite from the vector
			animatedSprites.erase(animatedSprites.begin() + i);
			continue;
		}

		// Update the sprite
		animatedSprites[i]->UpdateAnimation(totalTicks);
	}

	// Update Type 2 Arrows
	for (int i = 0; i < Type2Arrows.size(); i++)
	{
		if (Type2Arrows[i]->Destroy)
		{
			Type2Arrows.erase(Type2Arrows.begin() + i);

			Type2Columns[Type2ArrowDirections[i]]->Hide(totalTicks);
			Type2ArrowDirections.erase(Type2ArrowDirections.begin() + i);
			continue;
		}

		// Check if the arrow is on screen
		if (window->GameObjectIsOnTopPercentScreen(Type2Arrows[i]->GetRenderLayer(), Type2Arrows[i]->GetDrawIndex(), 0.8))
			Type2Columns[Type2Arrows[i]->Type->GetEndDirection()]->Show(totalTicks);
		else Type2Columns[Type2Arrows[i]->Type->GetEndDirection()]->Hide(totalTicks);
	}

	if (totalTicks % 60 == 0) CheckDesync(totalTicks);

	// Time based events (in ticks) { 1 second = 60 ticks }
	switch (totalTicks)
	{
	// 0 seconds
	case 0:
		// Play the music
		Mix_PlayMusic(Song, 1);
		Seek(totalTicks);

		// Foreground fade
		ForegroundFade = new GO_Rect(window->IsLoggingEnabled, 0, 0, window->logicalWidth, window->logicalHeight, new GO_Colour(0, 0, 0, 255));
		window->AddGameObject(ForegroundFade, 5);

		// Splash screen
		SplashBackground = new GO_Rect(window->IsLoggingEnabled, 0, 0, window->logicalWidth, window->logicalHeight, new GO_Colour(0, 0, 0, 255));
		window->AddGameObject(SplashBackground, 3);

		SplashImage = new AnimatedSprite(window->IsLoggingEnabled, window->logicalWidth / 2 - 150, window->logicalHeight / 2 - 150, 300, 300, "Assets/Sprites/Splash/Heart_Broken/Heart_Broken", 5, 5);
		SplashImage->Init(window->GetRenderer());
		animatedSprites.push_back(SplashImage);
		window->AddGameObject(SplashImage, 4);

		SplashText = new AnimatedSprite(window->IsLoggingEnabled, window->logicalWidth / 2 - 200, window->logicalHeight / 2 - 100 + (0.5 * SplashImage->GetHeight()), 400, 200, "Assets/Sprites/Splash/Heart_Text_Broken/Heart_Text_Broken", 7, 5);
		SplashText->Init(window->GetRenderer());
		animatedSprites.push_back(SplashText);
		window->AddGameObject(SplashText, 4);
		break;

		// Foreground fade in
	case 5:
		ForegroundFade->colour->a -= 25;
		break;
	case 10:
		ForegroundFade->colour->a -= 26;
		break;
	case 15:
		ForegroundFade->colour->a -= 25;
		break;
	case 20:
		ForegroundFade->colour->a -= 26;
		break;
	case 25:
		ForegroundFade->colour->a -= 25;
		break;
	case 30:
		ForegroundFade->colour->a -= 26;
		break;
	case 35:
		ForegroundFade->colour->a -= 25;
		break;
	case 40:
		ForegroundFade->colour->a -= 26;
		break;
	case 45:
		ForegroundFade->colour->a -= 25;
		break;
	case 50:
		ForegroundFade->colour->a -= 26;
		break;

	// 1 second
	case 60:
		SplashImage->MovePosition(2, 0);
		break;
	case 63:
		SplashImage->MovePosition(-2, 0);
		break;
	case 66:
		SplashImage->MovePosition(2, 0);
		break;
	case 69:
		SplashImage->MovePosition(-2, 0);
		break;
	case 72:
		SplashImage->MovePosition(2, 0);
		break;
	case 75:
		SplashImage->MovePosition(-2, 0);
		break;
	case 78:
		SplashImage->MovePosition(2, 0);
		break;
	case 81:
		SplashImage->MovePosition(-2, 0);
		break;
	case 84:
		SplashImage->MovePosition(2, 0);
		break;
	case 87:
		SplashImage->MovePosition(-2, 0);
		break;
	case 90:
		SplashImage->MovePosition(2, 0);
		break;
	case 93:
		SplashImage->MovePosition(-2, 0);
		break;
	case 96:
		SplashImage->MovePosition(2, 0);
		break;
	case 99:
		SplashImage->MovePosition(-2, 0);
		break;
	case 102:
		SplashImage->MovePosition(2, 0);
		break;
	case 105:
		SplashImage->MovePosition(-2, 0);
		break;
	case 108:
		SplashImage->MovePosition(2, 0);
		break;
	case 111:
		SplashImage->MovePosition(-2, 0);
		break;
	case 114:
		SplashImage->MovePosition(2, 0);
		break;
	case 117:
		SplashImage->MovePosition(-2, 0);
		break;
	case 120:
		SplashImage->MovePosition(2, 0);
		break;
	case 123:
		SplashImage->MovePosition(-2, 0);
		break;
	case 126:
		SplashImage->MovePosition(2, 0);
		break;
	case 129:
		SplashImage->MovePosition(-2, 0);
		break;
	case 132:
		SplashImage->MovePosition(2, 0);
		break;
	case 135:
		SplashImage->MovePosition(-2, 0);
		break;
	case 138:
		SplashImage->MovePosition(2, 0);
		break;
	case 141:
		SplashImage->MovePosition(-2, 0);
		break;
	case 144:
		SplashImage->MovePosition(2, 0);
		break;
	case 147:
		SplashImage->MovePosition(-2, 0);
		break;
	case 150:
		SplashImage->MovePosition(2, 0);
		break;
	case 155:
		SplashImage->StartAnimation(totalTicks);
		SplashText->StartAnimation(totalTicks);
		break;

	// Foreground fade out
	case 210:
		ForegroundFade->colour->a += 42;
		break;
	case 215:
		ForegroundFade->colour->a += 43;
		break;
	case 220:
		ForegroundFade->colour->a += 42;
		break;
	case 225:
		ForegroundFade->colour->a += 43;
		break;
	case 230:
		ForegroundFade->colour->a += 42;
		break;
	case 235:
		ForegroundFade->colour->a += 43;

		// Remove the splash screen
		window->RemoveGameObject(SplashImage->GetRenderLayer(), SplashImage->GetDrawIndex());
		SplashImage->DestroyObject();
		SplashImage = nullptr;

		window->RemoveGameObject(SplashText->GetRenderLayer(), SplashText->GetDrawIndex());
		SplashText->DestroyObject();
		SplashText = nullptr;

		// Show the arrows
		window->AddGameObject(LeftArrow, 0);
		window->AddGameObject(DownArrow, 0);
		window->AddGameObject(UpArrow, 0);
		window->AddGameObject(RightArrow, 0);

		window->AddGameObject(LeftArrowAnim, 0);
		window->AddGameObject(DownArrowAnim, 0);
		window->AddGameObject(UpArrowAnim, 0);
		window->AddGameObject(RightArrowAnim, 0);

		// Show the Hit Text
		window->AddGameObject(MissText[0], 3);
		window->AddGameObject(MissText[1], 3);
		window->AddGameObject(MissText[2], 3);
		window->AddGameObject(MissText[3], 3);

		window->AddGameObject(OkText[0], 3);
		window->AddGameObject(OkText[1], 3);
		window->AddGameObject(OkText[2], 3);
		window->AddGameObject(OkText[3], 3);

		window->AddGameObject(GoodText[0], 3);
		window->AddGameObject(GoodText[1], 3);
		window->AddGameObject(GoodText[2], 3);
		window->AddGameObject(GoodText[3], 3);

		window->AddGameObject(NiceText[0], 3);
		window->AddGameObject(NiceText[1], 3);
		window->AddGameObject(NiceText[2], 3);
		window->AddGameObject(NiceText[3], 3);

		window->AddGameObject(GreatText[0], 3);
		window->AddGameObject(GreatText[1], 3);
		window->AddGameObject(GreatText[2], 3);
		window->AddGameObject(GreatText[3], 3);

		window->AddGameObject(PerfectText, 3);

		// Remove the splash background
		window->RemoveGameObject(SplashBackground->GetRenderLayer(), SplashBackground->GetDrawIndex());
		break;

	// Foreground fade in
	case 240:
		ForegroundFade->colour->a -= 25;
		break;
	case 245:
		ForegroundFade->colour->a -= 26;
		break;
	case 250:
		ForegroundFade->colour->a -= 25;
		break;
	case 255:
		ForegroundFade->colour->a -= 26;
		break;
	case 260:
		ForegroundFade->colour->a -= 25;
		break;
	case 265:
		ForegroundFade->colour->a -= 26;
		break;
	case 270:
		ForegroundFade->colour->a -= 25;
		break;
	case 275:
		ForegroundFade->colour->a -= 26;
		break;
	case 280:
		ForegroundFade->colour->a -= 25;
		break;
	case 285:
		ForegroundFade->colour->a = 0;
		break;

	// 5 seconds
	case 300:
		break;

	case 360:
		break;

	case 600:
		break;

	// 65 seconds (1 minute 5 seconds) { Close The Game }
	case 3900:
		// Stop the music
		Mix_HaltMusic();
		if (PlayerScore->GetScore() < 40000)
		{
			return false;
		}
		break;

	// BONUS (66 seconds) { Switch The Song }
	case 3960:
		// Play the music
		SwitchSong(songNumber);
		Seek(totalTicks);

		//cout << endl << "<< BONUS SONG >>" << endl << endl;

		break;

	// 86 seconds (1 minute 26 seconds) { Close The Game } [This allows the song to fade in and out while having an extra 15 seconds of "gameplay"]
	case 5160:
		// Stop the music
		Mix_HaltMusic();
		return false;
	}

	return true;
}

void Spawner::ShowMissText(int x, int Ticks)
{
	if (x == LeftArrow->x)
	{
		MissText[0]->StartAnimation(Ticks);
	}
	else if (x == DownArrow->x)
	{
		MissText[1]->StartAnimation(Ticks);
	}
	else if (x == UpArrow->x)
	{
		MissText[2]->StartAnimation(Ticks);
	}
	else if (x == RightArrow->x)
	{
		MissText[3]->StartAnimation(Ticks);
	}
}

vector<GameObject*> Spawner::GetNewArrows()
{
	vector<GameObject*> returnVector = newArrows;
	newArrows.clear();
	return returnVector;
}

int Spawner::CheckCollision(int direction, int Ticks)
{
	GameObject* targetGameObject = nullptr;
	switch (direction)
	{
	case 0:
		targetGameObject = LeftArrow;

		LeftArrowAnim->StopAnimation();
		LeftArrowAnim->StartAnimation(Ticks);
		break;
	case 1:
		targetGameObject = DownArrow;

		DownArrowAnim->StopAnimation();
		DownArrowAnim->StartAnimation(Ticks);
		break;
	case 2:
		targetGameObject = UpArrow;

		UpArrowAnim->StopAnimation();
		UpArrowAnim->StartAnimation(Ticks);
		break;
	case 3:
		targetGameObject = RightArrow;

		RightArrowAnim->StopAnimation();
		RightArrowAnim->StartAnimation(Ticks);
		break;
	default:
		SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Invalid Arrow Direction Declared (Checking Collision)", Logger::GetTimestamp().c_str());
		return -1;
	}

	// Get the first arrow in the direction
	Arrow* arrow = GetCollision(direction, Ticks);

	if (arrow == nullptr)
	{
		// Miss
		MissText[direction]->StartAnimation(Ticks);

		// Return a miss
		return 0;
	}

	// Get the accuracy and worth of the hit
	double accuracy = arrow->HitAccuracy;
	int worth = arrow->GetWorth();

	// Check if the arrow is in the hitbox
	if (accuracy > 0)
	{
		// Show the Hit Text
		// Ok
		if (accuracy < 0.3) OkText[direction]->StartAnimation(Ticks);

		// Good
		else if (accuracy < 0.6) GoodText[direction]->StartAnimation(Ticks);

		// Nice
		else if (accuracy < 0.8) NiceText[direction]->StartAnimation(Ticks);

		// Great
		else if (accuracy < 0.9) GreatText[direction]->StartAnimation(Ticks);

		// Perfect
		else PerfectText->StartAnimation(Ticks);

		if (arrow->Type->Type == 0)
		{
			// Remove the arrow from the game
			window->RemoveGameObject(arrow->GetRenderLayer(), arrow->GetDrawIndex());
			RemoveArrow(arrow);
			delete arrow;
			arrow = nullptr;
		}
		else if (arrow->Type->Type == 1)
		{
			switch (direction)
			{
			case 0:
				LastLeftArrow = arrow;
				break;
			case 1:
				LastDownArrow = arrow;
				break;
			case 2:
				LastUpArrow = arrow;
				break;
			case 3:
				LastRightArrow = arrow;
				break;
			}

			// Freeze the arrow
			arrow->Freeze(Ticks);
			worth += arrow->Unfreeze(Ticks);
		}
		else if (arrow->Type->Type == 2)
		{
			Arrow* newArrow = nullptr;
			switch (arrow->Type->GetEndDirection())
			{
			case 0:
				newArrow = new Arrow(window->IsLoggingEnabled, LeftArrow->x, arrow->y + (arrow->Type->GetDelay() * -arrow->velocity->y), new Vector2(arrow->velocity->x, arrow->velocity->y), arrow->Type->GetEndArrowType());
				// Add the arrow into the LeftArrows vector in the correct position (sorted by y)
				for (int i = 0; i < LeftArrows.size(); i++)
				{
					if (newArrow->y < LeftArrows[i]->y)
					{
						LeftArrows.insert(LeftArrows.begin() + i, newArrow);
						break;
					}
				}
				break;
			case 1:
				newArrow = new Arrow(window->IsLoggingEnabled, DownArrow->x, arrow->y + (arrow->Type->GetDelay() * -arrow->velocity->y), new Vector2(arrow->velocity->x, arrow->velocity->y), arrow->Type->GetEndArrowType());
				// Add the arrow into the DownArrows vector in the correct position (sorted by y)
				for (int i = 0; i < DownArrows.size(); i++)
				{
					if (newArrow->y < DownArrows[i]->y)
					{
						DownArrows.insert(DownArrows.begin() + i, newArrow);
						break;
					}
				}
				if (DownArrows.size() == 0) DownArrows.push_back(newArrow);
				break;
			case 2:
				newArrow = new Arrow(window->IsLoggingEnabled, UpArrow->x, arrow->y + (arrow->Type->GetDelay() * -arrow->velocity->y), new Vector2(arrow->velocity->x, arrow->velocity->y), arrow->Type->GetEndArrowType());
				// Add the arrow into the UpArrows vector in the correct position (sorted by y)
				for (int i = 0; i < UpArrows.size(); i++)
				{
					if (newArrow->y < UpArrows[i]->y)
					{
						UpArrows.insert(UpArrows.begin() + i, newArrow);
						break;
					}
				}
				if (UpArrows.size() == 0) UpArrows.push_back(newArrow);
				break;
			case 3:
				newArrow = new Arrow(window->IsLoggingEnabled, RightArrow->x, arrow->y + (arrow->Type->GetDelay() * -arrow->velocity->y), new Vector2(arrow->velocity->x, arrow->velocity->y), arrow->Type->GetEndArrowType());
				// Add the arrow into the RightArrows vector in the correct position (sorted by y)
				for (int i = 0; i < RightArrows.size(); i++)
				{
					if (newArrow->y < RightArrows[i]->y)
					{
						RightArrows.insert(RightArrows.begin() + i, newArrow);
						break;
					}
				}
				if (RightArrows.size() == 0) RightArrows.push_back(newArrow);
				break;
			}
			newArrow->Init(window);
			newArrows.push_back(newArrow);

			// Remove the arrow from the game
			window->RemoveGameObject(arrow->GetRenderLayer(), arrow->GetDrawIndex());
			RemoveArrow(arrow);
			delete arrow;
			arrow = nullptr;
		}

		worth = worth * accuracy;

		// Return the worth of the hit
		return worth;
	}
	else
	{
		// Miss
		MissText[direction]->StartAnimation(Ticks);
		// Return a miss
		return 0;
	}
}

int Spawner::CheckHoldCollision(int direction, int Ticks)
{
	Arrow* arrow = nullptr;
	switch (direction)
	{
	case 0:
		arrow = LastLeftArrow;
		break;
	case 1:
		arrow = LastDownArrow;
		break;
	case 2:
		arrow = LastUpArrow;
		break;
	case 3:
		arrow = LastRightArrow;
		break;
	default:
		SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Invalid Arrow Direction Declared (Checking Held Collision)", Logger::GetTimestamp().c_str());
		return -1;
	}

	// Return -1 (to indicate points should not be added nor should a miss be counted)
	if (arrow == nullptr) return -1;

	if (arrow->GetHeldFor() >= arrow->Type->GetHoldDuration())
	{
		// Return the worth of the hit
		return CheckReleaseCollision(direction, Ticks);
	}

	// Return -1 (to indicate points should not be added nor should a miss be counted)
	return -1;
}

int Spawner::CheckReleaseCollision(int direction, int Ticks)
{
	Arrow* arrow = nullptr;
	switch (direction)
	{
	case 0:
		arrow = LastLeftArrow;
		break;
	case 1:
		arrow = LastDownArrow;
		break;
	case 2:
		arrow = LastUpArrow;
		break;
	case 3:
		arrow = LastRightArrow;
		break;
	default:
		SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Invalid Arrow Direction Declared (Checking Release Collision)", Logger::GetTimestamp().c_str());
		return -1;
	}

	// Return -1 (to indicate points should not be added nor should a miss be counted)
	if (arrow == nullptr) return -1;

	double holdAccuracy = arrow->Unfreeze(Ticks);

	// Remove the arrow from the game
	window->RemoveGameObject(arrow->GetRenderLayer(), arrow->GetDrawIndex());
	RemoveArrow(arrow);
	delete arrow;
	arrow = nullptr;

	// Set the last arrow to nullptr
	switch (direction)
	{
	case 0:
		LastLeftArrow = nullptr;
		break;
	case 1:
		LastDownArrow = nullptr;
		break;
	case 2:
		LastUpArrow = nullptr;
		break;
	case 3:
		LastRightArrow = nullptr;
		break;
	}

	// Return the worth of the hit
	return 100 * holdAccuracy;
}

void Spawner::RemoveArrow(GameObject* arrow)
{
	// Figure out which direction the arrow is in
	if (arrow->x == LeftArrow->x)
	{
		// Get the index of the arrow in the vector
		int index = -1;
		for (int i = 0; i < LeftArrows.size(); i++)
			if (LeftArrows[i] == arrow)
			{
				index = i;
				break;
			}

		// Remove the arrow from the vector
		if (index != -1)
			LeftArrows.erase(LeftArrows.begin() + index);
		else SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Arrow Not Found In Vector (Removing Arrow)", Logger::GetTimestamp().c_str());
	}
	else if (arrow->x == UpArrow->x)
	{
		// Get the index of the arrow in the vector
		int index = -1;
		for (int i = 0; i < UpArrows.size(); i++)
			if (UpArrows[i] == arrow)
			{
				index = i;
				break;
			}

		// Remove the arrow from the vector
		if (index != -1)
			UpArrows.erase(UpArrows.begin() + index);
		else SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Arrow Not Found In Vector (Removing Arrow)", Logger::GetTimestamp().c_str());
	}
	else if (arrow->x == DownArrow->x)
	{
		// Get the index of the arrow in the vector
		int index = -1;
		for (int i = 0; i < DownArrows.size(); i++)
			if (DownArrows[i] == arrow)
			{
				index = i;
				break;
			}

		// Remove the arrow from the vector
		if (index != -1)
			DownArrows.erase(DownArrows.begin() + index);
		else SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Arrow Not Found In Vector (Removing Arrow)", Logger::GetTimestamp().c_str());
	}
	else if (arrow->x == RightArrow->x)
	{
		// Get the index of the arrow in the vector
		int index = -1;
		for (int i = 0; i < RightArrows.size(); i++)
			if (RightArrows[i] == arrow)
			{
				index = i;
				break;
			}

		// Remove the arrow from the vector
		if (index != -1)
			RightArrows.erase(RightArrows.begin() + index);
		else SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Arrow Not Found In Vector (Removing Arrow)", Logger::GetTimestamp().c_str());
	}
	else
	{
		SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Invalid Arrow Direction Declared (Removing Arrow)", Logger::GetTimestamp().c_str());
	}
}

void Spawner::SpawnArrow(SDL_Renderer* renderer, int Ticks, ArrowType* arrowType)
{
	Arrow* arrow = nullptr;
	int arrowSpeed = 8;
	switch (arrowType->Direction)
	{
	case 0:
		arrow = new Arrow(window->IsLoggingEnabled, LeftArrow->x, window->logicalHeight + (Ticks * arrowSpeed), new Vector2(0, -arrowSpeed), arrowType);
		LeftArrows.push_back(arrow);
		break;
	case 1:
		arrow = new Arrow(window->IsLoggingEnabled, DownArrow->x, window->logicalHeight + (Ticks * arrowSpeed), new Vector2(0, -arrowSpeed), arrowType);
		DownArrows.push_back(arrow);
		break;
	case 2:
		arrow = new Arrow(window->IsLoggingEnabled, UpArrow->x, window->logicalHeight + (Ticks * arrowSpeed), new Vector2(0, -arrowSpeed), arrowType);
		UpArrows.push_back(arrow);
		break;
	case 3:
		arrow = new Arrow(window->IsLoggingEnabled, RightArrow->x, window->logicalHeight + (Ticks * arrowSpeed), new Vector2(0, -arrowSpeed), arrowType);
		RightArrows.push_back(arrow);
		break;
	default:
		SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Invalid Arrow Direction Declared (Spawning Arrow)", Logger::GetTimestamp().c_str());
		return;
	}
	arrow->Init(window);
	if (arrow->Type->Type == 2)
	{
		Type2Arrows.push_back(arrow);
		Type2ArrowDirections.push_back(arrowType->GetEndDirection());
	}
	newArrows.push_back(arrow);
}

void Spawner::SpawnBONUSArrow(SDL_Renderer* renderer, int Ticks, ArrowType* arrowType)
{
	Arrow* arrow = nullptr;
	int arrowSpeed = 12;
	switch (arrowType->Direction)
	{
	case 0:
		arrow = new Arrow(window->IsLoggingEnabled, LeftArrow->x, window->logicalHeight + (Ticks * arrowSpeed), new Vector2(0, -arrowSpeed), arrowType);
		LeftArrows.push_back(arrow);
		break;
	case 1:
		arrow = new Arrow(window->IsLoggingEnabled, DownArrow->x, window->logicalHeight + (Ticks * arrowSpeed), new Vector2(0, -arrowSpeed), arrowType);
		DownArrows.push_back(arrow);
		break;
	case 2:
		arrow = new Arrow(window->IsLoggingEnabled, UpArrow->x, window->logicalHeight + (Ticks * arrowSpeed), new Vector2(0, -arrowSpeed), arrowType);
		UpArrows.push_back(arrow);
		break;
	case 3:
		arrow = new Arrow(window->IsLoggingEnabled, RightArrow->x, window->logicalHeight + (Ticks * arrowSpeed), new Vector2(0, -arrowSpeed), arrowType);
		RightArrows.push_back(arrow);
		break;
	default:
		SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Invalid Arrow Direction Declared (Spawning Arrow)", Logger::GetTimestamp().c_str());
		return;
	}
	arrow->Init(window);
	if (arrow->Type->Type == 2)
	{
		Type2Arrows.push_back(arrow);
		Type2ArrowDirections.push_back(arrowType->GetEndDirection());
	}
	newArrows.push_back(arrow);
}

Arrow* Spawner::GetCollision(int direction, int Ticks)
{
	switch (direction)
	{
	case 0:
		if (LeftArrows.size() == 0) return nullptr;

		LeftArrows[0]->HitAccuracy = trunc(10 - (abs(LeftArrows[0]->y - LeftArrow->y) / static_cast<double>(10))) / 10;
		if (LeftArrows[0]->HitAccuracy < 0) LeftArrows[0]->HitAccuracy = 0;

		if (LeftArrows[0]->HitAccuracy > 0)
		{
			Arrow* arrow = LeftArrows[0];
			arrow->Hit();
			LeftArrows.erase(LeftArrows.begin());
			return arrow;
		}
		else return nullptr;
	case 1:
		if (DownArrows.size() == 0) return nullptr;

		DownArrows[0]->HitAccuracy = trunc(10 - (abs(DownArrows[0]->y - DownArrow->y) / static_cast<double>(10))) / 10;
		if (DownArrows[0]->HitAccuracy < 0) DownArrows[0]->HitAccuracy = 0;

		if (DownArrows[0]->HitAccuracy > 0)
		{
			Arrow* arrow = DownArrows[0];
			arrow->Hit();
			DownArrows.erase(DownArrows.begin());
			return arrow;
		}
		else return nullptr;
	case 2:
		if (UpArrows.size() == 0) return nullptr;

		UpArrows[0]->HitAccuracy = trunc(10 - (abs(UpArrows[0]->y - UpArrow->y) / static_cast<double>(10))) / 10;
		if (UpArrows[0]->HitAccuracy < 0) UpArrows[0]->HitAccuracy = 0;

		if (UpArrows[0]->HitAccuracy > 0)
		{
			Arrow* arrow = UpArrows[0];
			arrow->Hit();
			UpArrows.erase(UpArrows.begin());
			return arrow;
		}
		else return nullptr;
	case 3:
		if (RightArrows.size() == 0) return nullptr;

		RightArrows[0]->HitAccuracy = trunc(10 - (abs(RightArrows[0]->y - RightArrow->y) / static_cast<double>(10))) / 10;
		if (RightArrows[0]->HitAccuracy < 0) RightArrows[0]->HitAccuracy = 0;

		if (RightArrows[0]->HitAccuracy > 0)
		{
			Arrow* arrow = RightArrows[0];
			arrow->Hit();
			RightArrows.erase(RightArrows.begin());
			return arrow;
		}
		else return nullptr;
	default:
		SDL_LogWarn(SPAWNER_LOG_CATEGORY_ERROR, "%s Invalid Arrow Direction Declared (Getting Collision)", Logger::GetTimestamp().c_str());
		return nullptr;
	}
}
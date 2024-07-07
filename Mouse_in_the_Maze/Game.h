#pragma once 
#include <SDL.h>
#include <SDL_ttf.h>
#include <fstream>
#include <ctype.h>
#include <ctime>
#include <vector>

#include "Sprite.h"
#include "Text.h"
#include "Moving.h"
#include "Player.h"
#include "Projectile.h"
#include "Projectile_Spawner.h"

#include <iostream>
using namespace std;

#define CLOSE_APP 0
#define INTRO 1
#define MENU 2
#define SELECT_LVL 3

#define GAME 5
#define RULES 6
#define SCORES 7

struct player_profile
{
	char name[16];
	double forest;
	double swam;
	double desert;
	double dungeon;
	double volcano;

	player_profile()
	{
		name[0] = '\0';
		forest = 0;
		swam = 0;
		desert = 0;
		dungeon = 0;
		volcano = 0;
	}
};

class Game
{
	SDL_Window* window;
	SDL_Surface* surface;
	TTF_Font* big_font;
	TTF_Font* font;
	TTF_Font* input_font;

	SDL_Event event;

	int lvl_w;
	int lvl_h;
	Sprite scene_interface;
	Sprite background;
	Sprite** field;
	Sprite cheese;
	vector<Sprite*> bonfires;
	vector<Sprite*> hp;
	vector<Projectile*> projectiles;
	vector<Projectile_Spawner*> ps;
	//vector<Text*> texts;
	Player mouse;

	player_profile profile;

	string lvl_name;

	SDL_Point spawner;
	
	bool key_w_state;
	bool key_a_state;
	bool key_s_state;
	bool key_d_state;

	int game_mode;

	bool is_running;
	bool is_scene_load;
	bool need_draw;

	double start_time;

	int width;
	int height;
	
	void Draw_All(bool update = true);
	void Clear_Scene();
	void Collision_Objects();
	void Add_to_top();
	void Load_Profile();
	void Intro();
	void Menu();
	void Select_Lvl();
	void Rules();
	void Scores();
	void Game_process();

public:

	Game();
	~Game();
	bool Is_Running() { return is_running; };
	void Update();
};
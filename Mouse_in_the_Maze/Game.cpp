#include "Game.h"

void Game::Draw_All(bool update)
{
	background.Draw(surface);

	int x_offset = (width / 2) - (mouse.Get_Rect().x + mouse.Get_Rect().w / 2);
	int y_offset = (height / 2) - (mouse.Get_Rect().y + mouse.Get_Rect().h / 2);

	for(int i = 0; i < lvl_w; i++)
	{
		for(int j = 0; j < lvl_h; j++)
		{
			field[i][j].Draw(surface, x_offset, y_offset);
		}
	}

	for(int i = 0; i < bonfires.size(); i++)
	{
		bonfires[i]->Draw(surface, x_offset, y_offset);
	}

	for (int i = 0; i < hp.size(); i++)
	{
		hp[i]->Draw(surface, x_offset, y_offset);
	}

	cheese.Draw(surface, x_offset, y_offset);

	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->Draw(surface, x_offset, y_offset);
	}

	mouse.Draw(surface, x_offset, y_offset);

	scene_interface.Draw(surface);

	if(update)
	{
		SDL_UpdateWindowSurface(window);
		need_draw = false;
	}
}

void Game::Clear_Scene()
{
	background.Clear_Sprite();

	for (int i = 0; i < lvl_h; i++)
	{
		delete[] field[i];
	}
	delete[] field;
	field = nullptr;

	for (int i = 0; i < bonfires.size(); i++)
	{
		delete bonfires[i];
	}
	bonfires.clear();

	for (int i = 0; i < hp.size(); i++)
	{
		delete hp[i];
	}
	hp.clear();

	for (int i = 0; i < projectiles.size(); i++)
	{
		delete projectiles[i];
	}
	projectiles.clear();


	for (int i = 0; i < ps.size(); i++)
	{
		delete ps[i];
	}
	ps.clear();

	scene_interface.Clear_Sprite();

	lvl_w = 0;
	lvl_h = 0;

	is_scene_load = false;
}

void Game::Collision_Objects()
{
	SDL_Rect a = mouse.Get_Rect();
	SDL_Rect b;

	for (int i = 0; i < bonfires.size(); i++)
	{
		b = bonfires[i]->Get_Rect();
		if(SDL_HasIntersection(&a, &b))
		{
			spawner.x = bonfires[i]->Get_Rect().x;
			spawner.y = bonfires[i]->Get_Rect().y;
			break;
		}
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		b = projectiles[i]->Get_Rect();
		if (SDL_HasIntersection(&a, &b))
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);

			mouse.Add_hp(-50);
			if(mouse.Get_hp() <= 0)
			{
				mouse.Set_hp(100);
				mouse.Set_Position(spawner.x, spawner.y);
			}

			break;
		}
	}

	for (int i = 0; i < hp.size(); i++)
	{
		b = hp[i]->Get_Rect();
		if (SDL_HasIntersection(&a, &b))
		{
			delete hp[i];
			hp.erase(hp.begin() + i);

			mouse.Add_hp(25);
			break;
		}
	}

	b = cheese.Get_Rect();
	if (SDL_HasIntersection(&a, &b))
	{
		Clear_Scene();

		scene_interface.Set_Sprite("sprites\\final.bmp");
		scene_interface.Set_Size(700, 500);
		scene_interface.Set_Position(50, 50);
		scene_interface.Draw(surface);

		SDL_Surface* text_surf;
		SDL_Color text_col = { 0, 0, 0 };
		SDL_Rect text_pos = { 0, 0, 0, 0 };

		string s = "Поздравляем!!!";
		text_surf = TTF_RenderText_Blended(big_font, s.c_str(), text_col);
		text_pos.x = 50 + (700 - text_surf->w) / 2;
		text_pos.y = 80;
		text_pos.w = text_surf->w;
		text_pos.h = text_surf->h;
		SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
		SDL_FreeSurface(text_surf);

		s = "Вы прошли уровень!";
		text_surf = TTF_RenderText_Blended(big_font, s.c_str(), text_col);
		text_pos.x = 50 + (700 - text_surf->w) / 2;
		text_pos.y += text_surf->h * 1.5;
		text_pos.w = text_surf->w;
		text_pos.h = text_surf->h;
		SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
		SDL_FreeSurface(text_surf);

		char text[100];
		SDL_itoa((clock() - start_time) / 1000, text, 10);
		char txt[100];
		SDL_itoa(((int)(clock() - start_time) % 1000) / 100, txt, 10);

		strcat_s(text, ".");
		strcat_s(text, txt);

		s = "Время прохождения - ";
		s += text;
		s += " секунд.";

		text_surf = TTF_RenderText_Blended(font, s.c_str(), text_col);
		text_pos.x = 50 + (700 - text_surf->w) / 2;
		text_pos.y = 300;
		text_pos.w = text_surf->w;
		text_pos.h = text_surf->h;
		SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
		SDL_FreeSurface(text_surf);

		bool best = false;

		if(lvl_name == "sprites\\forest\\" && (clock() - start_time < profile.forest || profile.forest == 0))
		{
			profile.forest = clock() - start_time;
			best = true;
		}
		else if(lvl_name == "sprites\\swam\\" && (clock() - start_time < profile.swam || profile.swam == 0))
		{
			profile.swam = clock() - start_time;
			best = true;
		}
		else if (lvl_name == "sprites\\desert\\" && (clock() - start_time < profile.desert || profile.desert == 0))
		{
			profile.desert = clock() - start_time;
			best = true;
		}
		else if (lvl_name == "sprites\\dungeon\\" && (clock() - start_time < profile.dungeon || profile.dungeon == 0))
		{
			profile.dungeon = clock() - start_time;
			best = true;
		}
		else if (lvl_name == "sprites\\volcano\\" && (clock() - start_time < profile.volcano || profile.volcano == 0))
		{
			profile.volcano = clock() - start_time;
			best = true;
		}

		if(best)
		{
			s = "Это ваш лучший результат";
			text_surf = TTF_RenderText_Blended(font, s.c_str(), text_col);
			text_pos.x = 50 + (700 - text_surf->w) / 2;
			text_pos.y += text_surf->h * 1.5;
			text_pos.w = text_surf->w;
			text_pos.h = text_surf->h;
			SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
			SDL_FreeSurface(text_surf);
		}

		SDL_UpdateWindowSurface(window);

		Add_to_top();
		while(true)
		{
			SDL_WaitEvent(&event);

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.y > 450 && event.button.y < 500 && event.button.x > 300 && event.button.x < 500)
				{
					Clear_Scene();
					game_mode = MENU;
					break;
				}
				else if (event.type == SDL_QUIT)
				{
					game_mode = CLOSE_APP;
					break;
				}
			}
		}
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		b = projectiles[i]->Get_Rect();
		for(int j = 0; j < lvl_h; j++)
		{
			for(int k = 0; k < lvl_w; k++)
			{
				a = field[j][k].Get_Rect();
				if (SDL_HasIntersection(&a, &b) && field[j][k].Get_Object_Name() == "barrier")
				{
					delete projectiles[i];
					projectiles.erase(projectiles.begin() + i);
					break;
				}
			}
		}
	}
}

void Game::Add_to_top()
{
	player_profile* profiles = nullptr;
	double* scores = nullptr;

	int kol = 0;
	bool ins = false;

	ifstream in_file("save.txt");
	if (in_file.is_open())
	{
		in_file >> kol;
		profiles = new player_profile[kol + 1];
		scores = new double[kol + 1];

		for (int i = 0; i < kol; i++)
		{
			in_file >> profiles[i].name;
			in_file >> profiles[i].forest;
			in_file >> profiles[i].swam;
			in_file >> profiles[i].desert;
			in_file >> profiles[i].dungeon;
			in_file >> profiles[i].volcano;

			if (!strcmp(profile.name, profiles[i].name))
			{
				profiles[i] = profile;
				ins = true;
			}
			scores[i] = 0;
			scores[i] += profiles[i].forest == 0 ? 999999 : profiles[i].forest;
			scores[i] += profiles[i].swam == 0 ? 999999 : profiles[i].swam;
			scores[i] += profiles[i].desert == 0 ? 999999 : profiles[i].desert;
			scores[i] += profiles[i].dungeon == 0 ? 999999 : profiles[i].dungeon;
			scores[i] += profiles[i].volcano == 0 ? 999999 : profiles[i].volcano;
		}

		if(!ins)
		{
			profiles[kol] = profile;
			scores[kol] = 0;
			scores[kol] += profile.forest == 0 ? 999999 : profile.forest;
			scores[kol] += profile.swam == 0 ? 999999 : profile.swam;
			scores[kol] += profile.desert == 0 ? 999999 : profile.desert;
			scores[kol] += profile.dungeon == 0 ? 999999 : profile.dungeon;
			scores[kol] += profile.volcano == 0 ? 999999 : profile.volcano;

			kol++;
		}
	}
	else
	{
		profiles = new player_profile[1];
		scores = new double[1];

		kol++;
		profiles[0] = profile;
		scores[0] = 0;
		scores[0] += profile.forest == 0 ? 999999 : profile.forest;
		scores[0] += profile.swam == 0 ? 999999 : profile.swam;
		scores[0] += profile.desert == 0 ? 999999 : profile.desert;
		scores[0] += profile.dungeon == 0 ? 999999 : profile.dungeon;
		scores[0] += profile.volcano == 0 ? 999999 : profile.volcano;
	}
	in_file.close();

	ofstream out_file;
	out_file.open("save.txt");
	if(out_file.is_open())
	{
		for (int step = 0; step < kol - 1; step++) 
		{
			int min_idx = step;
			for (int i = step + 1; i < kol; i++) 
			{

				if (scores[i] < scores[min_idx])
					min_idx = i;
			}

			double temp_s = scores[min_idx];
			scores[min_idx] = scores[step];
			scores[step] = temp_s;

			player_profile temp_p = profiles[min_idx];
			profiles[min_idx] = profiles[step];
			profiles[step] = temp_p;
		}


		out_file << kol << endl;
		for(int i = 0; i < kol; i++)
		{
			out_file << profiles[i].name << endl;
			out_file << profiles[i].forest << endl;
			out_file << profiles[i].swam << endl;
			out_file << profiles[i].desert << endl;
			out_file << profiles[i].dungeon << endl;
			out_file << profiles[i].volcano << endl;
		}
	}

	delete[] profiles;
	delete[] scores;
}

void Game::Load_Profile()
{
	if (!is_scene_load)
	{
		background.Set_Sprite("sprites\\menu_background.bmp");
		background.Set_Size(800, 600);

		scene_interface.Set_Sprite("sprites\\nickname_input.bmp");
		scene_interface.Set_Position(100, 200);
		scene_interface.Set_Size(600, 200);

		is_scene_load = true;
		Draw_All(false);
	}
	int size = 0;

	SDL_Surface* text_surf;
	SDL_Color text_col = { 0, 0, 0 };
	SDL_Rect text_pos = { 0, 0, 0, 0 };

	string s;
	
	profile.forest = 0;
	profile.swam = 0;
	profile.desert = 0;
	profile.dungeon = 0;
	profile.volcano = 0;


	while (SDL_WaitEvent(&event))
	{
		Draw_All(false);

		s = "Введите имя:";
		text_surf = TTF_RenderText_Blended(big_font, s.c_str(), text_col);
		text_pos.x = (800 - text_surf->w) / 2;
		text_pos.y = 250;
		text_pos.w = text_surf->w;
		text_pos.h = text_surf->h;
		SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
		SDL_FreeSurface(text_surf);

		if(profile.name[0] != '\0')
		{
			text_surf = TTF_RenderText_Blended(input_font, profile.name, text_col);
			text_pos.x = (800 - text_surf->w) / 2;
			text_pos.y += text_surf->h;
			text_pos.w = text_surf->w;
			text_pos.h = text_surf->h;
			SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
			SDL_FreeSurface(text_surf);
		}

		SDL_UpdateWindowSurface(window);

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_RETURN && size > 0)
			{
				Clear_Scene();
				game_mode = MENU;
				break;
			}
			else if (event.key.keysym.sym == SDLK_SPACE && size > 0 && size < 16)
			{
				profile.name[size] = ' ';
				size++;
			}
			else if (event.key.keysym.sym == SDLK_BACKSPACE && size > 0)
			{
				size--;
				profile.name[size] = '\0';
			}
			else if (size < 16 && event.key.keysym.sym > 32 && event.key.keysym.sym < 127)
			{
				profile.name[size] = (char)event.key.keysym.sym;
				size++;
			}
		}
		else if (event.type == SDL_QUIT)
		{
			game_mode = CLOSE_APP;
			break;
		}
	}

	ifstream file;
	int file_size = 0;
	player_profile temp_profile;

	file.open("save.txt");;
	if(file.is_open())
	{
		file >> file_size;
		for(int i = 0; i < file_size; i++)
		{
			file >> temp_profile.name;
			file >> temp_profile.forest;
			file >> temp_profile.swam;
			file >> temp_profile.desert;
			file >> temp_profile.dungeon;
			file >> temp_profile.volcano;

			if(!strcmp(profile.name, temp_profile.name))
			{
				profile = temp_profile;
			}
		}
	}
}

void Game::Intro()
{
	if(!is_scene_load)
	{
		scene_interface.Set_Sprite("sprites\\intro.bmp");
		scene_interface.Set_Position(0, 0);
		scene_interface.Set_Size(800, 600);
		is_scene_load = true;
		need_draw = true;
	}

	SDL_PollEvent(&event);
	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN)
	{
		Clear_Scene();
		Load_Profile();
		game_mode = MENU;
	}
	else if (event.type == SDL_QUIT)
	{
		game_mode = CLOSE_APP;
	}
}

void Game::Menu()
{
	if (!is_scene_load)
	{
		scene_interface.Set_Sprite("sprites\\menu.bmp");
		scene_interface.Set_Position(0, 0);
		scene_interface.Set_Size(800, 600);
		is_scene_load = true;
		need_draw = true;
	}

	SDL_PollEvent(&event);
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(event.button.x > 550 && event.button.x < 750)
		{
			if(event.button.y > 100 && event.button.y < 150)
			{
				Clear_Scene();
				game_mode = SELECT_LVL;
			}
			else if (event.button.y > 160 && event.button.y < 210)
			{
				Clear_Scene();
				game_mode = RULES;
			}
			else if (event.button.y > 220 && event.button.y < 270)
			{
				Clear_Scene();
				game_mode = SCORES;
			}
			else if (event.button.y > 280 && event.button.y < 330)
			{
				Clear_Scene();
				for(int i = 0; i < 16; i++)
				{
					profile.name[i] = '\0';
				}
				Load_Profile();
			}
			else if (event.button.y > 340 && event.button.y < 390)
			{
				game_mode = CLOSE_APP;
			}
		}


	}
	else if (event.type == SDL_QUIT)
	{
		game_mode = CLOSE_APP;
	}
}

void Game::Select_Lvl()
{
	if (!is_scene_load)
	{
		scene_interface.Set_Sprite("sprites\\lvl_select.bmp");
		scene_interface.Set_Position(0, 0);
		scene_interface.Set_Size(800, 600);
		is_scene_load = true;
		need_draw = true;
	}

	SDL_PollEvent(&event);
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.y > 320 && event.button.y < 400)
		{
			if (event.button.x > 86 && event.button.x < 166)
			{
				start_time = clock();
				lvl_name = "sprites\\forest\\";
				Clear_Scene();
				game_mode = GAME;
			}
			else if (event.button.x > 224 && event.button.x < 303)
			{
				start_time = clock();
				lvl_name = "sprites\\swam\\";
				Clear_Scene();
				game_mode = GAME;
			}
			else if (event.button.x > 362 && event.button.x < 441)
			{
				start_time = clock();
				lvl_name = "sprites\\desert\\";
				Clear_Scene();
				game_mode = GAME;
			}
			else if (event.button.x > 500 && event.button.x < 580)
			{
				start_time = clock();
				lvl_name = "sprites\\dungeon\\";
				Clear_Scene();
				game_mode = GAME;
			}
			else if (event.button.x > 638 && event.button.x < 717)
			{
				start_time = clock();
				lvl_name = "sprites\\volcano\\";
				Clear_Scene();
				game_mode = GAME;
			}
		}
		else if(event.button.y > 450 && event.button.y < 500 && event.button.x > 600 && event.button.x < 700)
		{
			Clear_Scene();
			game_mode = MENU;
		}
	}
	else if (event.type == SDL_QUIT)
	{
		game_mode = CLOSE_APP;
	}
}

void Game::Rules()
{
	if (!is_scene_load)
	{
		background.Set_Sprite("sprites\\menu_background.bmp");
		background.Set_Size(800, 600);

		scene_interface.Set_Sprite("sprites\\rules.bmp");
		scene_interface.Set_Position(50, 50);
		scene_interface.Set_Size(700, 500);

		is_scene_load = true;
		need_draw = true;
	}

	Draw_All();

	while (true)
	{
		SDL_WaitEvent(&event);

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.y > 450 && event.button.y < 500 && event.button.x > 300 && event.button.x < 500)
			{
				Clear_Scene();
				game_mode = MENU;
				break;
			}
			else if (event.type == SDL_QUIT)
			{
				game_mode = CLOSE_APP;
				break;
			}
		}
	}
}

void Game::Scores()
{
	if (!is_scene_load)
	{
		background.Set_Sprite("sprites\\menu_background.bmp");
		background.Set_Size(800, 600);

		scene_interface.Set_Sprite("sprites\\top.bmp");
		scene_interface.Set_Position(50, 50);
		scene_interface.Set_Size(700, 500);

		is_scene_load = true;
		Draw_All(false);
	}
	int size = 0;

	SDL_Surface* text_surf;
	SDL_Color text_col = { 0, 0, 0 };
	SDL_Rect text_pos = { 0, 0, 0, 0 };

	string s;

	ifstream file("save.txt");
	if (file.is_open())
	{
		int size;
		
		player_profile profiles[10];

		file >> size;
		for (int i = 0; i < size && i < 10; i++)
		{
			file >> profiles[i].name;
			file >> profiles[i].forest;
			file >> profiles[i].swam;
			file >> profiles[i].desert;
			file >> profiles[i].dungeon;
			file >> profiles[i].volcano;

			text_surf = TTF_RenderText_Blended(input_font, profiles[i].name, text_col);
			text_pos.x = 60;
			text_pos.y = 100 + (30 * i);
			text_pos.w = text_surf->w;
			text_pos.h = text_surf->h;
			SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
			SDL_FreeSurface(text_surf);

			char text[100];
			char txt[100];

			//
			SDL_itoa(profiles[i].forest / 1000, text, 10);
			SDL_itoa(((int)profiles[i].forest % 1000) / 10, txt, 10);

			strcat_s(text, ".");
			strcat_s(text, txt);
			strcat_s(text, "c");

			text_surf = TTF_RenderText_Blended(input_font, text, text_col);
			text_pos.x = 230;
			text_pos.y = 100 + (30 * i);
			text_pos.w = text_surf->w;
			text_pos.h = text_surf->h;
			SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
			SDL_FreeSurface(text_surf);
			//
			SDL_itoa(profiles[i].swam / 1000, text, 10);
			SDL_itoa(((int)profiles[i].swam % 1000) / 10, txt, 10);

			strcat_s(text, ".");
			strcat_s(text, txt);
			strcat_s(text, "c");

			text_surf = TTF_RenderText_Blended(input_font, text, text_col);
			text_pos.x = 320;
			text_pos.y = 100 + (30 * i);
			text_pos.w = text_surf->w;
			text_pos.h = text_surf->h;
			SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
			SDL_FreeSurface(text_surf);
			//
			SDL_itoa(profiles[i].desert / 1000, text, 10);
			SDL_itoa(((int)profiles[i].desert % 1000) / 10, txt, 10);

			strcat_s(text, ".");
			strcat_s(text, txt);
			strcat_s(text, "c");

			text_surf = TTF_RenderText_Blended(input_font, text, text_col);
			text_pos.x = 420;
			text_pos.y = 100 + (30 * i);
			text_pos.w = text_surf->w;
			text_pos.h = text_surf->h;
			SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
			SDL_FreeSurface(text_surf);
			//
			SDL_itoa(profiles[i].dungeon / 1000, text, 10);
			SDL_itoa(((int)profiles[i].dungeon % 1000) / 10, txt, 10);

			strcat_s(text, ".");
			strcat_s(text, txt);
			strcat_s(text, "c");

			text_surf = TTF_RenderText_Blended(input_font, text, text_col);
			text_pos.x = 530;
			text_pos.y = 100 + (30 * i);
			text_pos.w = text_surf->w;
			text_pos.h = text_surf->h;
			SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
			SDL_FreeSurface(text_surf);
			//
			SDL_itoa(profiles[i].volcano / 1000, text, 10);
			SDL_itoa(((int)profiles[i].volcano % 1000) / 10, txt, 10);

			strcat_s(text, ".");
			strcat_s(text, txt);
			strcat_s(text, "c");

			text_surf = TTF_RenderText_Blended(input_font, text, text_col);
			text_pos.x = 645;
			text_pos.y = 100 + (30 * i);
			text_pos.w = text_surf->w;
			text_pos.h = text_surf->h;
			SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
			SDL_FreeSurface(text_surf);
		}
	}


	SDL_UpdateWindowSurface(window);


	while (true)
	{
		SDL_WaitEvent(&event);

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.y > 450 && event.button.y < 500 && event.button.x > 300 && event.button.x < 500)
			{
				Clear_Scene();
				game_mode = MENU;
				break;
			}
			else if (event.type == SDL_QUIT)
			{
				game_mode = CLOSE_APP;
				break;
			}
		}
	}
}

void Game::Game_process()
{
	if (!is_scene_load)
	{
		ifstream lvl(lvl_name + "lvl.txt");
		if(!lvl.is_open())
		{
			game_mode = CLOSE_APP;
			return;
		}

		lvl >> lvl_w;
		lvl >> lvl_h;

		int temp;
		field = new Sprite* [lvl_h];
		for(int i = 0; i < lvl_h; i++)
		{
			field[i] = new Sprite[lvl_w];
			for(int j = 0; j < lvl_w; j++)
			{
				lvl >> temp;

				if(temp == 0)
				{
					field[i][j].Set_Object_Name("barrier");
					field[i][j].Set_Sprite(lvl_name + "barrier.bmp");
					field[i][j].Set_Position(j * 128, i * 128);
					field[i][j].Set_Size(128, 128);
				}
				else
				{
					field[i][j].Set_Object_Name("field");
					field[i][j].Set_Sprite(lvl_name + "field.bmp");
					field[i][j].Set_Position(j * 128, i * 128);
					field[i][j].Set_Size(128, 128);
				}
			}
		}

		int c_x;
		int c_y;
		lvl >> c_x;
		lvl >> c_y;
		cheese.Set_Position(c_x * 128 + 32, c_y * 128 + 32);

		lvl >> temp;
		Sprite* t;
		for(int i = 0; i < temp; i++)
		{
			lvl >> c_x;
			lvl >> c_y;

			if(i == 0)
			{
				spawner.x = c_x * 128 + 32;
				spawner.y = c_y * 128 + 32;
				mouse.Set_Position(spawner.x, spawner.y);
			}

			t = new Sprite;
			t->Set_Size(64, 64);
			t->Set_Position(c_x * 128 + 32, c_y * 128 + 32);
			t->Set_Sprite("sprites\\fire.bmp");
			bonfires.push_back(t);
		}

		Projectile_Spawner* pst;
		lvl >> temp;
		for(int i = 0; i < temp; i++)
		{
			pst = new Projectile_Spawner();
			lvl >> c_x;
			pst->Set_Dir(c_x);
			lvl >> c_x;
			lvl >> c_y;
			pst->Set_Position(c_x * 128, c_y * 128);
			lvl >> c_x;
			lvl >> c_y;
			pst->Set_spawner(c_x, c_y);
			ps.push_back(pst);
		}

		lvl >> temp;
		for(int i = 0; i < temp; i++)
		{
			lvl >> c_x;
			lvl >> c_y;

			t = new Sprite;
			t->Set_Sprite("sprites\\hp.bmp");
			t->Set_Size(64, 64);
			t->Set_Position(c_x * 128 + 32, c_y * 128 + 32);

			hp.push_back(t);
		}

		background.Set_Sprite(lvl_name + "background.bmp");
		background.Set_Size(800, 600);


		scene_interface.Set_Sprite("sprites\\game_interface.bmp");
		scene_interface.Set_Size(80, 149);

		key_w_state = false;
		key_a_state = false;
		key_s_state = false;
		key_d_state = false;

		mouse.Set_hp(100);

		is_scene_load = true;
	}

	SDL_Point dir;
	dir.x = 0;
	dir.y = 0;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			game_mode = 0;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				key_w_state = true;
				break;
			case SDLK_a:
				key_a_state = true;
				break;
			case SDLK_s:
				key_s_state = true;
				break;
			case SDLK_d:
				key_d_state = true;
				break;
			case SDLK_r:
				mouse.Set_Position(spawner.x, spawner.y);
				mouse.Set_hp(100);
				break;
			case SDLK_ESCAPE:
				Clear_Scene();
				game_mode = MENU;
				break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				key_w_state = false;
				break;
			case SDLK_a:
				key_a_state = false;
				break;
			case SDLK_s:
				key_s_state = false;
				break;
			case SDLK_d:
				key_d_state = false;
				break;
			}
		}
	}

	if(key_w_state)
	{
		dir.y = -1;
	}
	if (key_a_state)
	{
		dir.x = -1;
	}
	if (key_s_state)
	{
		dir.y = 1;
	}
	if (key_d_state)
	{
		dir.x = 1;
	}
	
	SDL_Rect a = mouse.Get_Rect();
	SDL_Rect b;
	a.x += dir.x * mouse.Get_Speed();
	a.y += dir.y * mouse.Get_Speed();

	if(a.x > 0 && a.x < lvl_w * 128 - 64 && a.y > 0 && a.y < lvl_h * 128 - 64)
	{
		for (int i = 0; i < lvl_h; i++)
		{
			for (int j = 0; j < lvl_w; j++)
			{
				b = field[i][j].Get_Rect();
				if (SDL_HasIntersection(&a, &b) && field[i][j].Get_Object_Name() == "barrier")
				{
					dir.x = 0;
					dir.y = 0;
				}
			}
		}

		mouse.Set_Direction(dir.x, dir.y);
		mouse.Move();
	}

	for (int i = 0; i < ps.size(); i++)
	{
		ps[i]->Update(&projectiles, lvl_name + "projectile");
	}
	for(int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->Move();
	}

	Collision_Objects();
	Draw_All(false);

	SDL_Surface* text_surf;
	SDL_Color text_col = { 255, 255, 255 };
	SDL_Rect text_pos = { 90, 24, 0, 0 };
	char text[100];

	SDL_itoa(mouse.Get_hp(), text, 10);
	text_surf = TTF_RenderText_Blended(big_font, text, text_col);
	text_pos.w = text_surf->w;
	text_pos.h = text_surf->h;
	SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
	SDL_FreeSurface(text_surf);

	SDL_itoa((clock() - start_time) / 1000, text, 10);
	char txt[100];
	SDL_itoa(((int)(clock() - start_time) % 1000) / 100, txt, 10);

	strcat_s(text, ".");
	strcat_s(text, txt);
	strcat_s(text, " с");


	text_surf = TTF_RenderText_Blended(big_font, text, text_col);
	text_pos.y = 95;
	text_pos.w = text_surf->w;
	text_pos.h = text_surf->h;
	SDL_BlitSurface(text_surf, NULL, surface, &text_pos);
	SDL_FreeSurface(text_surf);

	SDL_UpdateWindowSurface(window);
}


/////////////////////////////////////

Game::Game()
{
	width = 800;
	height = 600;

	window = nullptr;
	surface = nullptr;
	big_font = nullptr;
	is_running = false;

	window = SDL_CreateWindow("Mouse in the Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window) 
	{
		cout << SDL_GetError() << endl;
		return;
	}

	surface = SDL_GetWindowSurface(window);

	big_font =  TTF_OpenFont("Izhitsa.ttf", 64);
	if(!big_font)
	{
		cout << TTF_GetError() << endl;
		return;
	}

	font = TTF_OpenFont("Izhitsa.ttf", 32);
	if (!font)
	{
		cout << TTF_GetError() << endl;
		return;
	}

	input_font = TTF_OpenFont("CharisSILR.ttf", 24);
	if (!input_font)
	{
		cout << TTF_GetError() << endl;
		return;
	}

	cheese.Set_Sprite("sprites\\cheese.bmp");
	cheese.Set_Size(64, 64);

	game_mode = 1;
	is_running = true;
	need_draw = true;
	is_scene_load = false;
}

Game::~Game()
{
	if(surface)
	{
		SDL_FreeSurface(surface);
	}

	if(big_font)
	{
		TTF_CloseFont(big_font);
	}

	key_w_state = false;
	key_a_state = false;
	key_s_state = false;
	key_d_state = false;
}

void Game::Update()
{
	switch (game_mode)
	{
	case INTRO:
		Intro();
		break;
	case MENU:
		Menu();
		break;
	case SELECT_LVL:
		Select_Lvl();
		break;
	case GAME:
		Game_process();
		break;
	case RULES:
		Rules();
		break;
	case SCORES:
		Scores();
		break;
	default:
		is_running = false;
		break;
	}

	if(need_draw)
	{
		Draw_All();
	}
}


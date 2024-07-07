#include "Game.h"

void Game::menu()
{
	int cur = 1;
	while(cur)
	{
		switch(cur)
		{
		case 1://заставка
			cur = intro();
			break;
		case 2://меню
			cur = game_menu();
			break;
		case 3://игра
			cur = game();
			break;
		case 4://правила
			cur = ruls();
			break;
		case 5://рекорды
			cur = records();
			break;
		}
	}
}

int Game::intro()
{
	Sprite background;
	background.Set_Sprite("intro.bmp");
	background.Draw(surface);

	//SDL_Flip(surface);
	SDL_UpdateWindowSurface(window);

	while(SDL_WaitEvent(&event))
	{
		if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN)
		{
			return 2;
		}
		else if(event.type == SDL_QUIT)
		{
			return 0;
		}
	}
}

int Game::game_menu()
{
	Sprite background;
	background.Set_Sprite("menu.bmp");
	background.Draw(surface);

	//SDL_Flip(surface);
	SDL_UpdateWindowSurface(window);

	while(SDL_WaitEvent(&event))
	{
		if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			int x;
			int y;

			SDL_GetMouseState(&x, &y);

			if(x > 256 && x < 640)
			{
				if(y > 300 && y < 360)
				{
					return 3;
				}
				else if(y > 370 && y < 430)
				{
					return 4;
				}
				else if(y > 440 && y < 500)
				{
					return 5;
				}
				else if(y > 510 && y < 570)
				{
					return 0;
				}
			}
		}
		else if(event.type == SDL_QUIT)
		{
			return 0;
		}
	}
}

void Game::draw_lvl(int w, int h, Moving& housewife, Moving& barabashka)
{
	int cur_tex_x;
	int cur_tex_y;

	for(int i = 0; i < 5; i++)
	{
		cur_tex_y = housewife.y - 2 + i;

		for(int j = 0; j < 7; j++)
		{
			cur_tex_x = housewife.x - 3 + j;

			if(cur_tex_x < 0 || cur_tex_y < 0 || cur_tex_x >= w || cur_tex_y >= h)
			{
				background_atlas.Draw(surface, 0, 384, 128, 128, 128 * j, 128 * i + 128);
			}
			else
			{
				switch(lvl[cur_tex_y][cur_tex_x])
				{
				case ' ':
					background_atlas.Draw(surface, 0, 0, 128, 128, 128 * j, 128 * i + 128);
					break;
				case '-':
					background_atlas.Draw(surface, 128, 0, 128, 128, 128 * j, 128 * i + 128);
					break;
				case '|':
					background_atlas.Draw(surface, 256, 0, 128, 128, 128 * j, 128 * i + 128);
					break;
				case '+':
					background_atlas.Draw(surface, 384, 0, 128, 128, 128 * j, 128 * i + 128);
					break;
				case 'F':
					background_atlas.Draw(surface, 0, 128, 128, 128, 128 * j, 128 * i + 128);
					break;
				case '%':
					background_atlas.Draw(surface, 128, 128, 128, 128, 128 * j, 128 * i + 128);
					break;
				case 'L':
					background_atlas.Draw(surface, 256, 128, 128, 128, 128 * j, 128 * i + 128);
					break;
				case 'J':
					background_atlas.Draw(surface, 384, 128, 128, 128, 128 * j, 128 * i + 128);
					break;
				case 'I':
					background_atlas.Draw(surface, 0, 256, 128, 128, 128 * j, 128 * i + 128);
					break;
				case '<':
					background_atlas.Draw(surface, 128, 256, 128, 128, 128 * j, 128 * i + 128);
					break;
				case 'Y':
					background_atlas.Draw(surface, 256, 256, 128, 128, 128 * j, 128 * i + 128);
					break;
				case '>':
					background_atlas.Draw(surface, 384, 256, 128, 128, 128 * j, 128 * i + 128);
					break;
				case 'P':
					items_atlas.Draw(surface,0,0,128, 128,128 * j, 128 * i + 128);
					break;
				case 'p':
					items_atlas.Draw(surface,0,128,128, 128,128 * j, 128 * i + 128);
					break;
				case 'E':
					items_atlas.Draw(surface,128,0,128, 128,128 * j, 128 * i + 128);
					break;
				case 'e':
					items_atlas.Draw(surface,128,128,128, 128,128 * j, 128 * i + 128);
					break;
				case 'B':
					items_atlas.Draw(surface,256,0,128, 128,128 * j, 128 * i + 128);
					break;
				case 'b':
					items_atlas.Draw(surface,256,128,128, 128,128 * j, 128 * i + 128);
					break;
				case 'C':
					items_atlas.Draw(surface,384,0,128, 128,128 * j, 128 * i + 128);
					break;
				case 'c':
					items_atlas.Draw(surface,384,128,128, 128,128 * j, 128 * i + 128);
					break;
				case 'W':
					items_atlas.Draw(surface,512,0,128, 128,128 * j, 128 * i + 128);
					break;
				case 'w':
					items_atlas.Draw(surface,512,128,128, 128,128 * j, 128 * i + 128);
					break;
				default:
					background_atlas.Draw(surface, 0, 0, 128, 128, 128 * j, 128 * i + 128);
					break;
				}
			}
		}
	}
	barabashka.Draw(surface, 0, 0, 128, 128, (barabashka.x - housewife.x + 3) * 128, (barabashka.y - housewife.y + 3) * 128);
	housewife.Draw(surface);
}



int Game::save(int res)
{
	Sprite nickname_input;
	nickname_input.Set_Sprite("nickname_input.bmp");
	nickname_input.Set_Position(197, 256);
	nickname_input.Draw(surface);

	Text text;
	text.Set_Font(font);
	text.Set_Color(102, 128, 153);
	text.Set_Position(285,405);
	
	char name[11];
	int size = 0;
	bool big = false;

	//SDL_Flip(surface);
	SDL_UpdateWindowSurface(window);

	while(SDL_WaitEvent(&event))
	{
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym > 32 && event.key.keysym.sym  < 127 && size < 10)
			{
				if(big && event.key.keysym.sym > 96 && event.key.keysym.sym  < 123)
				{
					name[size] =event.key.keysym.sym - 32;
				}
				else
				{
					name[size] = event.key.keysym.sym;
				}

				nickname_input.Draw(surface);

				name[size + 1] = '\0';
				text.Set_Text(name);
				text.Draw(surface);
				//SDL_Flip(surface);
				SDL_UpdateWindowSurface(window);

				size++;
			}
			else if(size > 0 && event.key.keysym.sym == SDLK_RETURN)
			{
				char* names[10];
				int time[11];

				for(int i = 0; i < 10; i++)
				{
					names[i] = new char[21];
				}

				int kol = 0;

				ifstream in_file("save.txt");
				if(in_file.is_open())
				{
					in_file >> kol;
					for(int i = 0; i < kol; i++)
					{
						in_file >> names[i];
						in_file >> time[i];
					}
				}
				in_file.close();

				int index = 0;
				while(index < kol && time[index] > res)
				{
					index++;
				}

				for(int i = 9; i > index; i--)
				{
					strcpy_s(names[i], 21, names[i - 1]);
					time[i] = time[i - 1];
				}

				if(index < 10)
				{
					strcpy_s(names[index], 21, name);
					time[index] = res;
				}

				if(kol < 10)
				{
					kol++;
				}

				ofstream out_file("save.txt");
				if(out_file.is_open())
				{
					out_file << kol << endl;
					for(int i = 0; i < kol; i++)
					{
						out_file << names[i] << ' ' << time[i] << endl;
					}
				}
				out_file.close();

				for(int i = 0; i < 10; i++)
				{
					delete[] names[i];
				}

				return 2;
			}
			else if(size > 0 && event.key.keysym.sym == SDLK_BACKSPACE)
			{
				size--;

				nickname_input.Draw(surface);

				name[size] = '\0';

				text.Set_Text(name);
				text.Draw(surface);
				//SDL_Flip(surface);
				SDL_UpdateWindowSurface(window);

				//SDL_Flip(surface);
			}
			else if(event.key.keysym.sym == SDLK_LSHIFT)
			{
				big = true;
			}
		}
		else if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LSHIFT)
		{
			big = false;
		}
		else if(event.type == SDL_QUIT)
		{
			return 0;
		}
	}
}
 

int Game::game()
{
	srand(time(0));
	//******************************************************************
	//загруза уровня
	background_atlas.Set_Sprite("background_atlas.bmp");
	items_atlas.Set_Sprite("items_atlas.bmp");

	Moving housewife;
	Moving barabashka;

	housewife.Set_Picture("housewife.bmp");
	barabashka.Set_Picture("barabashka.bmp");

	int stay_time = 250;
	int cur_stay_time = 0;
	int game_time = 0;
	int game_time_start;
	int game_time_end;
	int items_kol = 0;

	ifstream file("lvl.txt");
	if(!file.is_open())
	{
		return 0;
	}

	int lvl_w, lvl_h;

	file >> lvl_w;
	file >> lvl_h;

	file >> housewife.x;
	file >> housewife.y;

	file >> barabashka.x;
	file >> barabashka.y;

	file.get();

	lvl = new char*[lvl_h];
	for(int i = 0; i < lvl_h; i++)
	{
		lvl[i] = new char[lvl_w];
		for(int j = 0; j < lvl_w; j++)
		{
			file.get(lvl[i][j]);
			if(lvl[i][j] == 'P' ||
			   lvl[i][j] == 'E' ||
			   lvl[i][j] == 'B' ||
			   lvl[i][j] == 'C' ||
			   lvl[i][j] == 'W')
			{
				items_kol++;
			}
		}
		file.get();
	}

	housewife.Set_Position(384, 384);

	Sprite game_m;
	game_m.Set_Sprite("game_menu.bmp");

	Sprite pause;
	pause.Set_Sprite("pause.bmp");
	pause.Set_Position(177, 238);

	Text timer;
	timer.Set_Font(font);
	timer.Set_Text("0");
	timer.Set_Color(102, 128, 153);
	timer.Set_Position(200, 14);



	char temp_str[21];

	//******************************************************************

	game_m.Draw(surface);
	
	bool play = true;

	barabashka.Set_Direction(1,0);

	game_time_start = clock();
	while(play)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				return 0;
			}
			else if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
				{
					if(housewife.y - 1 > 0 && (lvl[housewife.y - 1][housewife.x] == ' ' || isdigit(lvl[housewife.y - 1][housewife.x])))
					{
						housewife.Set_Direction(0, -1);
						housewife.Move();
					}
				}
				else if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				{
					if(housewife.x + 1 < lvl_w - 1 && (lvl[housewife.y][housewife.x + 1] == ' ' || isdigit(lvl[housewife.y][housewife.x + 1])))
					{
						housewife.Set_Direction(1, 0);
						housewife.Move();
					}

				}
				else if(event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
				{
					if(housewife.y + 1 < lvl_h - 1 && (lvl[housewife.y + 1][housewife.x] == ' ' || isdigit(lvl[housewife.y + 1][housewife.x])))
					{
						housewife.Set_Direction(0, 1);
						housewife.Move();
					}

				}
				else if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				{
					if(housewife.x - 1 > 0 && (lvl[housewife.y][housewife.x - 1] == ' ' || isdigit(lvl[housewife.y][housewife.x - 1])))
					{
						housewife.Set_Direction(-1, 0);
						housewife.Move();
					}

				}
				else if(event.key.keysym.sym == SDLK_SPACE)
				{
					switch(lvl[housewife.y - 1][housewife.x])
					{
					case 'p':
						lvl[housewife.y - 1][housewife.x] = 'P';
						items_kol++;
						break;
					case 'e':
						lvl[housewife.y - 1][housewife.x] = 'E';
						items_kol++;
						break;
					case 'b':
						lvl[housewife.y - 1][housewife.x] = 'B';
						items_kol++;
						break;
					case 'c':
						lvl[housewife.y - 1][housewife.x] = 'C';
						items_kol++;
						break;
					case 'w':
						lvl[housewife.y - 1][housewife.x] = 'W';
						items_kol++;
						break;
					}

					switch(lvl[housewife.y + 1][housewife.x])
					{
					case 'p':
						lvl[housewife.y + 1][housewife.x] = 'P';
						items_kol++;
						break;
					case 'e':
						lvl[housewife.y + 1][housewife.x] = 'E';
						items_kol++;
						break;
					case 'b':
						lvl[housewife.y + 1][housewife.x] = 'B';
						items_kol++;
						break;
					case 'c':
						lvl[housewife.y + 1][housewife.x] = 'C';
						items_kol++;
						break;
					case 'w':
						lvl[housewife.y + 1][housewife.x] = 'W';
						items_kol++;
						break;
					}

					switch(lvl[housewife.y][housewife.x + 1])
					{
					case 'p':
						lvl[housewife.y][housewife.x + 1] = 'P';
						items_kol++;
						break;
					case 'e':
						lvl[housewife.y][housewife.x + 1] = 'E';
						items_kol++;
						break;
					case 'b':
						lvl[housewife.y][housewife.x + 1] = 'B';
						items_kol++;
						break;
					case 'c':
						lvl[housewife.y][housewife.x + 1] = 'C';
						items_kol++;
						break;
					case 'w':
						lvl[housewife.y][housewife.x + 1] = 'W';
						items_kol++;
						break;
					}

					switch(lvl[housewife.y][housewife.x - 1])
					{
					case 'p':
						lvl[housewife.y][housewife.x - 1] = 'P';
						items_kol++;
						break;
					case 'e':
						lvl[housewife.y][housewife.x - 1] = 'E';
						items_kol++;
						break;
					case 'b':
						lvl[housewife.y][housewife.x - 1] = 'B';
						items_kol++;
						break;
					case 'c':
						lvl[housewife.y][housewife.x - 1] = 'C';
						items_kol++;
						break;
					case 'w':
						lvl[housewife.y][housewife.x - 1] = 'W';
						items_kol++;
						break;
					}
				}

			}
			if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				int x;
				int y;

				SDL_GetMouseState(&x, &y);

				if(x > 700 && x < 800 && y > 20 && y < 60)
				{
					int pause_time = clock();
					pause.Draw(surface);
					//SDL_Flip(surface);
					SDL_UpdateWindowSurface(window);
					while(SDL_WaitEvent(&event))
					{
						if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
						{
							SDL_GetMouseState(&x, &y);
							if(x > 260 && x < 644)
							{
								if(y > 316 && y < 375)
								{
									game_time_start += clock() - pause_time;
									break;
								}
								else if(y > 386 && y < 445)
								{
									return 2;
								}
								else if(y > 456 && y < 515)
								{
									return 0;
								}
							}
						}
						else if(event.type == SDL_QUIT)
						{
							return 0;
						}
					}
				}
			}
		}
		//***************************************************************************************
		if(cur_stay_time <= 0)
		{
			barabashka.Move();
			if(isdigit(lvl[barabashka.y][barabashka.x]))
			{
				int t = 0;
				switch (lvl[barabashka.y][barabashka.x])
				{
				case '0':
					if(barabashka.dir_y == -1)
					{
						barabashka.Set_Direction(1,0);
					}
					else if(barabashka.dir_x == -1)
					{
						barabashka.Set_Direction(0,1);
					}
					break;
				case '1':
					if(barabashka.dir_y == -1)
					{
						barabashka.Set_Direction(-1,0);
					}
					else if(barabashka.dir_x == 1)
					{
						barabashka.Set_Direction(0,1);
					}
					break;
				case '2':
					if(barabashka.dir_y == 1)
					{
						barabashka.Set_Direction(-1,0);
					}
					else if(barabashka.dir_x == 1)
					{
						barabashka.Set_Direction(0,-1);
					}
					break;
				case '3':
					if(barabashka.dir_y == 1)
					{
						barabashka.Set_Direction(1,0);
					}
					else if(barabashka.dir_x == -1)
					{
						barabashka.Set_Direction(0,-1);
					}
					break;
				case '4':
					t = rand()%2;
					if(barabashka.dir_y == 1)
					{
						if(t)
						{
							barabashka.Set_Direction(1,0);
						}
						else
						{
							barabashka.Set_Direction(0,1);
						}
					}
					else if(barabashka.dir_y == -1)
					{
						if(t)
						{
							barabashka.Set_Direction(1,0);
						}
						else
						{
							barabashka.Set_Direction(0,1);
						}
					}
					else if(barabashka.dir_x == -1)
					{
						if(t)
						{
							barabashka.Set_Direction(0,1);
						}
						else
						{
							barabashka.Set_Direction(0,-1);
						}
					}
					break;
				case '5':
					t = rand()%2;
					if(barabashka.dir_y == -1)
					{
						if(t)
						{
							barabashka.Set_Direction(1,0);
						}
						else
						{
							barabashka.Set_Direction(-1,0);
						}
					}
					else if(barabashka.dir_x == -1)
					{
						if(t)
						{
							barabashka.Set_Direction(0,1);
						}
						else
						{
							barabashka.Set_Direction(-1,0);
						}
					}
					else if(barabashka.dir_x == 1)
					{
						if(t)
						{
							barabashka.Set_Direction(0,1);
						}
						else
						{
							barabashka.Set_Direction(1,0);
						}
					}
					break;
				case '6':
					t = rand()%2;
					if(barabashka.dir_y == 1)
					{
						if(t)
						{
							barabashka.Set_Direction(-1,0);
						}
						else
						{
							barabashka.Set_Direction(0,1);
						}
					}
					else if(barabashka.dir_y == -1)
					{
						if(t)
						{
							barabashka.Set_Direction(-1,0);
						}
						else
						{
							barabashka.Set_Direction(0,1);
						}
					}
					else if(barabashka.dir_x == 1)
					{
						if(t)
						{
							barabashka.Set_Direction(0,1);
						}
						else
						{
							barabashka.Set_Direction(0,-1);
						}
					}
					break;
				case '7':
					t = rand()%2;
					if(barabashka.dir_y == 1)
					{
						if(t)
						{
							barabashka.Set_Direction(1,0);
						}
						else
						{
							barabashka.Set_Direction(-1,0);
						}
					}
					else if(barabashka.dir_x == -1)
					{
						if(t)
						{
							barabashka.Set_Direction(0,-1);
						}
						else
						{
							barabashka.Set_Direction(-1,0);
						}
					}
					else if(barabashka.dir_x == 1)
					{
						if(t)
						{
							barabashka.Set_Direction(0,-1);
						}
						else
						{
							barabashka.Set_Direction(1,0);
						}
					}
					break;
				case '8':
					t = rand()%3;
					if(barabashka.dir_y == 1)
					{
						if(t == 0)
						{
							barabashka.Set_Direction(0,1);
						}
						else if(t == 1)
						{
							barabashka.Set_Direction(-1,0);
						}
						else
						{
							barabashka.Set_Direction(1,0);
						}
					}
					else if(barabashka.dir_y == -1)
					{
						if(t == 0)
						{
							barabashka.Set_Direction(0,-1);
						}
						else if(t == 1)
						{
							barabashka.Set_Direction(-1,0);
						}
						else
						{
							barabashka.Set_Direction(1,0);
						}
					}
					else if(barabashka.dir_x == 1)
					{
						if(t == 0)
						{
							barabashka.Set_Direction(1,0);
						}
						else if(t == 1)
						{
							barabashka.Set_Direction(0,1);
						}
						else
						{
							barabashka.Set_Direction(0,-1);
						}
					}
					else if(barabashka.dir_x == -1)
					{
						if(t == 0)
						{
							barabashka.Set_Direction(-1,0);
						}
						else if(t == 1)
						{
							barabashka.Set_Direction(0,1);
						}
						else
						{
							barabashka.Set_Direction(0,-1);
						}
					}
					break;
				}
			}
			
			if(stay_time > 20)
			{
				stay_time -= rand() % 5;
			}
			cur_stay_time = stay_time;

			switch(lvl[barabashka.y - 1][barabashka.x])
			{
			case 'P':
				lvl[barabashka.y - 1][barabashka.x] = 'p';
				items_kol--;
				break;
			case 'E':
				lvl[barabashka.y - 1][barabashka.x] = 'e';
				items_kol--;
				break;
			case 'B':
				lvl[barabashka.y - 1][barabashka.x] = 'b';
				items_kol--;
				break;
			case 'C':
				lvl[barabashka.y - 1][barabashka.x] = 'c';
				items_kol--;
				break;
			case 'W':
				lvl[barabashka.y - 1][barabashka.x] = 'w';
				items_kol--;
				break;
			}

			switch(lvl[barabashka.y + 1][barabashka.x])
			{
			case 'P':
				lvl[barabashka.y + 1][barabashka.x] = 'p';
				items_kol--;
				break;
			case 'E':
				lvl[barabashka.y + 1][barabashka.x] = 'e';
				items_kol--;
				break;
			case 'B':
				lvl[barabashka.y + 1][barabashka.x] = 'b';
				items_kol--;
				break;
			case 'C':
				lvl[barabashka.y + 1][barabashka.x] = 'c';
				items_kol--;
				break;
			case 'W':
				lvl[barabashka.y + 1][barabashka.x] = 'w';
				items_kol--;
				break;
			}

			switch(lvl[barabashka.y][barabashka.x + 1])
			{
			case 'P':
				lvl[barabashka.y][barabashka.x + 1] = 'p';
				items_kol--;
				break;
			case 'E':
				lvl[barabashka.y][barabashka.x + 1] = 'e';
				items_kol--;
				break;
			case 'B':
				lvl[barabashka.y][barabashka.x + 1] = 'b';
				items_kol--;
				break;
			case 'C':
				lvl[barabashka.y][barabashka.x + 1] = 'c';
				items_kol--;
				break;
			case 'W':
				lvl[barabashka.y][barabashka.x + 1] = 'w';
				items_kol--;
				break;
			}

			switch(lvl[barabashka.y][barabashka.x - 1])
			{
			case 'P':
				lvl[barabashka.y][barabashka.x - 1] = 'p';
				items_kol--;
				break;
			case 'E':
				lvl[barabashka.y][barabashka.x - 1] = 'e';
				items_kol--;
				break;
			case 'B':
				lvl[barabashka.y][barabashka.x - 1] = 'b';
				items_kol--;
				break;
			case 'C':
				lvl[barabashka.y][barabashka.x - 1] = 'c';
				items_kol--;
				break;
			case 'W':
				lvl[barabashka.y][barabashka.x - 1] = 'w';
				items_kol--;
				break;
			}

		}
		//***************************************************************************************

		draw_lvl(lvl_w, lvl_h, housewife, barabashka);
		game_m.Draw(surface);


		game_time_end = clock();
		SDL_itoa((game_time_end - game_time_start)/CLOCKS_PER_SEC, temp_str, 10);
		timer.Set_Text(temp_str);
		timer.Draw(surface);

		//SDL_Flip(surface);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(20);
		cur_stay_time-=20;

		if(items_kol <= 0)
		{
			play = false;
		}

	}

	//******************************************************************
	//очиска атласов
	background_atlas.Clear_Sprite();
	items_atlas.Clear_Sprite();
	//******************************************************************


	return save((game_time_end - game_time_start)/CLOCKS_PER_SEC);
}





int Game::ruls()
{
	Sprite background;
	background.Set_Sprite("ruls.bmp");
	background.Draw(surface);

	//SDL_Flip(surface);
	SDL_UpdateWindowSurface(window);

	while(SDL_WaitEvent(&event))
	{
		if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			int x;
			int y;

			SDL_GetMouseState(&x, &y);

			if(x > 348 && x < 547 && y > 615 && y < 664)
			{
				return 2;
			}
		}
		else if(event.type == SDL_QUIT)
		{
			return 0;
		}
	}
}

int Game::records()
{
	Sprite background;
	background.Set_Sprite("records.bmp");
	background.Draw(surface);


	Text text;
	text.Set_Font(font);
	text.Set_Color(181, 4, 12);

	int size = 0;
	char str[11];
	int temp = 0;

	ifstream file("save.txt");
	if(file.is_open())
	{
		file >> size;
		for(int i = 0; i < size; i++)
		{
			file >> str;
			text.Set_Text(str);
			text.Set_Position(270, 180 + 30*i);
			text.Draw(surface);

			file >> temp;
			SDL_itoa(temp, str, 10);
			text.Set_Text(str);
			text.Set_Position(570, 180 + 30*i);
			text.Draw(surface);
		}
	}
	file.close();

	//SDL_Flip(surface);
	SDL_UpdateWindowSurface(window);

	while(SDL_WaitEvent(&event))
	{
		if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			int x;
			int y;

			SDL_GetMouseState(&x, &y);

			if(x > 348 && x < 547 && y > 615 && y < 664)
			{
				return 2;
			}
		}
		else if(event.type == SDL_QUIT)
		{
			return 0;
		}
	}
}

/////////////////////////////////////

Game::Game()
{
	width = 896;
	height = 768;

	window = nullptr;
	surface = nullptr;
	font = nullptr;
	success = true;

	lvl = nullptr;

	window = SDL_CreateWindow("Barabashka", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window) 
	{
		cout << SDL_GetError() << endl;
		success = false;
		return;
	}

	surface = SDL_GetWindowSurface(window);

	font =  TTF_OpenFont("CharisSILR.ttf", 30);
	if(!font)
	{
		cout << TTF_GetError() << endl;
		success = false;
		return;
	}
}

Game::~Game()
{
	if(surface)
	{
		SDL_FreeSurface(surface);
	}

	if(font)
	{
		TTF_CloseFont(font);
	}
}

void Game::Start()
{
	if(success)
	{
		menu();
	}
}
//#include "Text.h"
//
//
//Text::Text(void)
//{
//	text[0] = '\0';
//
//	color.r = 0;
//	color.g = 0;
//	color.b = 0;
//
//	font = nullptr;
//}
//
//void Text::Set_Text(char* text)
//{
//	strcpy_s(this->text, text);
//}
//
//void Text::Set_Color(int r, int g, int b)
//{
//	color.r = r;
//	color.g = g;
//	color.b = b;
//}
//
//void Text::Set_Font(TTF_Font* font)
//{
//	this->font = font;
//}
//
//void Text::Draw(SDL_Surface* main_surface)
//{
//	SDL_Surface* temp;
//	temp = TTF_RenderText_Blended(font, text, color);
//	SDL_BlitSurface(temp, NULL, main_surface, &transform);
//	SDL_FreeSurface(temp);
//}
//
//void Text::Draw(SDL_Surface* main_surface, int x_offset, int y_offset)
//{
//	SDL_Rect offset_rect = transform;
//	offset_rect.x += x_offset;
//	offset_rect.y += y_offset;
//
//	SDL_Surface* temp;
//	temp = TTF_RenderText_Blended(font, text, color);
//	SDL_BlitSurface(temp, NULL, main_surface, &offset_rect);
//	SDL_FreeSurface(temp);
//
//}

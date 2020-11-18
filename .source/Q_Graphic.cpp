#include "Q_Graphic.h"


extern "C" int setCursorShow(lua_State * L)
{
	SDL_ShowCursor(lua_toboolean(L, 1) ? SDL_ENABLE : SDL_DISABLE);
	return 0;
}


extern "C" int loadImage(lua_State * L)
{
	const char* path = lua_tostring(L, 1);
	SDL_Surface* surface = IMG_Load(path);
	if (!surface)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		QGImage image;
		image.image = SDL_CreateTextureFromSurface(renderer, surface);
		image.width = surface->w;
		image.height = surface->h;
		vImage.push_back(image);
		lua_pushnumber(L, vImage.size() ? vImage.size() - 1 : 0);
	}
	SDL_FreeSurface(surface);
	return 1;
}


extern "C" int loadColorKeyImage(lua_State * L)
{
	const char* path = lua_tostring(L, 1);
	int R = lua_tonumber(L, 2);
	int G = lua_tonumber(L, 3);
	int B = lua_tonumber(L, 4);
	SDL_Surface* surface = IMG_Load(path);
	if (!surface)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		QGImage image;
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, R, G, B));
		image.image = SDL_CreateTextureFromSurface(renderer, surface);
		image.width = surface->w;
		image.height = surface->h;
		vImage.push_back(image);
		lua_pushnumber(L, vImage.size() ? vImage.size() - 1 : 0);
	}
	SDL_FreeSurface(surface);
	return 1;
}


extern "C" int unloadImage(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	if (index >= vImage.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		SDL_DestroyTexture(vImage[index].image);
		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int setImageAlpha(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	int alpha = lua_tonumber(L, 2);
	if (index >= vImage.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		SDL_SetTextureBlendMode(vImage[index].image, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(vImage[index].image, alpha);
		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int getImageSize(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	if (index >= vImage.size() || index < 0)
	{
		lua_pushnumber(L, -1);
		lua_pushnumber(L, -1);
	}
	else
	{
		lua_pushnumber(L, vImage[index].width);
		lua_pushnumber(L, vImage[index].height);
	}
	return 2;
}


extern "C" int showImage(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	if (index >= vImage.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		SDL_Rect rect = { lua_tonumber(L, 2) , lua_tonumber(L, 3) , lua_tonumber(L, 4) < 0 ? vImage[index].width : lua_tonumber(L, 4) , lua_tonumber(L, 5) < 0 ? vImage[index].height : lua_tonumber(L, 5) };
		SDL_RenderCopy(renderer, vImage[index].image, NULL, &rect);

		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int showRotateImage(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	if (index >= vImage.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		SDL_Rect rect = { lua_tonumber(L, 6) , lua_tonumber(L, 7) , lua_tonumber(L, 8) < 0 ? vImage[index].width : lua_tonumber(L, 8) , lua_tonumber(L, 9) < 0 ? vImage[index].height : lua_tonumber(L, 9) };
		SDL_Point point = { lua_tonumber(L, 3), lua_tonumber(L, 4) };
		SDL_RendererFlip flip;

		if (!strcmp(lua_tostring(L, 5), "HORIZONTAL"))
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		else if (!strcmp(lua_tostring(L, 5), "VERTICAL"))
		{
			flip = SDL_FLIP_VERTICAL;
		}
		else
		{
			flip = SDL_FLIP_NONE;
		}

		SDL_RenderCopyEx(renderer, vImage[index].image, NULL, &rect, lua_tonumber(L, 2), &point, flip);

		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int showReshapeImage(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	if (index >= vImage.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		SDL_Rect reshapeRect = { lua_tonumber(L, 2) , lua_tonumber(L, 3) , lua_tonumber(L, 4) < 0 ? vImage[index].width : lua_tonumber(L, 4) , lua_tonumber(L, 5) < 0 ? vImage[index].height : lua_tonumber(L, 5) };
		SDL_Rect showRect = { lua_tonumber(L, 6) , lua_tonumber(L, 7) , lua_tonumber(L, 8) < 0 ? vImage[index].width : lua_tonumber(L, 8) , lua_tonumber(L, 9) < 0 ? vImage[index].width : lua_tonumber(L, 9) };
		SDL_RenderCopy(renderer, vImage[index].image, &reshapeRect, &showRect);

		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int showRotateReshapeImage(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	if (index >= vImage.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		SDL_Rect reshapeRect = { lua_tonumber(L, 6) , lua_tonumber(L, 7) , lua_tonumber(L, 8) < 0 ? vImage[index].width : lua_tonumber(L, 8) , lua_tonumber(L, 9) < 0 ? vImage[index].height : lua_tonumber(L, 9) };
		SDL_Rect showRect = { lua_tonumber(L, 10) , lua_tonumber(L, 11) , lua_tonumber(L, 12) < 0 ? vImage[index].width : lua_tonumber(L, 12) , lua_tonumber(L, 13) < 0 ? vImage[index].width : lua_tonumber(L, 13) };
		SDL_Point point = { lua_tonumber(L, 3), lua_tonumber(L, 4) };
		SDL_RendererFlip flip;

		if (!strcmp(lua_tostring(L, 5), "HORIZONTAL"))
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		else if (!strcmp(lua_tostring(L, 5), "VERTICAL"))
		{
			flip = SDL_FLIP_VERTICAL;
		}
		else
		{
			flip = SDL_FLIP_NONE;
		}

		SDL_RenderCopyEx(renderer, vImage[index].image, &reshapeRect, &showRect, lua_tonumber(L, 2), &point, flip);

		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int setDrawColor(lua_State * L)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));

	return 0;
}


extern "C" int getDrawColor(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	lua_pushnumber(L, R);
	lua_pushnumber(L, G);
	lua_pushnumber(L, B);
	lua_pushnumber(L, A);

	return 4;
}


extern "C" int point(lua_State * L)
{
	SDL_RenderDrawPoint(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2));

	return 0;
}


extern "C" int line(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	aalineRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), R, G, B, A);

	return 0;
}


extern "C" int thickLine(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	thickLineRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5), R, G, B, A);

	return 0;
}


extern "C" int rectangle(lua_State * L)
{
	SDL_Rect rect = { lua_tonumber(L, 1) , lua_tonumber(L, 2) , lua_tonumber(L, 3) , lua_tonumber(L, 4) };
	SDL_RenderDrawRect(renderer, &rect);

	return 0;
}


extern "C" int fillRectangle(lua_State * L)
{
	SDL_Rect rect = { lua_tonumber(L, 1) , lua_tonumber(L, 2) , lua_tonumber(L, 3) , lua_tonumber(L, 4) };
	SDL_RenderFillRect(renderer, &rect);

	return 0;
}


extern "C" int roundRectangle(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	roundedRectangleRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 1) + lua_tonumber(L, 3), lua_tonumber(L, 2) + lua_tonumber(L, 4), lua_tonumber(L, 5), R, G, B, A);

	return 0;
}


extern "C" int fillRoundRectangle(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	roundedBoxRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 1) + lua_tonumber(L, 3), lua_tonumber(L, 2) + lua_tonumber(L, 4), lua_tonumber(L, 5), R, G, B, A);

	return 0;
}


extern "C" int circle(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	aacircleRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), R, G, B, A);

	return 0;
}


extern "C" int fillCircle(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	filledCircleRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), R, G, B, A);

	return 0;
}


extern "C" int ellipse(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	aaellipseRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), R, G, B, A);

	return 0;
}


extern "C" int fillEllipse(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	filledEllipseRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), R, G, B, A);

	return 0;
}

extern "C" int pie(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	pieRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5), R, G, B, A);

	return 0;
}

extern "C" int fillPie(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	filledPieRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5), R, G, B, A);

	return 0;
}

extern "C" int triangle(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	aatrigonRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5), lua_tonumber(L, 5), R, G, B, A);

	return 0;
}

extern "C" int fillTriangle(lua_State * L)
{
	Uint8 R, G, B, A;
	SDL_GetRenderDrawColor(renderer, &R, &G, &B, &A);
	filledTrigonRGBA(renderer, lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5), lua_tonumber(L, 5), R, G, B, A);

	return 0;
}


extern "C" int loadFont(lua_State * L)
{
	const char* path = lua_tostring(L, 1);
	int size = lua_tonumber(L, 2);
	TTF_Font* tf = TTF_OpenFont(path, size);
	if (!tf)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		vFont.push_back(tf);
		lua_pushnumber(L, vFont.size() ? vFont.size() - 1 : 0);
	}
	return 1;
}


extern "C" int unloadFont(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	if (index >= vFont.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		TTF_CloseFont(vFont[index]);
		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int setTextColor(lua_State * L)
{
	font_color.r = lua_tonumber(L, 1);
	font_color.g = lua_tonumber(L, 2);
	font_color.b = lua_tonumber(L, 3);
	font_color.a = lua_tonumber(L, 4);
	return 0;
}


extern "C" int drawText(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	const char* text = lua_tostring(L, 2);
	int x = lua_tonumber(L, 3);
	int y = lua_tonumber(L, 4);
	int width = lua_tonumber(L, 5);
	int height = lua_tonumber(L, 6);
	if (index >= vFont.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		SDL_Surface* surface = TTF_RenderUTF8_Solid(vFont[index], text, font_color);
		SDL_Rect rect = { x, y, width < 0 ? surface->w : width, height < 0 ? surface->h : height };
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, &rect);

		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int update(lua_State * L)
{
	SDL_RenderPresent(renderer);
	return 0;
}
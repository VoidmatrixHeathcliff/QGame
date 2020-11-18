#include "Q_Window.h"


extern "C" int showMessageBox(lua_State * L)
{
	SDL_MessageBoxFlags flag;
	if (!strcmp(lua_tostring(L, 1), "ERROR"))
	{
		flag = SDL_MESSAGEBOX_ERROR;
	}
	else if (!strcmp(lua_tostring(L, 1), "WARNING"))
	{
		flag = SDL_MESSAGEBOX_WARNING;
	}
	else
	{
		flag = SDL_MESSAGEBOX_INFORMATION;
	}
	SDL_ShowSimpleMessageBox(flag, lua_tostring(L, 2), lua_tostring(L, 3), window);
	return 0;
}


extern "C" int createWindow(lua_State * L)
{
	const char* title = lua_tostring(L, 1);
	int x = lua_tonumber(L, 2) < 0 ? SDL_WINDOWPOS_UNDEFINED : lua_tonumber(L, 2);
	int y = lua_tonumber(L, 3) < 0 ? SDL_WINDOWPOS_UNDEFINED : lua_tonumber(L, 3);
	int width = lua_tonumber(L, 4);
	int height = lua_tonumber(L, 5);
	string flags_str = lua_tostring(L, 6);
	int flags = SDL_WINDOW_SHOWN;
	if (!flags_str.empty())
	{
		for (char flag : flags_str)
		{
			switch (toupper(flag))
			{
			case 'F':
				flags |= SDL_WINDOW_FULLSCREEN;	// fullscreen window	
				break;
			case 'D':
				flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;	// fullscreen window at the current desktop resolution
				break;
			case 'B':
				flags |= SDL_WINDOW_BORDERLESS;	// no window decoration
				break;
			case 'R':
				flags |= SDL_WINDOW_RESIZABLE;	// window can be resized
				break;
			case 'M':
				flags |= SDL_WINDOW_MAXIMIZED;	// window is maximized
				break;
			case 'N':
				flags |= SDL_WINDOW_MINIMIZED;	// window is minimized
				break;
			default:
				break;
			}
		}
	}
	window = SDL_CreateWindow(title, x, y, width, height, flags);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);;
	return 0;
}


extern "C" int closeWindow(lua_State * L)
{
	SDL_DestroyWindow(window);
	window = NULL;
	return 0;
}


extern "C" int setWindowTitle(lua_State * L)
{
	SDL_SetWindowTitle(window, lua_tostring(L, 1));
	return 0;
}


extern "C" int getWindowTitle(lua_State * L)
{
	lua_pushstring(L, SDL_GetWindowTitle(window));
	return 1;
}


extern "C" int setWindowMode(lua_State * L)
{
	int flag = lua_tonumber(L, 1);
	switch (flag)
	{
	case 0:
		SDL_SetWindowFullscreen(window, 0);
		break;
	case 1:
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		break;
	case 2:
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		break;
	}
	return 0;
}


extern "C" int setWindowResizable(lua_State * L)
{
	SDL_SetWindowResizable(window, lua_toboolean(L, 1) ? SDL_TRUE : SDL_FALSE);
	return 0;
}


extern "C" int setWindowOpacity(lua_State * L)
{
	SDL_SetWindowOpacity(window, lua_tonumber(L, 1));
	return 0;
}


extern "C" int setWindowSize(lua_State * L)
{
	SDL_SetWindowSize(window, lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
}


extern "C" int getWindowSize(lua_State * L)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	return 2;
}


extern "C" int setWindowMaxSize(lua_State * L)
{
	SDL_SetWindowMaximumSize(window, lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
}


extern "C" int getWindowMaxSize(lua_State * L)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowMaximumSize(window, &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	return 2;
}


extern "C" int setWindowMinSize(lua_State * L)
{
	SDL_SetWindowMinimumSize(window, lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
}


extern "C" int getWindowMinSize(lua_State * L)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowMinimumSize(window, &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	return 2;
}


extern "C" int setWindowPosition(lua_State * L)
{
	SDL_SetWindowPosition(window, lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
}


extern "C" int getWindowPosition(lua_State * L)
{
	int x = 0;
	int y = 0;
	SDL_GetWindowSize(window, &x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}


extern "C" int clear(lua_State * L)
{
	SDL_RenderClear(renderer);

	return 0;
}


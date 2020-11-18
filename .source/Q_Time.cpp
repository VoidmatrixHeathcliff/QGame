#include "Q_Time.h"

#include <iostream>
using namespace std;

Uint32 timerCallback(Uint32 interval, void* param)
{
	TimerCallbackParam* pTimerCallbackParam = vParam[(int)param];
	lua_getglobal(pTimerCallbackParam->L, pTimerCallbackParam->name.c_str());
	lua_pcall(pTimerCallbackParam->L, 0, 0, 0);
	return interval;
}

extern "C" int sleep(lua_State * L)
{
	int delay = lua_tonumber(L, 1);
	SDL_Delay(delay);

	return 0;
}


extern "C" int getInitTime(lua_State * L)
{
	lua_pushnumber(L, SDL_GetTicks());

	return 1;
}


extern "C" int getAccurateCount(lua_State * L)
{
	lua_pushnumber(L, SDL_GetPerformanceCounter());

	return 1;
}


extern "C" int getCounterFrequency(lua_State * L)
{
	lua_pushnumber(L, SDL_GetPerformanceFrequency());

	return 1;
}

extern "C" int addTimer(lua_State* L)
{
	TimerCallbackParam* pTimerCallbackParam = new TimerCallbackParam;
	pTimerCallbackParam->name = lua_tostring(L, 2);
	pTimerCallbackParam->L = L;
	SDL_TimerID id = SDL_AddTimer(lua_tonumber(L, 1), timerCallback, (void*)vParam.size());
	if (id)
	{
		vParam.push_back(pTimerCallbackParam);
		lua_pushnumber(L, id);
	}
	else
	{
		lua_pushnumber(L, -1);
	}

	return 1;
}


extern "C" int removeTimer(lua_State * L)
{
	int id = lua_tonumber(L, 1);
	if (id <= 0 || id > vParam.size())
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		SDL_RemoveTimer(id);
		cout << "Remove_ID: " << id << endl;
		/*delete(vParam[id - 1]);*/
		lua_pushnumber(L, 0);
	}

	return 1;
}
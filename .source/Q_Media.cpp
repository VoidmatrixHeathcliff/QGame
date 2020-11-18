#include "Q_Media.h"


extern "C" int loadMusic(lua_State * L)
{
	const char* path = lua_tostring(L, 1);
	Mix_Music* mm = Mix_LoadMUS(path);
	if (!mm)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		vMusic.push_back(mm);
		lua_pushnumber(L, vMusic.size() ? vMusic.size() - 1 : 0);
	}
	return 1;
}


extern "C" int unloadMusic(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	if (index >= vMusic.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		Mix_FreeMusic(vMusic[index]);
		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int playMusic(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	int loops = lua_tonumber(L, 2);
	if (index >= vMusic.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		Mix_PlayMusic(vMusic[index], loops);
		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int fadeInMusic(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	int loops = lua_tonumber(L, 2);
	int delay = lua_tonumber(L, 3);
	if (index >= vMusic.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		Mix_FadeInMusic(vMusic[index], loops, delay);
		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int fadeOutMusic(lua_State * L)
{
	int delay = lua_tonumber(L, 1);
	Mix_FadeOutMusic(delay);
	return 0;
}


extern "C" int setMusicVolume(lua_State * L)
{
	int value = lua_tonumber(L, 1);
	Mix_VolumeMusic(value);
	return 0;
}


extern "C" int getMusicVolume(lua_State * L)
{
	int value = Mix_VolumeMusic(-1);
	lua_pushnumber(L, value);
	return 1;
}


extern "C" int pauseMusic(lua_State * L)
{
	Mix_PauseMusic();
	return 0;
}


extern "C" int resumeMusic(lua_State * L)
{
	Mix_ResumeMusic();
	return 0;
}


extern "C" int rewindMusic(lua_State * L)
{
	Mix_RewindMusic();
	return 0;
}


extern "C" int getMusicType(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	Mix_MusicType type;
	if (index < 0)
	{
		type = Mix_GetMusicType(NULL);
	}
	else
	{
		if (index >= vMusic.size())
		{
			lua_pushstring(L, "ERROR");
		}
		else
		{
			type = Mix_GetMusicType(vMusic[index]);
		}
	}
	switch (type)
	{
	case MUS_WAV:
		lua_pushstring(L, "WAV");
		break;
	case MUS_MP3:
		lua_pushstring(L, "MP3");
		break;
	case MUS_OGG:
		lua_pushstring(L, "OGG");
		break;
	case MUS_CMD:
		lua_pushstring(L, "CMD");
		break;
	case MUS_MOD:
		lua_pushstring(L, "MOD");
		break;
	case MUS_MID:
		lua_pushstring(L, "MID");
		break;
	default:
		lua_pushstring(L, "UNKONWN");
		break;
	}
	return 1;
}


extern "C" int loadSound(lua_State * L)
{
	const char* path = lua_tostring(L, 1);
	Mix_Chunk* mc = Mix_LoadWAV(path);
	if (!mc)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		vSound.push_back(mc);
		lua_pushnumber(L, vSound.size() ? vSound.size() - 1 : 0);
	}
	return 1;
}


extern "C" int unloadSound(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	if (index >= vSound.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		Mix_FreeChunk(vSound[index]);
		lua_pushnumber(L, 0);
	}
	return 1;
}


extern "C" int playSound(lua_State * L)
{
	int index = lua_tonumber(L, 1);
	int loops = lua_tonumber(L, 2);

	if (index >= vSound.size() || index < 0)
	{
		lua_pushnumber(L, -1);
	}
	else
	{
		if (loops > 0)
		{
			Mix_PlayChannel(-1, vSound[index], loops - 1);
		}
		else
		{
			Mix_PlayChannel(-1, vSound[index], loops);
		}
		lua_pushnumber(L, 0);
	}
	return 1;
}
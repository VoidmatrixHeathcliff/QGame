#ifndef _Q_BASIC_H_
#define _Q_BASIC_H_

#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

// 初始化QGame库
// 无参数
// 无返回值
extern "C" int init(lua_State * L);

// 退出QGame库
// 无参数
// 无返回值
extern "C" int quit(lua_State * L);

// 暂停程序
// 无参数
// 无返回值
extern "C" int pause(lua_State * L);


#endif // !_Q_BASIC_H_


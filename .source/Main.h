#ifndef _MAIN_H_
#define _MAIN_H_

#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Q_Basic.h"
#include "Q_Window.h"
#include "Q_Graphic.h"
#include "Q_Media.h"
#include "Q_Interactivity.h"
#include "Q_Time.h"
#include "Q_Others.h"

#include <vector>
#include <string>
using namespace std;

SDL_Event event;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Color font_color = { 255, 255, 255, 255 };
TimerCallbackParam* pTimerCallbackParam = NULL;

vector<Mix_Music*>			vMusic;		// 已加载的音乐文件
vector<Mix_Chunk*>			vSound;		// 已加载的音效文件
vector<QGImage>				vImage;		// 已加载的图像文件
vector<TTF_Font*>			vFont;		// 已加载的字体文件
vector<TimerCallbackParam*>	vParam;		// 定时器回调函数参数结构体

#endif // !_MAIN_H_


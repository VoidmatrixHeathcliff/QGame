#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <vector>
#include <string>
using namespace std;

struct QGImage
{
	SDL_Texture* image = NULL;
	int width = 0;
	int height = 0;
};	// 图像数据结构体

SDL_Event event;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Color font_color = { 255, 255, 255, 255 };

vector<Mix_Music*> vMusic;	// 已加载的音乐文件
vector<Mix_Chunk*> vSound;	// 已加载的音效文件
vector<QGImage> vImage;		// 已加载的图像文件
vector<TTF_Font*> vFont;	// 已加载的字体文件

// 初始化QGame库
// 无参数
// 无返回值
extern "C" int init(lua_State * L)
{
	TTF_Init();
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return 0;
}

// 退出QGame库
// 无参数
// 无返回值
extern "C" int quit(lua_State * L)
{
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}

// 获取程序运行的目录
// 无参数
// 1返回值：程序运行目录
extern "C" int getBasePath(lua_State * L)
{
	lua_pushstring(L, SDL_GetBasePath());
	return 1;
}

// 设置剪切板文本
// 1参数：剪切板文本
// 无返回值
extern "C" int setClipboardText(lua_State * L)
{
	const char* text = lua_tostring(L, 1);
	SDL_SetClipboardText(text);
	return 1;
}

// 获取剪切板文本
// 无参数
// 1返回值：剪切板文本
extern "C" int getClipboardText(lua_State * L)
{
	lua_pushstring(L, SDL_GetClipboardText());
	return 1;
}

// 获取平台类型
// 无参数
// 1返回值：平台类型（字符串）
extern "C" int getPlatform(lua_State * L)
{
	lua_pushstring(L, SDL_GetPlatform());
	return 1;
}

// 获取系统总内存大小
// 无参数
// 1返回值：系统内存（MB）
extern "C" int getSystemRAM(lua_State * L)
{
	lua_pushnumber(L, SDL_GetSystemRAM());
	return 1;
}

// 显示模态的提示信息窗口
// 3参数：窗口类型（错误、警告、提示），标题，提示信息内容
// 无返回值
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

// 创建窗口，并将此窗口作为图形绘制等操作的上下文
// 5参数：窗口标题，窗口x、y坐标（负值为默认位置），窗口宽度和高度，窗口属性标志（对应关系见下方代码注释）
// 无返回值
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

// 设置窗口标题
// 1参数：标题内容
// 无返回值
extern "C" int setWindowTitle(lua_State * L)
{
	SDL_SetWindowTitle(window, lua_tostring(L, 1));
	return 0;
}

// 获取窗口标题
// 无参数
// 1返回值：标题内容
extern "C" int getWindowTitle(lua_State * L)
{
	lua_pushstring(L, SDL_GetWindowTitle(window));
	return 1;
}

// 设置窗口模式
// 1参数：全屏标志（0，窗口模式；1，视频模式改变的真全屏；2，使用当前屏幕分辨率的假全屏）
// 无返回值
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

// 设置窗口是否大小可变
// 1参数：是否大小可变
// 无返回值
extern "C" int setWindowResizable(lua_State * L)
{
	SDL_SetWindowResizable(window, lua_toboolean(L, 1) ? SDL_TRUE : SDL_FALSE);
	return 0;
}

// 设置窗口透明度
// 1参数：透明度大小（0-1）
// 无返回值
extern "C" int setWindowOpacity(lua_State * L)
{
	SDL_SetWindowOpacity(window, lua_tonumber(L, 1));
	return 0;
}

// 设置窗口大小
// 2参数：窗口的宽和高
// 无返回值
extern "C" int setWindowSize(lua_State * L)
{
	SDL_SetWindowSize(window, lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
}

// 获取窗口大小
// 无参数
// 2返回值，窗口的宽和高
extern "C" int getWindowSize(lua_State * L)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	return 2;
}

// 设置窗口最大尺寸的大小
// 2参数：窗口宽度的最大值和高度的最大值
// 无返回值
extern "C" int setWindowMaxSize(lua_State * L)
{
	SDL_SetWindowMaximumSize(window, lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
}

// 获取窗口最大尺寸的大小
// 无参数
// 2返回值，窗口度的最大值和高度的最大值
extern "C" int getWindowMaxSize(lua_State * L)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowMaximumSize(window, &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	return 2;
}

// 设置窗口最小尺寸的大小
// 2参数：窗口宽度的最小值和高度的最小值
// 无返回值
extern "C" int setWindowMinSize(lua_State * L)
{
	SDL_SetWindowMinimumSize(window, lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
}

// 获取窗口最小尺寸的大小
// 无参数
// 2返回值，窗口度的最小值和高度的最小值
extern "C" int getWindowMinSize(lua_State * L)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowMinimumSize(window, &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	return 2;
}

// 设置窗口坐标
// 2参数：窗口位置的x和y坐标
// 无返回值
extern "C" int setWindowPosition(lua_State * L)
{
	SDL_SetWindowPosition(window, lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
}

// 获取窗口坐标
// 无参数
// 2返回值，窗口位置的x和y坐标
extern "C" int getWindowPosition(lua_State * L)
{
	int x = 0;
	int y = 0;
	SDL_GetWindowSize(window, &x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

// 使用当前绘图颜色清空窗口内容
// 无参数
// 无返回值
extern "C" int clear(lua_State * L)
{
	SDL_RenderClear(renderer);
 
	return 0;
}

// 设置鼠标是否显示
// 1参数：是否显示
// 无返回值
extern "C" int setCursorShow(lua_State * L)
{
	SDL_ShowCursor(lua_toboolean(L, 1) ? SDL_ENABLE : SDL_DISABLE);
	return 0;
}

// 获取鼠标位置
// 无参数
// 2返回值：位置的x和y坐标
extern "C" int getCursorPosition(lua_State * L)
{
	lua_pushnumber(L, event.motion.x);
	lua_pushnumber(L, event.motion.y);
	return 2;
}

// 获取鼠标滚轮滚动距离
// 无参数
// 1返回值：滚轮滚动距离
extern "C" int getScrollValue(lua_State * L)
{
	lua_pushnumber(L, abs(event.wheel.y) > 0 ? abs(event.wheel.y) : abs(event.wheel.x));
	return 1;
}

// 加载图像文件
// 1参数：图像文件路径
// 1返回值：-1，加载文件失败；其他，已加载的图像文件在图像库中的标志
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

// 加载使用ColorKey表示透明区域的图像文件
// 4参数：图像文件路径，ColorKey的R、G、B分量
// 1返回值：-1，加载文件失败；其他，已加载的图像文件在图像库中的标志
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

// 释放已加载的图像
// 1参数：已加载的图像文件在图像库中的标志
// 1返回值：-1，释放图像失败；0，释放图像成功
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

// 设置已加载图像的透明度
// 2参数：已加载的图像文件在图像库中的标志，透明度数值（0-255）
// 1返回值：-1，设置图像透明度失败；0，设置图像透明度成功
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

// 获取已加载图像尺寸
// 1参数：已加载的图像文件在图像库中的标志
// 2返回值：-1，-1，获取图像尺寸失败；成功则返回图像的长和宽
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

// 显示已加载的图像
// 5参数：已加载的图像文件在图像库中的标志，显示位置x，显示位置y，显示宽度，显示高度（-1为默认尺寸）
// 1返回值：-1，显示图像失败；0，显示图像成功
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

// 显示旋转后的已加载图像
// 9参数：已加载的图像文件在图像库中的标志，顺时针旋转角度，旋转中心x坐标，旋转中心y坐标，翻转模式，显示位置x，显示位置y，显示宽度（-1为默认尺寸），显示高度（-1为默认尺寸）
// 1返回值：-1，显示图像失败；0，显示图像成功
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

// 显示裁剪后的已加载图像
// 9参数：已加载的图像文件在图像库中的标志，裁剪区域x，裁剪区域y，裁剪区域宽度（-1为默认尺寸），裁剪区域高度（-1为默认尺寸），显示位置x，显示位置y，显示宽度（-1为默认尺寸），显示高度（-1为默认尺寸）
// 1返回值：-1，显示图像失败；0，显示图像成功
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

// 显示旋转且裁剪后的已加载图像
// 13参数：已加载的图像文件在图像库中的标志，旋转角度，旋转中心x坐标，旋转中心y坐标，旋转模式，裁剪区域x，裁剪区域y，裁剪区域宽度（-1为默认尺寸），裁剪区域高度（-1为默认尺寸），显示位置x，显示位置y，显示宽度（-1为默认尺寸），显示高度（-1为默认尺寸）
// 1返回值：-1，显示图像失败；0，显示图像成功
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

// 设置窗口绘图颜色
// 4参数：颜色的R、G、B、A分量（取值范围均为0-255）
// 无返回值
extern "C" int setDrawColor(lua_State * L)
{
	int R = lua_tonumber(L, 1);
	int G = lua_tonumber(L, 2);
	int B = lua_tonumber(L, 3);
	int A = lua_tonumber(L, 4);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, R, G, B, A);
 
	return 0;
}

// 在指定位置绘制点
// 2参数：点所在的x和y坐标
// 无返回值
extern "C" int point(lua_State * L)
{
	int x = lua_tonumber(L, 1);
	int y = lua_tonumber(L, 2);
	SDL_RenderDrawPoint(renderer, x, y);
 
	return 0;
}

// 在指定位置绘制直线
// 4参数：起点x、y坐标，终点x、y坐标
// 无返回值
extern "C" int line(lua_State * L)
{
	int x1 = lua_tonumber(L, 1);
	int y1 = lua_tonumber(L, 2);
	int x2 = lua_tonumber(L, 3);
	int y2 = lua_tonumber(L, 4);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
 
	return 0;
}

// 在指定位置绘制无填充矩形
// 4参数：矩形左上角x、y坐标，矩形宽和高	// 1参数：-1未填充整个窗口
// 无返回值
extern "C" int rectangle(lua_State * L)
{
	SDL_Rect rect = { lua_tonumber(L, 1) , lua_tonumber(L, 2) , lua_tonumber(L, 3) , lua_tonumber(L, 4) };
	SDL_RenderDrawRect(renderer, &rect);
 
	return 0;
}

// 在指定位置绘制填充矩形
// 4参数：矩形左上角x、y坐标，矩形宽和高
// 无返回值
extern "C" int fillRectangle(lua_State * L)
{
	SDL_Rect rect = { lua_tonumber(L, 1) , lua_tonumber(L, 2) , lua_tonumber(L, 3) , lua_tonumber(L, 4) };
	SDL_RenderFillRect(renderer, &rect);
 
	return 0;
}

// 将渲染缓冲区的内容刷新到屏幕上
// 无参数
// 无返回值
extern "C" int update(lua_State * L)
{
	SDL_RenderPresent(renderer);
	return 0;
}

// 加载音乐文件
// 1参数：音乐文件路径
// 1返回值：-1，加载文件失败；其他，已加载的音乐文件在音乐库中的标志
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

// 释放已加载的音乐
// 1参数：已加载的音乐文件在音乐库中的标志
// 1返回值：-1，释放音乐失败；0，释放音乐成功
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

// 播放已加载的音乐
// 2参数：已加载的音乐文件在音乐库中的标志、音乐播放的次数（-1为循环播放）
// 1返回值：-1，播放音乐失败；0，播放音乐成功
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

// 播放淡入音乐
// 3参数：已加载的音乐文件在音乐库中的标志、音乐播放的次数、淡入音效持续时间（ms）
// 1参数：-1，播放音乐失败；0，播放音乐成功
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

// 淡出并停止当前正在播放的音乐
// 1参数：淡出音效持续时间（ms）
// 无返回值
extern "C" int fadeOutMusic(lua_State * L)
{
	int delay = lua_tonumber(L, 1);
	Mix_FadeOutMusic(delay);
	return 0;
}

// 设置音乐播放的音量
// 1参数：音量大小（0-128）
// 无返回值
extern "C" int setMusicVolume(lua_State * L)
{
	int value = lua_tonumber(L, 1);
	Mix_VolumeMusic(value);
	return 0;
}

// 获取当前音乐音量
// 无参数
// 1返回值：当前音乐音量大小
extern "C" int getMusicVolume(lua_State * L)
{
	int value = Mix_VolumeMusic(-1);
	lua_pushnumber(L, value);
	return 1;
}

// 暂停当前正在播放的音乐
// 无参数
// 无返回值
extern "C" int pauseMusic(lua_State * L)
{
	Mix_PauseMusic();
	return 0;
}

// 恢复当前暂停状态的音乐
// 无参数
// 无返回值
extern "C" int resumeMusic(lua_State * L)
{
	Mix_ResumeMusic();
	return 0;
}

// 重播当前正在播放的音乐
// 无参数
// 无返回值
extern "C" int rewindMusic(lua_State * L)
{
	Mix_RewindMusic();
	return 0;
}

// 获取指定音乐的类型
// 1参数：已加载的音乐文件在音乐库中的标志（-1表示正在播放的音乐）
// 1返回值：成功则返回指定音乐的类型（字符串），未知则返回"UNKONWN"，失败则返回"ERROR"
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

// 加载音效文件
// 1参数：音效文件路径
// 1返回值：-1，加载音效文件失败；其他，已加载的音效文件在音效库中的标志
// 备注：音效文件支持以下格式：WAVE, AIFF, RIFF, OGG, VOC
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

// 释放已加载的音效
// 1参数：已加载的音效文件在音乐库中的标志
// 1返回值：-1，释放音效失败；0，释放音效成功
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

// 播放已加载的音效
// 2参数：已加载的音效文件在音效库中的标志、音效播放的次数（-1为循环播放）
// 1返回值：-1，播放音乐失败；0，播放音乐成功
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

// 加载字体文件
// 2参数：字体文件路径、字体大小
// 1返回值：-1，加载文件失败；其他，已加载的字体文件在字体库中的标志
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

// 释放已加载的字体
// 1参数：已加载的字体文件在字体库中的标志
// 1返回值：-1，释放字体失败；0，释放字体成功
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

// 设置字体绘制颜色
// 4参数：字体颜色的R、G、B、A分量（0-255）
// 无返回值
extern "C" int setTextColor(lua_State * L)
{
	font_color.r = lua_tonumber(L, 1);
	font_color.g = lua_tonumber(L, 2);
	font_color.b = lua_tonumber(L, 3);
	font_color.a = lua_tonumber(L, 4);
	return 0;
}

// 在指定位置绘制文字
// 6参数：已加载的字体文件在字体库中的标志，文本内容，绘制位置x、y坐标，绘制宽度和高度（-1为默认尺寸）
// 1返回值：-1，绘制字体失败；0，绘制字体成功
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


// 获取并更新事件
// 无参数
// 1返回值：-1，当前事件队列无待解决事件；0，获取到新事件
extern "C" int updateEvent(lua_State * L)
{
	if (SDL_PollEvent(&event))
	{
		lua_pushnumber(L, 0);
	}
	else
	{
		lua_pushnumber(L, -1);
	}
	return 1;
}

// 获取当前事件类型
// 无参数
// 1返回值：事件类型（字符串）
// 注意：由于部分字符按键事件对应的输入在大多数键盘上只能通过组合键完成，故这些字符的按键事件在大多数键盘上可能无法通过物理按键激活
extern "C" int getEventType(lua_State * L)
{
	string prefix = "";
	string suffix = "";
	string keyResult = "";
	switch (event.type)
	{
	case SDL_QUIT:
		lua_pushstring(L, "QUIT");
		break;
	case SDL_MOUSEMOTION:
		lua_pushstring(L, "MOUSEMOTION");
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			lua_pushstring(L, "MOUSEBUTTON_D_L");
			break;
		case SDL_BUTTON_RIGHT:
			lua_pushstring(L, "MOUSEBUTTON_D_R");
			break;
		case SDL_BUTTON_MIDDLE:
			lua_pushstring(L, "MOUSEBUTTON_D_M");
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			lua_pushstring(L, "MOUSEBUTTON_U_L");
			break;
		case SDL_BUTTON_RIGHT:
			lua_pushstring(L, "MOUSEBUTTON_U_R");
			break;
		case SDL_BUTTON_MIDDLE:
			lua_pushstring(L, "MOUSEBUTTON_U_M");
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEWHEEL:
		if (event.wheel.y > 0)
		{
			lua_pushstring(L, "MOUSESCROLL_U");
		}
		else if (event.wheel.y < 0)
		{
			lua_pushstring(L, "MOUSESCROLL_D");
		}
		else if (event.wheel.x > 0)
		{
			lua_pushstring(L, "MOUSESCROLL_R");
		}
		else if (event.wheel.x < 0)
		{
			lua_pushstring(L, "MOUSESCROLL_L");
		}
		break;
	case SDL_WINDOWEVENT:
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			lua_pushstring(L, "WINDOWSHOW");
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			lua_pushstring(L, "WINDOWHIDE");
			break;
		case SDL_WINDOWEVENT_MOVED:
			lua_pushstring(L, "WINDOWMOVE");
			break;
		case SDL_WINDOWEVENT_RESIZED:
			lua_pushstring(L, "WINDOWRESIZE");
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			lua_pushstring(L, "WINDOWMINSIZE");
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			lua_pushstring(L, "WINDOWMAXSIZE");
			break;
		case SDL_WINDOWEVENT_ENTER:
			lua_pushstring(L, "WINDOWENTER");
			break;
		case SDL_WINDOWEVENT_LEAVE:
			lua_pushstring(L, "WINDOWLEAVE");
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			lua_pushstring(L, "WINDOWFOCUS");
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			lua_pushstring(L, "WINDOWLOST");
			break;
		case SDL_WINDOWEVENT_CLOSE:
			lua_pushstring(L, "WINDOWCLOSE");
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		prefix = event.type == SDL_KEYUP ? "KEYUP_" : "KEYDOWN_";
		switch (event.key.keysym.sym)
		{
		case SDLK_0:
		case SDLK_KP_0:
			keyResult = prefix + "0";
			break;
		case SDLK_KP_00:
			keyResult = prefix + "00";
			break;
		case SDLK_KP_000:
			keyResult = prefix + "000";
			break;
		case SDLK_1:
		case SDLK_KP_1:
			keyResult = prefix + "1";
			break;
		case SDLK_2:
		case SDLK_KP_2:
			keyResult = prefix + "2";
			break;
		case SDLK_3:
		case SDLK_KP_3:
			keyResult = prefix + "3";
			break;
		case SDLK_4:
		case SDLK_KP_4:
			keyResult = prefix + "4";
			break;
		case SDLK_5:
		case SDLK_KP_5:
			keyResult = prefix + "5";
			break;
		case SDLK_6:
		case SDLK_KP_6:
			keyResult = prefix + "6";
			break;
		case SDLK_7:
		case SDLK_KP_7:
			keyResult = prefix + "7";
			break;
		case SDLK_8:
		case SDLK_KP_8:
			keyResult = prefix + "8";
			break;
		case SDLK_9:
		case SDLK_KP_9:
			keyResult = prefix + "9";
			break;
		case SDLK_F1:
			keyResult = prefix + "F1";
			break;
		case SDLK_F2:
			keyResult = prefix + "F2";
			break;
		case SDLK_F3:
			keyResult = prefix + "F3";
			break;
		case SDLK_F4:
			keyResult = prefix + "F4";
			break;
		case SDLK_F5:
			keyResult = prefix + "F5";
			break;
		case SDLK_F6:
			keyResult = prefix + "F6";
			break;
		case SDLK_F7:
			keyResult = prefix + "F7";
			break;
		case SDLK_F8:
			keyResult = prefix + "F8";
			break;
		case SDLK_F9:
			keyResult = prefix + "F9";
			break;
		case SDLK_F10:
			keyResult = prefix + "F10";
			break;
		case SDLK_F11:
			keyResult = prefix + "F11";
			break;
		case SDLK_F12:
			keyResult = prefix + "F12";
			break;
		case SDLK_F13:
			keyResult = prefix + "F13";
			break;
		case SDLK_F14:
			keyResult = prefix + "F14";
			break;
		case SDLK_F15:
			keyResult = prefix + "F15";
			break;
		case SDLK_F16:
			keyResult = prefix + "F16";
			break;
		case SDLK_F17:
			keyResult = prefix + "F17";
			break;
		case SDLK_F18:
			keyResult = prefix + "F18";
			break;
		case SDLK_F19:
			keyResult = prefix + "F19";
			break;
		case SDLK_F20:
			keyResult = prefix + "F20";
			break;
		case SDLK_F21:
			keyResult = prefix + "F21";
			break;
		case SDLK_F22:
			keyResult = prefix + "F22";
			break;
		case SDLK_F23:
			keyResult = prefix + "F23";
			break;
		case SDLK_F24:
			keyResult = prefix + "F24";
			break;
		case SDLK_a:
		case SDLK_KP_A:
			keyResult = prefix + "A";
			break;
		case SDLK_b:
		case SDLK_KP_B:
			keyResult = prefix + "B";
			break;
		case SDLK_c:
		case SDLK_KP_C:
			keyResult = prefix + "C";
			break;
		case SDLK_d:
		case SDLK_KP_D:
			keyResult = prefix + "D";
			break;
		case SDLK_e:
		case SDLK_KP_E:
			keyResult = prefix + "E";
			break;
		case SDLK_f:
		case SDLK_KP_F:
			keyResult = prefix + "F";
			break;
		case SDLK_g:
			keyResult = prefix + "G";
			break;
		case SDLK_h:
			keyResult = prefix + "H";
			break;
		case SDLK_i:
			keyResult = prefix + "I";
			break;
		case SDLK_j:
			keyResult = prefix + "J";
			break;
		case SDLK_k:
			keyResult = prefix + "K";
			break;
		case SDLK_l:
			keyResult = prefix + "L";
			break;
		case SDLK_m:
			keyResult = prefix + "M";
			break;
		case SDLK_n:
			keyResult = prefix + "N";
			break;
		case SDLK_o:
			keyResult = prefix + "O";
			break;
		case SDLK_p:
			keyResult = prefix + "P";
			break;
		case SDLK_q:
			keyResult = prefix + "Q";
			break;
		case SDLK_r:
			keyResult = prefix + "R";
			break;
		case SDLK_s:
			keyResult = prefix + "S";
			break;
		case SDLK_t:
			keyResult = prefix + "T";
			break;
		case SDLK_u:
			keyResult = prefix + "U";
			break;
		case SDLK_v:
			keyResult = prefix + "V";
			break;
		case SDLK_w:
			keyResult = prefix + "W";
			break;
		case SDLK_x:
			keyResult = prefix + "X";
			break;
		case SDLK_y:
			keyResult = prefix + "Y";
			break;
		case SDLK_z:
			keyResult = prefix + "Z";
			break;
		case SDLK_ESCAPE:
			keyResult = prefix + "ESC";
			break;
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			keyResult = prefix + "ENTER";
			break;
		case SDLK_BACKSPACE:
		case SDLK_KP_BACKSPACE:
			keyResult = prefix + "BACKSPACE";
			break;
		case SDLK_UP:
			keyResult = prefix + "UP";
			break;
		case SDLK_DOWN:
			keyResult = prefix + "DOWN";
			break;
		case SDLK_LEFT:
			keyResult = prefix + "LEFT";
			break;
		case SDLK_RIGHT:
			keyResult = prefix + "RIGHT";
			break;
		case SDLK_INSERT:
			keyResult = prefix + "INSERT";
			break;
		case SDLK_DELETE:
			keyResult = prefix + "DELETE";
			break;
		case SDLK_HOME:
			keyResult = prefix + "HOME";
			break;
		case SDLK_END:
			keyResult = prefix + "END";
			break;
		case SDLK_PAGEUP:
			keyResult = prefix + "PAGEUP";
			break;
		case SDLK_PAGEDOWN:
			keyResult = prefix + "PAGEDOWN";
			break;
		case SDLK_LCTRL:
			keyResult = prefix + "LCTRL";
			break;
		case SDLK_LGUI:
			keyResult = prefix + "LGUI";
			break;
		case SDLK_LALT:
			keyResult = prefix + "LALT";
			break;
		case SDLK_LSHIFT:
			keyResult = prefix + "LSHIFT";
			break;
		case SDLK_RCTRL:
			keyResult = prefix + "RCTRL";
			break;
		case SDLK_RGUI:
			keyResult = prefix + "RGUI";
			break;
		case SDLK_RALT:
			keyResult = prefix + "RALT";
			break;
		case SDLK_RSHIFT:
			keyResult = prefix + "RSHIFT";
			break;
		case SDLK_SPACE:
			keyResult = prefix + "SPACE";
			break;
		case SDLK_TAB:
		case SDLK_KP_TAB:
			keyResult = prefix + "TAB";
			break;
		case SDLK_CAPSLOCK:
			keyResult = prefix + "CAPSLOCK";
			break;
		case SDLK_NUMLOCKCLEAR:
			keyResult = prefix + "NUMLOCK";
			break;
		case SDLK_PRINTSCREEN:
			keyResult = prefix + "PRINTSCREEN";
			break;
		case SDLK_SCROLLLOCK:
			keyResult = prefix + "SCROLLLOCK";
			break;
		case SDLK_PAUSE:
			keyResult = prefix + "PAUSE";
			break;
		case SDLK_AUDIOMUTE:
			keyResult = prefix + "AUDIOMUTE";
			break;
		case SDLK_AUDIOPREV:
			keyResult = prefix + "AUDIOPREV";
			break;
		case SDLK_AUDIONEXT:
			keyResult = prefix + "AUDIONEXT";
			break;
		case SDLK_AUDIOPLAY:
			keyResult = prefix + "AUDIOPLAY";
			break;
		case SDLK_AUDIOSTOP:
			keyResult = prefix + "AUDIOSTOP";
			break;
		case SDLK_VOLUMEUP:
			keyResult = prefix + "VOLUMEUP";
			break;
		case SDLK_VOLUMEDOWN:
			keyResult = prefix + "VOLUMEDOWN";
			break;
		case SDLK_BRIGHTNESSUP:
			keyResult = prefix + "BRIGHTNESSUP";
			break;
		case SDLK_BRIGHTNESSDOWN:
			keyResult = prefix + "BRIGHTNESSDOWN";
			break;
		case SDLK_BACKQUOTE:
			keyResult = prefix + "BACKQUOTE";
			break;
		case SDLK_EXCLAIM:
		case SDLK_KP_EXCLAM:
			keyResult = prefix + "EXCLAM";
			break;
		case SDLK_AT:
		case SDLK_KP_AT:
			keyResult = prefix + "AT";
			break;
		case SDLK_HASH:
		case SDLK_KP_HASH:
			keyResult = prefix + "HASH";
			break;
		case SDLK_DOLLAR:
			keyResult = prefix + "DOOLAR";
			break;
		case SDLK_CARET:
		case SDLK_KP_POWER:
			keyResult = prefix + "CARET";
			break;
		case SDLK_AMPERSAND:
		case SDLK_KP_AMPERSAND:
			keyResult = prefix + "AMPERSAND";
			break;
		case SDLK_KP_DBLAMPERSAND:
			keyResult = prefix + "DBLAMPERSAND";
			break;
		case SDLK_ASTERISK:
		case SDLK_KP_MULTIPLY:
			keyResult = prefix + "ASTERISK";
			break;
		case SDLK_LEFTPAREN:
		case SDLK_KP_LEFTPAREN:
			keyResult = prefix + "LEFTPAREN";
			break;
		case SDLK_RIGHTPAREN:
		case SDLK_KP_RIGHTPAREN:
			keyResult = prefix + "RIGHTPAREN";
			break;
		case SDLK_MINUS:
		case SDLK_KP_MINUS:
			keyResult = prefix + "MINUS";
			break;
		case SDLK_UNDERSCORE:
			keyResult = prefix + "UNDERSCORE";
			break;
		case SDLK_PLUS:
		case SDLK_KP_PLUS:
			keyResult = prefix + "PLUS";
			break;
		case SDLK_EQUALS:
		case SDLK_KP_EQUALS:
			keyResult = prefix + "EQUALS";
			break;
		case SDLK_LEFTBRACKET:
			keyResult = prefix + "LEFTBRACKET";
			break;
		case SDLK_RIGHTBRACKET:
			keyResult = prefix + "RIGHTBRACKET";
			break;
		case SDLK_KP_LEFTBRACE:
			keyResult = prefix + "LEFTBRACE";
			break;
		case SDLK_KP_RIGHTBRACE:
			keyResult = prefix + "RIGHTBRACE";
			break;
		case SDLK_COLON:
			keyResult = prefix + "COLON";
			break;
		case SDLK_SEMICOLON:
			keyResult = prefix + "SEMICOLON";
			break;
		case SDLK_BACKSLASH:
			keyResult = prefix + "BACKSLASH";
			break;
		case SDLK_QUOTE:
			keyResult = prefix + "QUOTE";
			break;
		case SDLK_QUOTEDBL:
			keyResult = prefix + "QUOTEDBL";
			break;
		case SDLK_LESS:
			keyResult = prefix + "LESS";
			break;
		case SDLK_GREATER:
			keyResult = prefix + "GREATER";
			break;
		case SDLK_COMMA:
			keyResult = prefix + "COMMA";
			break;
		case SDLK_PERIOD:
			keyResult = prefix + "PERIOD";
			break;
		case SDLK_QUESTION:
			keyResult = prefix + "QUESTION";
			break;
		case SDLK_SLASH:
			keyResult = prefix + "SLASH";
			break;
		case SDLK_KP_VERTICALBAR:
			keyResult = prefix + "VERTICALBAR";
			break;
		case SDLK_KP_DBLVERTICALBAR:
			keyResult = prefix + "DBLVERTICALBAR";
			break;
		case SDLK_WWW:
			keyResult = prefix + "WWW";
			break;
		case SDLK_MAIL:
			keyResult = prefix + "EMAIL";
			break;
		default:
			break;
		}
		lua_pushstring(L, keyResult.c_str());
		break;
	default:
		break;
	}
	return 1;
}

// 暂停程序
// 无参数
// 无返回值
extern "C" int pause(lua_State * L)
{
	system("pause");
	return 0;
}

// 挂起程序指定时间
// 1参数：挂起时间（单位：毫秒）
// 无返回值
extern "C" int sleep(lua_State * L)
{
	int delay = lua_tonumber(L, 1);
	SDL_Delay(delay);
	return 0;
}

static luaL_Reg cMethods[] = {
	{ "Init", init },
	{ "Quit", quit },
	{ "GetBasePath", getBasePath },
	{ "SetClipboardText", setClipboardText },
	{ "GetClipboardText", getClipboardText },
	{ "GetPlatform", getPlatform },
	{ "GetSystemRAM", getSystemRAM },
	{ "ShowMessageBox", showMessageBox},
	{ "CreateWindow", createWindow },
	{ "SetWindowTitle", setWindowTitle },
	{ "GetWindowTitle", getWindowTitle },
	{ "SetWindowMode", setWindowMode },
	{ "SetWindowResizable", setWindowResizable },
	{ "SetWindowOpacity", setWindowOpacity },
	{ "SetWindowSize", setWindowSize },
	{ "GetWindowSize", getWindowSize },
	{ "SetWindowMaxSize", setWindowMaxSize },
	{ "GetWindowMaxSize", getWindowMaxSize },
	{ "SetWindowMinSize", setWindowMinSize },
	{ "GetWindowMinSize", getWindowMinSize },
	{ "SetWindowPosition", setWindowPosition },
	{ "GetWindowPosition", getWindowPosition },
	{ "Clear", clear },
	{ "SetCursorShow", setCursorShow },
	{ "GetCursorPosition", getCursorPosition },
	{ "GetScrollValue", getScrollValue },
	{ "LoadImage", loadImage },
	{ "LoadColorKeyImage", loadColorKeyImage },
	{ "UnloadImage", unloadImage },
	{ "SetImageAlpha", setImageAlpha },
	{ "GetImageSize", getImageSize },
	{ "ShowImage", showImage },
	{ "ShowRotateImage", showRotateImage },
	{ "ShowReshapeImage", showReshapeImage },
	{ "ShowRotateReshapeImage", showRotateReshapeImage },
	{ "SetDrawColor", setDrawColor },
	{ "Point", point },
	{ "Line", line },
	{ "Rectangle", rectangle },
	{ "FillRectangle", fillRectangle },
	{ "Update", update },
	{ "LoadMusic", loadMusic },
	{ "UnloadMusic", unloadMusic },
	{ "PlayMusic", playMusic },
	{ "FadeInMusic", fadeInMusic },
	{ "FadeOutMusic", fadeOutMusic },
	{ "SetMusicVolume", setMusicVolume },
	{ "GetMusicVolume", getMusicVolume },
	{ "PauseMusic", pauseMusic },
	{ "ResumeMusic", resumeMusic },
	{ "RewindMusic", rewindMusic },
	{ "GetMusicType", getMusicType },
	{ "LoadSound", loadSound },
	{ "UnloadSound", unloadSound },
	{ "PlaySound", playSound },
	{ "LoadFont", loadFont },
	{ "UnloadFont", unloadFont },
	{ "SetTextColor", setTextColor },
	{ "DrawText", drawText },
	{ "UpdateEvent", updateEvent },
	{ "GetEventType", getEventType },
	{ "Pause", pause },
	{ "Sleep", sleep },
	{ NULL, NULL }
};

extern "C" __declspec(dllexport)
int luaopen_QGame(lua_State * L)
{
	luaL_newlib(L, cMethods);
	return 1;
}

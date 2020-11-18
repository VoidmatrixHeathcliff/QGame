#ifndef _Q_TIME_H_
#define _Q_TIME_H_

#include <lua.hpp>
#include <SDL.h>

#include <string>
#include <vector>
using namespace std;

struct TimerCallbackParam
{
	string name = "";
	lua_State* L;
};

extern vector<TimerCallbackParam*> vParam;

// 挂起程序指定时间
// 1参数：挂起时间（单位：毫秒）
// 无返回值
extern "C" int sleep(lua_State * L);

// 获取程序从初始化运行到现在为止的时间
// 无参数
// 1返回值：运行时间（单位：毫秒）
extern "C" int getInitTime(lua_State * L);

// 获取高分辨率计数器当前值
// 无参数
// 1返回值：计数器当前值
extern "C" int getAccurateCount(lua_State * L);

// 获取高分辨率计数器频率
// 无参数
// 1返回值：计数器频率（单位：赫兹）
extern "C" int getCounterFrequency(lua_State * L);

// 新增定时器
// 2参数：定时器触发时间间隔（单位：毫秒），回调函数
// 1返回值：失败则返回-1，否则定时器ID
extern "C" int addTimer(lua_State * L);

// 移除定时器
// 1参数：定时器ID
// 1返回值：失败则返回-1，返回0
extern "C" int removeTimer(lua_State * L);

#endif // !_Q_TIME_H_

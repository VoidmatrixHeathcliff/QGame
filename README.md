# QGame开发文档

> QGame意为Quick Game或Cute Game，是一个基于[SDL](http://www.libsdl.org/)及其附加库开发的轻量级跨平台Lua游戏库，开发者可以通过简单的Lua脚本制作出效率和体积都十分出色的游戏程序，目前版本的QGame可以提供图像渲染、媒体播放控制，以及系统信息的获取和完善的交互事件处理等功能，如果在使用过程中出现任何问题或有任何建议，请联系*Voidmatrix@qq.com*

## 1. API字母顺序总览

+ CreateWindow()：创建窗口，并将此窗口作为图形绘制等操作的上下文
+ Clear()：清空绘图窗口内容
+ DrawText()：在指定位置绘制文字
+ FillRectangle()：在指定位置绘制填充矩形
+ FadeInMusic()：播放淡入音乐
+ FadeOutMusic()：淡出并停止当前正在播放的音乐
+ GetBasePath()：获取程序运行的目录
+ GetClipboardText()：获取剪切板文本
+ GetCursorPosition()：获取鼠标位置
+ GetEventType()：获取当前事件类型
+ GetImageSize()：获取已加载图像尺寸
+ GetMusicType()：获取指定音乐的类型
+ GetMusicVolume()：获取当前音乐音量
+ GetPlatform()：获取平台类型
+ GetScrollValue ()：获取鼠标滚轮滚动距离
+ GetSystemRAM()：获取系统总内存大小
+ GetWindowMaxSize()：获取窗口最大尺寸的大小
+ GetWindowMinSize()：获取窗口最小尺寸的大小
+ GetWindowPosition()：获取窗口坐标
+ GetWindowSize()：获取窗口大小
+ GetWindowTitle()：获取窗口标题
+ Init()：初始化QGame库
+ LoadImage()：加载图像文件
+ LoadColorKeyImage()：加载使用ColorKey表示透明区域的图像文件
+ Line()：在指定位置绘制直线
+ LoadMusic()：加载音乐文件
+ LoadSound()：加载音效文件
+ LoadFont()：加载字体文件
+ Point()：在指定位置绘制点
+ PlayMusic()：播放已加载的音乐
+ PauseMusic()：暂停当前正在播放的音乐
+ PlaySound()：播放已加载的音效
+ Pause()：暂停程序
+ Quit()：退出QGame库
+ Rectangle()：在指定位置绘制无填充矩形
+ ResumeMusic()：恢复当前暂停状态的音乐
+ RewindMusic()：重播当前正在播放的音乐
+ SetClipboardText()：设置剪切板文本
+ SetCursorShow()：设置鼠标是否显示
+ SetDrawColor()：设置窗口绘图颜色
+ SetImageAlpha()：设置已加载图像的透明度
+ SetMusicVolume()：设置音乐播放的音量
+ SetTextColor()：设置字体绘制颜色
+ SetWindowMaxSize()：设置窗口最大尺寸的大小
+ SetWindowMinSize()：设置窗口最小尺寸的大小
+ SetWindowMode()：设置窗口模式
+ SetWindowOpacity()：设置窗口透明度
+ SetWindowPosition()：设置窗口坐标
+ SetWindowResizable()：设置窗口是否大小可变
+ SetWindowSize()：设置窗口大小
+ SetWindowTitle ()：设置窗口标题
+ ShowImage()：显示已加载的图像
+ ShowMessageBox()：显示模态的提示信息窗口
+ ShowReshapeImage()：显示裁剪后的已加载图像
+ ShowRotateImage()：显示旋转后的已加载图像
+ ShowRotateReshapeImage()：显示旋转且裁剪后的已加载图像
+ Sleep()：挂起程序指定时间
+ UnloadImage()：释放已加载的图像
+ UnloadMusic()：释放已加载的音乐
+ UnloadSound()：释放已加载的音效
+ UnloadFont()：释放已加载的字体
+ Update()：将渲染缓冲区的内容刷新到屏幕上
+ UpdateEvent()：获取并更新事件

## 2. API功能分类及介绍

### 2.1 QGame库基础功能

> ## Init
初始化QGame库
```lua
Init()
```
**参数**

无

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()
```

> ## Quit
退出QGame库并释放资源
```lua
Quit()
```
**参数**

无

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()   -- 在初始化QGame后才可以调用Quit()
QG.Quit()
```

> ## Pause
暂停程序
```lua
Pause()
```

**参数**

无

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

print("Hello World")
QG.Pause()  -- 输出Hello World字符串后暂停程序，在控制台窗口中按下回车后程序继续运行

QG.Quit()
```

> ## Sleep
挂起程序指定时间
```lua
Sleep(ms)
```
**参数**

+ ***[number] ms***：程序挂起时间，单位为毫秒

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

print("Hello World")
QG.Sleep(5000)  -- 输出Hello World字符串五秒后退出QGame库并退出程序

QG.Quit()
os.exit()
```

### 2.2 QGame库窗口操作

> ## CreateWindow
创建窗口，并将此窗口作为图形绘制等操作的上下文
```lua
CreateWindow(title, x, y, width, height, flags)
```
**参数**

+ ***[string] title***：窗口标题
+ ***[number] x***：窗口位置的x坐标，负值表示显示在默认位置
+ ***[number] y***：窗口位置的y坐标，负值表示显示在默认位置
+ ***[number] width***：窗口宽度
+ ***[number] height***：窗口高度
+ ***[string] flags***：窗口属性标志，可以是如下值组成的字符串：

| 值  | 描述                                                   |
|:----|:-------------------------------------------------------|
| "F" | 全屏（通过更改视频模式实现）                           |
| "D" | 伪全屏（不更改视频模式，仅使用当前设备分辨率显示窗口） |
| "B" | 无边框窗口                                             |
| "R" | 窗口大小可变                                           |
| "M" | 窗口最大化                                             |
| "N" | 窗口最小化                                             |

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM") -- 创建标题为Hello World的窗口，使其最大化并且可调节大小，并将其显示在默认位置，当使用“最大化”属性来设置窗口时，设置的宽度和高度将被忽略
QG.Sleep(5000)  -- 创建窗口五秒后退出QGame库并退出程序

QG.Quit()
os.exit()
```

> ## ShowMessageBox
显示模态的提示信息窗口
```lua
ShowMessageBox(type, title, content)
```
**参数**

+ ***[string] type***：窗口类型，可以是如下值：
+ ***[string] title***：窗口标题
+ ***[string] content***：窗口内容

| 值             | 描述 |
|:---------------|:-----|
| "ERROR"        | 错误 |
| "WARNING"      | 警告 |
| "INFO"（默认） | 提示 |

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
QG.ShowMessageBox("ERROR", "错误", "程序启动失败！")
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## SetWindowTitle
设置窗口标题
```lua
SetWindowTitle(title)
```
**参数**

+ ***[string] title***：窗口标题

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
QG.Sleep(3000)  -- 3秒钟后改变窗口标题
QG.SetWindowTitle("This is new Title")
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## GetWindowTitle
获取窗口标题
```lua
title = GetWindowTitle()
```
**参数**

无

**返回值**

+ ***[string] title***：窗口标题

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
print(QG.GetWindowTitle())    -- 打印获取到的当前窗口标题
QG.Pause()

QG.Quit()
os.exit()
```

> ## SetWindowPosition
设置窗口坐标
```lua
SetWindowPosition(x, y)
```
**参数**

+ ***[number] x***：窗口位置的x坐标
+ ***[number] y***：窗口位置的y坐标

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.Sleep(3000)  -- 3秒钟后移动窗口到屏幕左上角
QG.SetWindowPosition(0, 0)
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## GetWindowPosition
获取窗口坐标
```lua
x, y = GetWindowPosition()
```
**参数**

无

**返回值**

+ ***[number] x***：窗口位置的x坐标
+ ***[number] y***：窗口位置的y坐标

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
print(QG.GetWindowPosition())    -- 打印获取到的当前窗口坐标
QG.Pause()

QG.Quit()
os.exit()
```

> ## SetWindowSize
设置窗口大小
```lua
SetWindowSize(width, height)
```
**参数**

+ ***[number] width***：窗口宽度
+ ***[number] height***：窗口高度

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.Sleep(3000)  -- 3秒钟后缩小窗口大小到原来的一半
QG.SetWindowSize(640, 360)
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## GetWindowSize
获取窗口大小
```lua
width, height = GetWindowSize()
```
**参数**

无

**返回值**

+ ***[number] width***：窗口宽度
+ ***[number] height***：窗口高度

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
print(QG.GetWindowSize())    -- 打印获取到的当前窗口大小
QG.Pause()

QG.Quit()
os.exit()
```

> ## SetWindowMaxSize
设置窗口最大尺寸的大小
```lua
SetWindowMaxSize(width, height)
```
**参数**

+ ***[number] width***：窗口宽度的最大值
+ ***[number] height***：窗口高度的最大值

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.SetWindowMaxSize(1920, 1080) -- 设置窗口最大尺寸为 1920x1080
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## GetWindowMaxSize
获取窗口最大尺寸大小
```lua
width, height = GetWindowMaxSize()
```
**参数**

无

**返回值**

+ ***[number] width***：窗口宽度的最大值
+ ***[number] height***：窗口高度的最大值

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
QG.SetWindowMaxSize(1920, 1080) -- 设置窗口最大尺寸为 1920x1080
print(QG.GetWindowMaxSize())    -- 打印获取到的窗口最大尺寸大小
QG.Pause()

QG.Quit()
os.exit()
```

> ## SetWindowMinSize
设置窗口最小尺寸的大小
```lua
SetWindowMinSize(width, height)
```
**参数**

+ ***[number] width***：窗口宽度的最小值
+ ***[number] height***：窗口高度的最小值

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.SetWindowMinSize(640, 360) -- 设置窗口最小尺寸为 640x360
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## GetWindowMinSize
获取窗口最小尺寸大小
```lua
width, height = GetWindowMinSize()
```
**参数**

无

**返回值**

+ ***[number] width***：窗口宽度的最小值
+ ***[number] height***：窗口高度的最小值

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
QG.SetWindowMinSize(640, 360) -- 设置窗口最大尺寸为 1920x1080
print(QG.GetWindowMinSize())    -- 打印获取到的窗口最大尺寸大小
QG.Pause()

QG.Quit()
os.exit()
```

> ## SetWindowMode
设置窗口模式
```lua
SetWindowMode(mode)
```
**参数**

+ ***[number] mode***：窗口模式，可以是如下值：

| 值 | 描述                       |
|:---|:---------------------------|
| 0  | 窗口模式                   |
| 1  | 视频模式改变的真全屏模式   |
| 2  | 使用当前屏幕分辨率的假全屏 |

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.Sleep(3000)  -- 窗口创建3秒后设置窗口模式为真全屏且使用 1280x720 的分辨率显示
QG.SetWindowMode(1)
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## SetWindowResizable
设置窗口是否大小可变
```lua
SetWindowResizable(value)
```
**参数**

+ ***[boolean] value***：是否大小可变

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "M")
QG.SetWindowResizable(true) -- 设置窗口大小可变，与在CreateWindow函数中使用"R"标志效果相同
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## SetWindowOpacity
设置窗口透明度
```lua
SetWindowOpacity(value)
```
**参数**

+ ***[number] value***：窗口透明度，取值范围为0.0-1.0

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.SetWindowOpacity(0.5) -- 设置窗口为半透明
QG.Sleep(5000)

QG.Quit()
os.exit()
```

### 2.3 QGame库图形相关操作

> ## Update
将渲染缓冲区的内容刷新到屏幕上
```lua
Update()
```
**参数**

无

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
-- 进行相关绘图操作
QG.Update()  -- 更新屏幕内容
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## Clear
使用当前绘图颜色清空窗口内容
```lua
Clear()
```
**参数**

无

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.Clear()  -- 默认使用的清空颜色为黑色
QG.Update()
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## SetCursorShow
设置鼠标是否显示
```lua
SetCursorShow(value)
```
**参数**

+ ***[boolean] value***：是否显示鼠标

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.SetCursorShow(false) -- 设置鼠标在窗口内不显示
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## SetDrawColor
设置窗口绘图颜色
```lua
SetDrawColor(R, G, B, A)
```
**参数**

+ ***[number] R***：窗口绘图颜色的红色分量，取值范围为 0-255
+ ***[number] G***：窗口绘图颜色的绿色分量，取值范围为 0-255
+ ***[number] B***：窗口绘图颜色的蓝色分量，取值范围为 0-255
+ ***[number] A***：窗口绘图颜色的透明度，取值范围为 0-255

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.SetDrawColor(255, 0, 0, 255) -- 设置窗口绘图颜色为红色
QG.Clear()  -- 使用红色清空当前窗口
QG.Update()
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## Point
在指定位置绘制点
```lua
Point(x, y)
```
**参数**

+ ***[number] x***：点所在位置的x坐标
+ ***[number] y***：点所在位置的y坐标

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.SetDrawColor(255, 0, 0, 255) -- 设置窗口绘图颜色为红色
QG.Point(640, 360)  -- 在窗口的中心画一个红色的像素点
QG.Update()
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## Line
在指定位置绘制直线
```lua
Line(x1, y1, x2, y2)
```
**参数**

+ ***[number] x1***：直线起点所在位置的x坐标
+ ***[number] y1***：直线起点所在位置的y坐标
+ ***[number] x2***：直线终点所在位置的x坐标
+ ***[number] y2***：直线终点所在位置的y坐标

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.SetDrawColor(255, 0, 0, 255) -- 设置窗口绘图颜色为红色
QG.Line(0, 0, 640, 360)  -- 从窗口的左上角到窗口中心画一条红色直线
QG.Update()
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## Rectangle
在指定位置绘制无填充矩形
```lua
Rectangle(x, y, width, height)
```
**参数**

+ ***[number] x***：矩形左上角所在位置的x坐标
+ ***[number] y***：矩形左上角所在位置的y坐标
+ ***[number] width***：矩形宽度
+ ***[number] height***：矩形高度

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.SetDrawColor(255, 0, 0, 255) -- 设置窗口绘图颜色为红色
QG.Rectangle(25, 25, 640, 360)  -- 绘制红色无填充矩形
QG.Update()
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## FillRectangle
在指定位置绘制填充矩形
```lua
FillRectangle(x, y, width, height)
```
**参数**

+ ***[number] x***：矩形左上角所在位置的x坐标
+ ***[number] y***：矩形左上角所在位置的y坐标
+ ***[number] width***：矩形宽度
+ ***[number] height***：矩形高度

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
QG.SetDrawColor(255, 0, 0, 255) -- 设置窗口绘图颜色为红色
QG.FillRectangle(25, 25, 640, 360)  -- 绘制红色填充矩形
QG.Update()
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## LoadImage
加载图像文件
```lua
flag = LoadImage(path)
```
**参数**

+ ***[string] path***：图像文件路径

**返回值**

+ ***[number] flag***：-1表示加载文件失败，否则返回已加载的图像文件在图像库中的标志

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
flag = QG.LoadImage("hello.jpg")
if flag == -1 then
    error("Failed to load 'hello.jpg'!")    -- 图片文件加载失败则输出错误信息
else
    -- 处理加载图片成功后任务
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## LoadColorKeyImage
加载使用ColorKey表示透明区域的图像文件
```lua
flag = LoadColorKeyImage(path, R, G, B)
```
**参数**

+ ***[string] path***：图像文件路径
+ ***[number] R***：ColorKey的红色分量
+ ***[number] G***：ColorKey的绿色分量
+ ***[number] B***：ColorKey的蓝色分量

**返回值**

+ ***[number] flag***：-1表示加载文件失败，否则返回已加载的图像文件在图像库中的标志

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
flag = QG.LoadColorKeyImage("hello.jpg", 0, 0, 0)   -- 加载使用黑色表示透明区域的hello.jpg图像文件
if flag == -1 then
    error("Failed to load 'hello.jpg'!")    -- 图片文件加载失败则输出错误信息
else
    -- 处理加载图片成功后任务
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## UnloadImage
释放已加载的图像
```lua
result = UnloadImage(flag)
```
**参数**

+ ***[number] flag***：已加载的图像文件在图像库中的标志

**返回值**

+ ***[number] result***：-1表示释放图像失败，0表示释放图像成功

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
flag = QG.LoadImage("hello.jpg")
if flag == -1 then
    error("Failed to load 'hello.jpg'!")    -- 图片文件加载失败则输出错误信息
else
    result = QG.UnloadImage(flag)   -- 如果图片加载成功则释放该图像
    if result == -1 then
        error("Failed to unload 'hello.jpg'!")  -- 图片文件释放失败则输出错误信息
    else
        -- 处理释放图片成功后任务
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## ShowImage
显示已加载的图像
```lua
result = ShowImage(flag, x, y, width, height)
```
**参数**

+ ***[number] flag***：已加载的图像文件在图像库中的标志
+ ***[number] x***：图像显示位置的x坐标
+ ***[number] y***：图像显示位置的y坐标
+ ***[number] width***：图像显示宽度，-1表示使用原图像尺寸
+ ***[number] height***：图像显示高度，-1表示使用原图像尺寸

**返回值**

+ ***[number] result***：-1表示显示图像失败，0表示显示图像成功

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
if QG.ShowImage(QG.LoadImage("hello.jpg"), 0, 0, -1, -1) == -1 then
    error("Failed to load and show 'hello.jpg'!")   -- 图片文件加载并显示失败则输出错误信息
else
    -- 处理加载图片加载并显示成功后任务
    QG.Update()
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## ShowRotateImage
显示旋转后的已加载图像
```lua
result = ShowRotateImage(flag, angle, center_x, center_y, mode, x, y, width, height)
```
**参数**

+ ***[number] flag***：已加载的图像文件在图像库中的标志
+ ***[number] angle***：顺时针旋转角度
+ ***[number] center_x***：旋转中心x坐标
+ ***[number] center_y***：旋转中心y坐标
+ ***[number] mode***：翻转模式，可以是如下值：

| 值           | 描述                 |
|:-------------|:---------------------|
| "NONE"       | 不进行翻转（默认值） |
| "HORIZONTAL" | 水平翻转             |
| "VERTICAL"   | 垂直翻转             |

+ ***[number] x***：图像显示位置的x坐标
+ ***[number] y***：图像显示位置的y坐标
+ ***[number] width***：图像显示宽度，-1表示使用原图像尺寸
+ ***[number] height***：图像显示高度，-1表示使用原图像尺寸

**返回值**

+ ***[number] result***：-1表示显示图像失败，0表示显示图像成功

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
if QG.ShowRotateImage(QG.LoadImage("hello.jpg"), 45, 0, 0, "NONE", 0, 0, -1, -1) == -1 then  -- 将原图像绕左上角顺时针旋转45°并以原图像尺寸显示在屏幕左上角位置
    error("Failed to load and show 'hello.jpg'!")   -- 图片文件加载并显示失败则输出错误信息
else
    -- 处理加载图片加载并显示成功后任务
    QG.Update()
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## ShowReshapeImage
显示已加载的图像
```lua
result = ShowReshapeImage(flag, cut_x, cut_y, cut_width, cut_height, x, y, width, height)
```
**参数**

+ ***[number] flag***已加载的图像文件在图像库中的标志
+ ***[number] cut_x***：裁剪位置在原图像位置的x坐标
+ ***[number] cut_y***：裁剪位置在原图像位置的y坐标
+ ***[number] cut_width***：裁剪区域宽度，-1表示使用原图像尺寸
+ ***[number] cut_height***：裁剪区域高度，-1表示使用原图像尺寸
+ ***[number] x***：图像显示位置的x坐标
+ ***[number] y***：图像显示位置的y坐标
+ ***[number] width***：图像显示宽度，-1表示使用原图像尺寸
+ ***[number] height***：图像显示高度，-1表示使用原图像尺寸

**返回值**

+ ***[number] result***：-1表示显示图像失败，0表示显示图像成功

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
if QG.ShowReshapeImage(QG.LoadImage("hello.jpg"), 0, 0, 100, 100, 0, 0, -1, -1) == -1 then  -- 从原图像的(0, 0)位置裁剪长宽均为100像素的矩形区域并以原图像尺寸显示在屏幕左上角位置
    error("Failed to load and show 'hello.jpg'!")   -- 图片文件加载并显示失败则输出错误信息
else
    -- 处理加载图片加载并显示成功后任务
    QG.Update()
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## ShowRotateReshapeImage
显示旋转且裁剪后的已加载图像
```lua
result = ShowRotateReshapeImage(flag, angle, center_x, center_y, mode, cut_x, cut_y, cut_width, cut_height, x, y, width, height)
```
**参数**

+ ***[number] flag***：已加载的图像文件在图像库中的标志
+ ***[number] angle***：顺时针旋转角度
+ ***[number] center_x***：旋转中心x坐标
+ ***[number] center_y***：旋转中心y坐标
+ ***[number] mode***：翻转模式，可以是如下值：

| 值           | 描述                 |
|:-------------|:---------------------|
| "NONE"       | 不进行翻转（默认值） |
| "HORIZONTAL" | 水平翻转             |
| "VERTICAL"   | 垂直翻转             |

+ ***[number] cut_x***：裁剪位置在原图像位置的x坐标
+ ***[number] cut_y***：裁剪位置在原图像位置的y坐标
+ ***[number] cut_width***：裁剪区域宽度，-1表示使用原图像尺寸
+ ***[number] cut_height***：裁剪区域高度，-1表示使用原图像尺寸
+ ***[number] x***：图像显示位置的x坐标
+ ***[number] y***：图像显示位置的y坐标
+ ***[number] width***：图像显示宽度，-1表示使用原图像尺寸
+ ***[number] height***：图像显示高度，-1表示使用原图像尺寸

**返回值**

+ ***[number] result***：-1表示显示图像失败，0表示显示图像成功

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
if QG.ShowRotateReshapeImage(QG.LoadImage("hello.jpg"), 45, 0, 0, "NONE", 0, 0, 100, 100, 0, 0, -1, -1) == -1 then  -- 从原图像的(0, 0)位置裁剪长宽均为100像素的矩形区域后绕左上角顺时针旋转45°并以原图像尺寸显示在屏幕左上角位置
    error("Failed to load and show 'hello.jpg'!")   -- 图片文件加载并显示失败则输出错误信息
else
    -- 处理加载图片加载并显示成功后任务
    QG.Update()
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## GetImageSize
获取已加载图像尺寸
```lua
width, height = GetImageSize(flag)
```
**参数**

+ ***[number] flag***：已加载的图像文件在图像库中的标志

**返回值**

+ ***[number] width***：-1获取图像尺寸失败，否则返回指定图像的宽度
+ ***[number] height***：-1获取图像尺寸失败，否则返回指定图像的高度

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
width, height = GetImageSize(QG.LoadImage("hello.jpg"))
print(width, height)    -- 打印 hello.jpg 图像文件的宽度和高度
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## SetImageAlpha
获取已加载图像尺寸
```lua
result = SetImageAlpha(flag, value)
```
**参数**

+ ***[number] flag***：已加载的图像文件在图像库中的标志
+ ***[number] value***：需要设置的透明度数值，取值范围为 0-255

**返回值**

+ ***[number] result***：-1表示设置图像透明度失败，0表示设置图像透明度成功

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
if SetImageAlpha(QG.LoadImage("hello.jpg"), 125) == -1 then
    error("Failed to set alpha value of 'hello.jpg'!")   -- 设置图像透明度失败则输出错误信息
else
    -- 处理设置图像透明度成功后任务
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## LoadFont
加载字体文件
```lua
flag = LoadFont(path, size)
```
**参数**

+ ***[string] path***：字体文件路径
+ ***[number] size***：字体大小

**返回值**

+ ***[number] flag***：-1表示加载文件失败，否则返回已加载的字体文件在字体库中的标志

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
flag = QG.LoadFont("hello.ttf", 20)
if flag == -1 then
    error("Failed to load 'hello.ttf'!")    -- 字体文件加载失败则输出错误信息
else
    -- 处理加载字体成功后任务
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## UnloadFont
释放已加载的字体
```lua
result = UnloadFont(flag)
```
**参数**

+ ***[number] flag***：已加载的字体文件在字体库中的标志

**返回值**

+ ***[number] result***：-1表示释放字体失败，0表示释放字体成功

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
flag = QG.LoadFont("hello.ttf", 20)
if flag == -1 then
    error("Failed to load 'hello.ttf'!")    -- 字体文件加载失败则输出错误信息
else
    result = QG.UnloadFont(flag)   -- 如果字体加载成功则释放该字体
    if result == -1 then
        error("Failed to unload 'hello.ttf'!")  -- 字体文件释放失败则输出错误信息
    else
        -- 处理释放字体成功后任务
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## SetTextColor
设置字体绘制颜色
```lua
SetTextColor(R, G, B, A)
```
**参数**

+ ***[number] R***：字体绘制颜色的红色分量，取值范围为 0-255
+ ***[number] G***：字体绘制颜色的绿色色分量，取值范围为 0-255
+ ***[number] B***：字体绘制颜色的蓝色分量，取值范围为 0-255
+ ***[number] A***：字体绘制的Alpha通道值，取值范围为 0-255

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
flag = QG.LoadFont("hello.ttf")
if flag == -1 then
    error("Failed to load 'hello.ttf'!")    -- 字体文件加载失败则输出错误信息
else
    QG.SetTextColor(255, 0, 0, 255)    -- 设置字体颜色为红色
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## DrawText
在指定位置绘制文字
```lua
DrawText(flag, text, x, y, width, height)
```
**参数**

+ ***[number] flag***：已加载的字体文件在字体库中的标志
+ ***[string] text***：文字内容
+ ***[number] x***：文字显示位置的x坐标
+ ***[number] y***：文字显示位置的y坐标
+ ***[number] width***：文字显示宽度，-1表示使用原文字尺寸
+ ***[number] height***：文字显示高度，-1表示使用原文字尺寸

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
flag = QG.LoadFont("hello.ttf", 20)
if flag == -1 then
    error("Failed to load 'hello.ttf'!")    -- 字体文件加载失败则输出错误信息
else
    QG.SetTextColor(255, 0, 0, 255)    -- 设置字体颜色为红色
    QG.DrawText(flag, "Hello World", 0, 0, -1, -1)  -- 在窗口左上角绘制"Hello World"
    QG.Update()
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

### 2.4 QGame库媒体相关操作

> ## LoadMusic
加载音乐文件
```lua
flag = LoadMusic(path)
```
**参数**

+ ***[string] path***：音乐文件路径

**返回值**

+ ***[number] flag***：-1表示加载文件失败，否则返回已加载的音乐文件在音乐库中的标志

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QGame.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    -- 处理加载音乐成功后任务
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## UnloadMusic
释放已加载的音乐
```lua
result = UnloadMusic(flag)
```
**参数**

+ ***[number] flag***：已加载的音乐文件在音乐库中的标志

**返回值**

+ ***[number] result***：-1表示释放音乐失败，0表示释放音乐成功

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    result = QG.UnloadMusic(flag)   -- 如果音乐加载成功则释放该音乐
    if result == -1 then
        error("Failed to unload 'hello.mp3'!")  -- 音乐文件释放失败则输出错误信息
    else
        -- 处理释放音乐成功后任务
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## PlayMusic
播放已加载的音乐
```lua
result = PlayMusic(flag, loops)
```
**参数**

+ ***[number] flag***：已加载的音乐文件在音乐库中的标志
+ ***[number] loops***：音乐播放的次数，-1为循环播放

**返回值**

+ ***[number] result***：-1表示播放音乐失败，0表示播放音乐成功

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    result = QG.PlayMusic(flag, -1)   -- 如果音乐加载成功则循环播放该音乐
    if result == -1 then
        error("Failed to play 'hello.mp3'!")  -- 音乐文件播放失败则输出错误信息
    else
        -- 处理播放音乐成功后任务
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## FadeInMusic
使用淡入效果播放已加载的音乐
```lua
result = FadeInMusic(flag, loops, ms)
```
**参数**

+ ***[number] flag***：已加载的音乐文件在音乐库中的标志
+ ***[number] loops***：音乐播放的次数，-1为循环播放
+ ***[number] ms***：淡入音效持续时间，单位为毫秒

**返回值**

+ ***[number] result***：-1表示播放音乐失败，0表示播放音乐成功

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    result = QG.FadeInMusic(flag, -1, 1000)   -- 如果音乐加载成功则使用1秒的淡入效果循环播放该音乐
    if result == -1 then
        error("Failed to play 'hello.mp3'!")  -- 音乐文件播放失败则输出错误信息
    else
        -- 处理播放音乐成功后任务
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## FadeOutMusic
淡出并停止当前正在播放的音乐
```lua
FadeOutMusic(ms)
```
**参数**

+ ***[number] ms***：淡出音效持续时间，单位为毫秒

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    result = QG.PlayMusic(flag, -1)   -- 如果音乐加载成功则循环播放该音乐
    if result == -1 then
        error("Failed to play 'hello.mp3'!")  -- 音乐文件播放失败则输出错误信息
    else
        QG.Sleep(3000)  -- 如果音乐播放成功则3秒后使用1秒的淡出音效结束音乐播放
        QG.FadeOutMusic(1000)
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## SetMusicVolume
设置音乐播放的音量
```lua
SetMusicVolume(value)
```
**参数**

+ ***[number] value***：音量大小，取值范围为 0-128，默认音量大小为128

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    result = QG.PlayMusic(flag, -1)   -- 如果音乐加载成功则循环播放该音乐
    if result == -1 then
        error("Failed to play 'hello.mp3'!")  -- 音乐文件播放失败则输出错误信息
    else
        QG.Sleep(3000)  -- 如果音乐播放成功则3秒后减半音量播放
        QG.SetMusicVolume(64)
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## GetMusicVolume
获取当前音乐音量
```lua
value = GetMusicVolume()
```
**参数**

无

**返回值**

+ ***[number] value***：音量大小，取值范围为 0-128

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    result = QG.PlayMusic(flag, -1)   -- 如果音乐加载成功则循环播放该音乐
    if result == -1 then
        error("Failed to play 'hello.mp3'!")  -- 音乐文件播放失败则输出错误信息
    else
        print(QG.GetMusicVolume())  -- 如果音乐播放成功输出当前音乐音量大小
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## PauseMusic
暂停当前正在播放的音乐
```lua
PauseMusic()
```
**参数**

无

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    result = QG.PlayMusic(flag, -1)   -- 如果音乐加载成功则循环播放该音乐
    if result == -1 then
        error("Failed to play 'hello.mp3'!")  -- 音乐文件播放失败则输出错误信息
    else
        QG.Sleep(3000)  -- 如果音乐播放成功则3秒后暂停
        QG.PauseMusic()
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## ResumeMusic
恢复当前暂停状态的音乐
```lua
ResumeMusic()
```
**参数**

无

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    result = QG.PlayMusic(flag, -1)   -- 如果音乐加载成功则循环播放该音乐
    if result == -1 then
        error("Failed to play 'hello.mp3'!")  -- 音乐文件播放失败则输出错误信息
    else
        QG.Sleep(3000)  -- 如果音乐播放成功则3秒后暂停
        QG.PauseMusic()
        QG.Sleep(3000)  -- 3秒后重新恢复播放
        QG.ResumeMusic()
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## RewindMusic
重播当前正在播放的音乐
```lua
RewindMusic()
```
**参数**

无

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    result = QG.PlayMusic(flag, -1)   -- 如果音乐加载成功则循环播放该音乐
    if result == -1 then
        error("Failed to play 'hello.mp3'!")  -- 音乐文件播放失败则输出错误信息
    else
        QG.Sleep(3000)  -- 如果音乐播放成功则3秒后重播当前播放的音乐
        QG.RewindMusic()
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## GetMusicType
获取指定音乐的类型
```lua
typeName = GetMusicType(flag)
```
**参数**

+ ***[number] flag***：已加载的音乐文件在音乐库中的标志

**返回值**

+ ***[string] typeName***：成功则返回指定音乐的类型的字符串，未知则返回"UNKONWN"，失败则返回"ERROR"

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadMusic("hello.mp3")
if flag == -1 then
    error("Failed to load 'hello.mp3'!")    -- 音乐文件加载失败则输出错误信息
else
    print(QG.GetMusicType(flag))    -- 如果音乐加载成功则输出该音乐的类型
end
QG.Pause()

QG.Quit()
os.exit()
```

> ## LoadSound
加载音效文件
```lua
flag = LoadSound(path)
```
**参数**

+ ***[string] path***：音效文件路径

**返回值**

+ ***[number] flag***：-1表示加载文件失败，否则返回已加载的音效文件在音效库中的标志

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QGame.LoadSound("hello.wav")
if flag == -1 then
    error("Failed to load 'hello.wav'!")    -- 音效文件加载失败则输出错误信息
else
    -- 处理加载音效成功后任务
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## UnloadSound
释放已加载的音效
```lua
result = UnloadSound(flag)
```
**参数**

+ ***[number] flag***：已加载的音效文件在音效库中的标志

**返回值**

+ ***[number] result***：-1表示释放音效失败，0表示释放音效成功

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadSound("hello.wav")
if flag == -1 then
    error("Failed to load 'hello.wav'!")    -- 音效文件加载失败则输出错误信息
else
    result = QG.UnloadSound(flag)   -- 如果音效加载成功则释放该音效
    if result == -1 then
        error("Failed to unload 'hello.wav'!")  -- 音效文件释放失败则输出错误信息
    else
        -- 处理释放音效成功后任务
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

> ## PlaySound
播放已加载的音效
```lua
result = PlaySound(flag, loops)
```
**参数**

+ ***[number] flag***：已加载的音效文件在音效库中的标志
+ ***[number] loops***：音效播放的次数，-1为循环播放

**返回值**

+ ***[number] result***：-1表示播放音效失败，0表示播放音效成功

**示例**

```lua
QG = require("QGame")

QG.Init()

flag = QG.LoadSound("hello.wav")
if flag == -1 then
    error("Failed to load 'hello.wav'!")    -- 音效文件加载失败则输出错误信息
else
    result = QG.PlaySound(flag, -1)   -- 如果音效加载成功则循环播放该音效
    if result == -1 then
        error("Failed to play 'hello.wav'!")  -- 音效文件播放失败则输出错误信息
    else
        -- 处理播放音效成功后任务
    end
end
QG.Sleep(5000)

QG.Quit()
os.exit()
```

### 2.5 QGame库交互事件处理

> ## UpdateEvent
获取并更新事件
```lua
result = UpdateEvent()
```
**参数**

无

**返回值**

+ ***[number] result***：获取事件结果，-1表示当前事件队列无待解决事件，0表示获取到新事件

**示例**

```lua
QG = require("QGame")

QG.Init()
QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
while true do
    if QG.UpdateEvent() == 0 then    -- 循环获取并更新事件
        -- 处理获取到的新事件
    end
end

QG.Quit()
os.exit()
```

> ## GetEventType
获取当前事件类型
```lua
event = GetEventType()
```
**参数**

无

**返回值**

+ ***[string] event***：表示当前事件类型的字符串，可以是如下值：

***基础事件***

| 值     | 描述 |
|:-------|:-----|
| "QUIT" | 退出 |

***窗口事件***

| 值              | 描述         |
|:----------------|:-------------|
| "QUIT"          | 窗口退出     |
| "WINDOWSHOW"    | 窗口显示     |
| "WINDOWHIDE"    | 窗口隐藏     |
| "WINDOWMOVE"    | 窗口移动     |
| "WINDOWRESIZE"  | 窗口尺寸变化 |
| "WINDOWMINSIZE" | 窗口最小化   |
| "WINDOWMAXSIZE" | 窗口最大化   |
| "WINDOWENTER"   | 光标移入窗口 |
| "WINDOWLEAVE"   | 光标离开窗口 |
| "WINDOWFOCUS"   | 窗口获得焦点 |
| "WINDOWLOST"    | 窗口失去焦点 |
| "WINDOWCLOSE"   | 窗口关闭     |

***鼠标事件***

| 值                | 描述             |
|:------------------|:-----------------|
| "MOUSEMOTION"     | 鼠标移动         |
| "MOUSEBUTTON_D_L" | 鼠标左键按下     |
| "MOUSEBUTTON_D_R" | 鼠标右键按下     |
| "MOUSEBUTTON_D_M" | 鼠标中键按下     |
| "MOUSEBUTTON_U_L" | 鼠标左键抬起     |
| "MOUSEBUTTON_U_R" | 鼠标右键抬起     |
| "MOUSEBUTTON_U_M" | 鼠标中键抬起     |
| "MOUSESCROLL_U"   | 鼠标滚轮向上滚动 |
| "MOUSESCROLL_D"   | 鼠标滚轮向下滚动 |
| "MOUSESCROLL_R"   | 鼠标滚轮向右滚动 |
| "MOUSESCROLL_L"   | 鼠标滚动向左滚动 |

***键盘事件***

键盘事件由前缀和后缀组成，前缀分别使用`"KEYDOWN"`和`"KEYUP"`来表示按键按下事件和抬起事件，后缀则由下述的按键描述符组成，通过下划线`"_"`连接共同构成完整的键盘事件，全部键盘事件见附录

**示例**

```lua
QG = require("QGame")

QG.Init()
QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
while true do
    if QG.UpdateEvent() == 0 then   -- 循环获取并更新事件
        if QG.GetEventType() == "QUIT" then
            QG.Quit()   -- 如果是窗口退出事件，则关闭窗口并退出QGame库
            break
        elseif QG.GetEventType() == "KEYDOWN_X" then
            print("The 'X' key down !")    -- 如果是键盘X键按下事件则输出提示信息
        end
    end
end

os.exit()
```

> ## GetCursorPosition
获取鼠标位置
```lua
x, y = GetCursorPosition()
```
**参数**

无

**返回值**

+ ***[number] x***：鼠标位置的x坐标
+ ***[number] y***：鼠标位置的y坐标

**示例**

```lua
QG = require("QGame")

QG.Init()

QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
while true do
    if QG.UpdateEvent() == 0 then   -- 循环获取并更新事件
        if QG.GetEventType() == "QUIT" then
            QG.Quit()   -- 如果是窗口退出事件，则关闭窗口并退出QGame库
            break
        elseif QG.GetEventType() == "MOUSEMOTION" then
            print(QG.GetCursorPosition())    -- 如果是鼠标移动事件则打印当前鼠标位置
        end
    end
end

os.exit()
```

### 2.6 QGame库其它功能

> ## GetBasePath
获取程序运行的目录
```lua
basepath = GetBasePath()
```
**参数**

无

**返回值**

+ ***[string] basepath***：程序运行目录

**示例**

```lua
QG = require("QGame")

QG.Init()
basepath = QG.GetBasePath()
print(basepath)
QG.Pause()

os.exit()
```

> ## GetPlatform
获取平台类型
```lua
platform = GetPlatform()
```
**参数**

无

**返回值**

+ ***[string] platform***：平台类型

**示例**

```lua
QG = require("QGame")

QG.Init()
platform = QG.GetPlatform()
print(platform)
QG.Pause()

os.exit()
```

> ## GetSystemRAM
获取系统总内存大小
```lua
ram = GetSystemRAM()
```
**参数**

无

**返回值**

+ ***[number] ram***：系统内存大小，单位为MB

**示例**

```lua
QG = require("QGame")

QG.Init()
ram = QG.GetSystemRAM()
print(ram)
QG.Pause()

os.exit()
```

> ## SetClipboardText
设置剪切板文本
```lua
SetClipboardText(text)
```
**参数**

+ ***[string] text***：剪切板文本

**返回值**

无

**示例**

```lua
QG = require("QGame")

QG.Init()
QG.SetClipboardText("Hello World !")

QG.Quit()
os.exit()
```

> ## GetClipboardText
获取剪切板文本
```lua
text = GetClipboardText()
```
**参数**

无

**返回值**

+ ***[string] text***：剪切板文本

**示例**

```lua
QG = require("QGame")

QG.Init()
QG.SetClipboardText("Hello World !")
text = QG.GetClipboardText()
print(text)
QG.Pause()

os.exit()
```

## 3. 附录

> ## 键盘事件对应表

### ***前缀***

| 值        | 描述     |
|:----------|:---------|
| "KEYDOWN" | 按键按下 |
| "KEYUP"   | 按键抬起 |

### ***后缀***

**注意：**
部分字符的按键事件为虚拟事件，在大部分键盘上可能无法通过物理按键触发

| 值              | 描述            |
|:----------------|:----------------|
| "0"             | 0               |
| "00"            | 00              |
| "000"           | 000             |
| "1"             | 1               |
| "2"             | 2               |
| "3"             | 3               |
| "4"             | 4               |
| "5"             | 5               |
| "6"             | 6               |
| "7"             | 7               |
| "8"             | 8               |
| "9"             | 9               |
| "F1"            | F1              |
| "F2"            | F2              |
| "F3"            | F3              |
| "F4"            | F4              |
| "F5"            | F5              |
| "F6"            | F6              |
| "F7"            | F7              |
| "F8"            | F8              |
| "F9"            | F9              |
| "F10"           | F10             |
| "F11"           | F11             |
| "F12"           | F12             |
| "F13"           | F13             |
| "F14"           | F14             |
| "F15"           | F15             |
| "F16"           | F16             |
| "F17"           | F17             |
| "F18"           | F18             |
| "F19"           | F19             |
| "F20"           | F20             |
| "F21"           | F21             |
| "F22"           | F22             |
| "F23"           | F23             |
| "F24"           | F24             |
| "A"             | A               |
| "B"             | B               |
| "C"             | C               |
| "D"             | D               |
| "E"             | E               |
| "F"             | F               |
| "G"             | G               |
| "H"             | H               |
| "I"             | I               |
| "J"             | J               |
| "K"             | K               |
| "L"             | L               |
| "M"             | M               |
| "N"             | N               |
| "O"             | O               |
| "P"             | P               |
| "Q"             | Q               |
| "R"             | R               |
| "S"             | S               |
| "T"             | T               |
| "U"             | U               |
| "V"             | V               |
| "W"             | W               |
| "X"             | X               |
| "Y"             | Y               |
| "Z"             | Z               |
| "ESC"           | Esc             |
| "ENTER"         | Enter           |
| "BACKSPACE"     | Backspace       |
| "UP"            | ↑               |
| "DOWN"          | ↓               |
| "LEFT"          | ←               |
| "RIGHT"         | →               |
| "INSERT" | Insert |
| "DELETE" | Delete |
| "HOME" | Home |
| "END" | End |
| "PAGEUP" | PageUp |
| "PAGEDOWN" | pageDown |
| "LCTRL" | 左Ctrl键 |
| "LGUI" | 左GUI键（Windows系统下为Win键，Mac系统下为Command键） |
| "LALT" | 左Alt键 |
| "LSHIFT" | 左Shift键 |
| "RCTRL" | 右Ctrl键 |
| "RGUI" | 右GUI键（Windows系统下为Win键，Mac系统下为Command键） |
| "RALT" | 右Alt键 |
| "RSHIFT" | 右Shift键 |
| "SPACE" | 空格键 |
| "TAB" | Tab键 |
| "CAPSLOCK" | CapsLock |
| "NUMLOCK" | NumLock |
| "PRINTSCREEN" | PrintScreen |
| "SCROLLLOCK" | ScrollLock |
| "PAUSE" | 媒体播放暂停键 |
| "AUDIOMUTE" | 静音键 |
| "AUDIOPREV" | 媒体播放上一首键 |
| "AUDIONEXT" | 媒体播放下一首键 |
| "AUDIOPLAY" | 媒体播放开始键 |
| "AUDIOSTOP" | 媒体播放停止键 |
| "VOLUMEUP" | 音量增大键 |
| "VOLUMEDOWN" | 音量减小键 |
| "BRIGHTNESSUP" | 亮度增加键 |
| "BRIGHTNESSDOWN" | 亮度减少键 |
| "BACKQUOTE" | ` |
| "EXCLAM" | ! |
| "AT" | @ |
| "HASH" | # |
| "DOOLAR" | $ |
| "CARET" | ^ |
| "AMPERSAND" | & |
| "DBLAMPERSAND" | && |
| "ASTERISK" | * |
| "LEFTPAREN" | ( |
| "RIGHTPAREN" | ) |
| "MINUS" | - |
| "UNDERSCORE" | _ |
| "PLUS" | + |
| "EQUALS" | = |
| "LEFTBRACKET" | [ |
| "RIGHTBRACKET" | ] |
| "LEFTBRACE" | { |
| "RIGHTBRACE" | } |
| "COLON" | : |
| "SEMICOLON" | ; |
| "BACKSLASH" | \ |
| "QUOTE" | ' |
| "QUOTEDBL" | " |
| "LESS" | < |
| "GREATER" | > |
| "COMMA" | , |
| "PERIOD" | . |
| "QUESTION" | ? |
| "SLASH" | / |
| "VERTICALBAR" | \| |
| "DBLVERTICALBAR" | \|\| |
| "WWW" | WWW |
| "EMAIL" | Email |


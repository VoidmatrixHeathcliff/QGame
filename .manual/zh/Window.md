# QGame库窗口操作

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

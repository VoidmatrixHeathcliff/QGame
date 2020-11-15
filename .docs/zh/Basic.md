# QGame库基础功能

> ## Init
> 初始化QGame库
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
> 退出QGame库并释放资源
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
> 暂停程序
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
> 挂起程序指定时间
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
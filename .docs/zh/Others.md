# QGame库其它功能

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
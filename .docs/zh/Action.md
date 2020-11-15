# QGame库交互事件处理

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
# QGame库图形相关操作

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
# QGame库媒体相关操作
 
> ## LoadMusic
> 加载音乐文件
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
> 释放已加载的音乐
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
> 播放已加载的音乐
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
> 使用淡入效果播放已加载的音乐
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
> 淡出并停止当前正在播放的音乐
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
> 设置音乐播放的音量
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
> 获取当前音乐音量
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
> 暂停当前正在播放的音乐
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
> 恢复当前暂停状态的音乐
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
> 重播当前正在播放的音乐
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
> 获取指定音乐的类型
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
> 加载音效文件
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
> 释放已加载的音效
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
> 播放已加载的音效
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
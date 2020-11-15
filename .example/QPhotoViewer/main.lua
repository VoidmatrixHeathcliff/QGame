QG = require("QGame")
ET = require("EasyTool")

MIN_SIZE = {width = 627, height = 627}  -- 定义窗口最大尺寸
TEXT_COLOR = {R = 185, G = 185, B = 185, A = 255}   -- 定义文字颜色
DRAW_COLOR = {R = 34, G = 34, B = 34, A = 255}  -- 定义绘图颜色
MARGIN_WIDTH = 40   -- 定义显示图片的面板与窗口边框间的距离
BUTTON_WIDTH = MARGIN_WIDTH     -- 定义按钮宽度
BUTTON_HEIGHT = 80      -- 定义按钮高度
FRAME_DELAY = 20        -- 定义帧间隔，单位为毫秒
SLIDE_DELAY = 150       -- 定义幻灯片切换的帧数间隔

isFirstImg = true   -- 当前图片是否是第一张图片
isLastImg = true    -- 当前图片是否是最后一张图片
isFullScreen = false    -- 当前窗口是否全屏显示
isStartSlide = false    -- 当前是否开启幻灯片播放

slideCounter = 0    -- 幻灯片播放计时器

function showInfo(width, height)    -- 定义无附加启动参数时的提示信息显示函数，参数分别为窗口宽度和高度
    QG.SetDrawColor(DRAW_COLOR.R, DRAW_COLOR.G, DRAW_COLOR.B, DRAW_COLOR.A) -- 设置绘图颜色
    QG.SetTextColor(TEXT_COLOR.R, TEXT_COLOR.G, TEXT_COLOR.B, TEXT_COLOR.A) -- 设置文字颜色
    QG.Clear()  -- 使用当前绘图颜色清空窗口
    if not font then
        font = QG.LoadFont(basePath.."res/SIMYOU.TTF", 100)
    end
    QG.DrawText(
        font,
        "请 使 用 Q Photo Viewer 打 开 图 片 文 件",
        width / 2 - width * 0.4 / 2,
        height / 2 - height * 0.035 / 2,
        width * 0.4,
        height * 0.035
    )
    QG.Update()
end

function showError(width, height)   -- 定义打开文件失败时的错误信息显示函数，参数分别为窗口宽度和高度
    QG.SetDrawColor(DRAW_COLOR.R, DRAW_COLOR.G, DRAW_COLOR.B, DRAW_COLOR.A) -- 设置绘图颜色
    QG.SetTextColor(TEXT_COLOR.R, TEXT_COLOR.G, TEXT_COLOR.B, TEXT_COLOR.A) -- 设置文字颜色
    QG.Clear()  -- 使用当前绘图颜色清空窗口
    if not font then
        font = QG.LoadFont(basePath.."res/SIMYOU.TTF", 100)
    end
    QG.DrawText(
        font,
        "打 开 图 片 失 败 ，不 支 持 的 格 式 或 文 件 已 损 坏",
        width / 2 - width * 0.5 / 2,
        height / 2 - height * 0.035 / 2,
        width * 0.5,
        height * 0.035
    )
    QG.Update()
end

function showImage(image, width, height)    -- 定义图片加载成功后的显示函数，参数分别为图片标识、窗口宽度和高度
    QG.SetDrawColor(DRAW_COLOR.R, DRAW_COLOR.G, DRAW_COLOR.B, DRAW_COLOR.A) -- 设置绘图颜色
    QG.Clear()  -- 使用当前绘图颜色清空窗口
    imgWidth, imgHeight = QG.GetImageSize(image)    -- 获取需要显示的图片的尺寸
    panelSize = {
        x = MARGIN_WIDTH,
        y = MARGIN_WIDTH,
        width = width - MARGIN_WIDTH * 2,
        height = height - MARGIN_WIDTH * 2
    }   -- 定义用于显示图片的面板尺寸
    showSize = {x = 0, y = 0, width = 0, height = 0}    -- 定义图片的实际显示尺寸
    widthScaleRatio = panelSize.width / imgWidth    -- 根据图片和窗口宽度计算可能的水平缩放比例
    heightScaleRatio = panelSize.height / imgHeight -- 根据图片和窗口高度计算可能的垂直缩放比例
    if widthScaleRatio < 1 or heightScaleRatio < 1 then -- 若水平或垂直缩放比小于1，则进一步计算实际的缩放比
        if widthScaleRatio < heightScaleRatio then  -- 实际缩放比取二者中的较小值
            realScaleRatio = widthScaleRatio
        else
            realScaleRatio = heightScaleRatio
        end
        showSize.width = imgWidth * realScaleRatio  -- 根据图片的实际缩放比计算出图片的实际显示宽度
        showSize.height = imgHeight * realScaleRatio    -- 根据图片的实际缩放比计算出图片的实际显示高度
    else
        showSize.width = imgWidth   -- 若不需要进行缩放，则图片的实际显示宽度即为图片宽度
        showSize.height = imgHeight -- 若不需要进行缩放，则图片的实际显示高度即为图片高度
    end
    showSize.x = MARGIN_WIDTH + panelSize.width / 2 - showSize.width / 2
    showSize.y = MARGIN_WIDTH + panelSize.height / 2 - showSize.height / 2
    QG.ShowImage(image, showSize.x, showSize.y, showSize.width, showSize.height)
    QG.Update()
end

function getFileIndex(fileName, fileList)   -- 定义在文件列表中获取指定文件索引的函数
    local index = 1
    for _, file in pairs(fileList) do
        if fileName == file then break end
        index = index + 1
    end
    return index
end

function changePage(width, height, type)    -- 定义切换图片函数，type为切页类型，1代表下一页，-1代表上一页
    index = index + type
    if index > #imgList then index = #imgList elseif index < 1 then index = 1 end    -- 控制当前图片的索引值不越界
    isFirstImg = index == 1
    isLastImg = index == #imgList
    QG.SetWindowTitle("Q Photo Viewer - "..imgList[index])   -- 切页后重新设置窗口标题
    QG.SetDrawColor(DRAW_COLOR.R, DRAW_COLOR.G, DRAW_COLOR.B, DRAW_COLOR.A) -- 设置绘图颜色
    QG.Clear()  -- 使用当前绘图颜色清空窗口
    QG.UnloadImage(image)   -- 释放当前已加载的图片所占用的资源
    image = QG.LoadImage(dirPath.."\\"..imgList[index])  -- 加载图片列表中当前索引所指定的图片
    if image == -1 then -- 若图片文件加载失败，则输出错误信息
        showError(width, height)
    else
        showImage(image, width, height)
        QG.Update()
    end
end

function redraw(width, height)  -- 定义重新绘制当前窗口内容的函数
    QG.SetDrawColor(DRAW_COLOR.R, DRAW_COLOR.G, DRAW_COLOR.B, DRAW_COLOR.A) -- 设置绘图颜色
    QG.Clear()  -- 使用当前绘图颜色清空窗口
    if not imgList then 
        showError(width, height)    -- 若imgList未定义，则首次打开图片失败，重绘内容为错误信息
    elseif _argc < 2 then
        showInfo(width, height)     -- 若程序启动参数小于两个，则并未打开其他文件，重绘内容为提示信息
    else
        showImage(image, width, height) -- 否则，重绘的内容为重绘前的图片
    end
    QG.Update()
end

QG.Init()
basePath = QG.GetBasePath() -- 获取当前程序运行目录
QG.CreateWindow("Q Photo Viewer", -1, -1, 1280, 720, "RM")  -- 创建窗口，设置窗口默认最大化并且大小可变
QG.SetWindowMinSize(MIN_SIZE.width, MIN_SIZE.height)   -- 设置窗口最小尺寸
width, height = QG.GetWindowSize()  -- 获取当前最大化的窗口的宽度和高度
img_pgDn = QG.LoadImage(basePath.."res/PgDn.png")   -- 下一页按钮图片
img_pgUp = QG.LoadImage(basePath.."res/PgUp.png")   -- 上一页按钮图片
if (_argc > 1) then     -- 若程序的启动参数大于1个，则是作为打开方式打开其他文件
    filePath = _argv[2]     -- 目标图片文件路径
    imgName = string.match(_argv[2], ".+\\([^\\]*%.%w+)$")    -- 目标图片文件名
    if not imgName then     -- 如果文件名不合法则输出错误信息
         showError(width, height)
    else
        dirPath = string.match(_argv[2], "(.+)\\[^\\]*%.%w+$")     -- 目标图片文件所在目录
        QG.SetWindowTitle("Q Photo Viewer - "..imgName)    -- 设置窗口标题后添加文件名
        image = QG.LoadImage(filePath)  -- 加载指定的图片文件
        if image == -1 then -- 若图片文件加载失败，则输出错误信息
            showError(width, height)
        else
            showImage(image, width, height) -- 若图片文件加载成功，则直接显示
            fileList = ET.GetFileList(dirPath)
            imgList = {}
            for _, fileName in pairs(fileList) do
                if (#fileName > 3 and (     -- 根据文件扩展名判断文件是否为图片文件
                    string.sub(fileName, #fileName - 3) == ".jpg" or
                    string.sub(fileName, #fileName - 3) == ".png" or
                    string.sub(fileName, #fileName - 3) == ".gif" or
                    string.sub(fileName, #fileName - 3) == ".bmp" or
                    string.sub(fileName, #fileName - 3) == ".ico" or
                    string.sub(fileName, #fileName - 3) == ".tif" or
                    string.sub(fileName, #fileName - 3) == ".tga"
                )) or (
                    #fileName > 4 and (
                    string.sub(fileName, #fileName - 4) == ".jpeg" or
                    string.sub(fileName, #fileName - 4) == ".jfif" or
                    string.sub(fileName, #fileName - 4) == ".webp"
                )) then
                    table.insert(imgList, fileName) -- 若扩展名为图片格式则将此文件添加到图片列表中
                end
            end
            if #imgList == 0 then table.insert(imgList, imgName) end    -- 如果无法在目录下获取到图片文件，则将已打开的图片文件加入到文件列表中
            index = getFileIndex(imgName, imgList)  -- 获取当前图片位于图片列表中的索引
            isFirstImg = index == 1         -- 根据索引判断当前图片是否为第一张图片
            isLastImg = index == #imgList   -- 根据索引判断当前图片是否为最后一张图片
        end
    end
else
    showInfo(width, height) -- 若不作为打开方式打开其他文件，则显示提示信息
end

PgUpBtnSize = {x = 0, y = 0, width = BUTTON_WIDTH, height = BUTTON_HEIGHT}  -- 定义上一页按钮显示尺寸
PgDnBtnSize = {x = 0, y = 0, width = BUTTON_WIDTH, height = BUTTON_HEIGHT}  -- 定义下一页按钮显示尺寸

while true do

    if isFullScreen and isStartSlide then    -- 如果窗口全屏并开启了幻灯片播放，则对计时器累加
        slideCounter = slideCounter + 1
        if slideCounter >= SLIDE_DELAY then -- 若计时器累加至指定时间间隔则尝试切换图片，并重置计时器
            slideCounter = 0
            changePage(width, height, 1)
        end
    else
        isStartSlide = false
        slideCounter = 0    -- 否则关闭幻灯片播放并重置计时器
    end

    if QG.UpdateEvent() == 0 then
        eventType = QG.GetEventType()
        if eventType == "QUIT" then QG.Quit() break -- 若检测到退出事件或Esc按键事件，退出QGame库并且跳出循环
        elseif eventType == "KEYDOWN_ESC" then  -- 若检测Esc按键事件，则退出全屏或退出程序
            if isFullScreen then    -- 若当前为全屏模式，则退出全屏，重新获取窗口尺寸并重绘窗口
                isFullScreen = false
                QG.SetWindowMode(0) 
                width, height = QG.GetWindowSize()
                redraw(width, height)
            else
                QG.Quit() 
                break
            end
        elseif eventType == "MOUSEMOTION" then  -- 若检测到鼠标移动事件，更新鼠标位置坐标
            x, y = QG.GetCursorPosition()
        elseif eventType == "MOUSEBUTTON_U_L" then  -- 若检测到鼠标左键抬起事件，判断是否点击到按钮上
            if x <= PgUpBtnSize.width then
                changePage(width, height, -1)   -- 若鼠标点击在"上一页"按钮位置则尝试显示上一页
            elseif x >= width - PgDnBtnSize.width then
                changePage(width, height, 1)    -- 若鼠标点击在"下一页"按钮位置则尝试显示下一页
            end
        elseif imgList and (eventType == "KEYDOWN_RIGHT" or eventType == "KEYDOWN_DOWN") then
            -- 将imgList是否定义加入判断条件，从而使当前事件只在图片正常显示的情况下被处理
            changePage(width, height, 1)
        elseif imgList and (eventType == "KEYDOWN_LEFT" or eventType == "KEYDOWN_UP") then
            -- 将imgList是否定义加入判断条件，从而使当前事件只在图片正常显示的情况下被处理
            changePage(width, height, -1)
        elseif eventType == "WINDOWRESIZE" then
            width, height = QG.GetWindowSize()  -- 若检测到窗口大小改变事件，则重新获取当前的窗口的宽度和高度
            redraw(width, height)   -- 重新绘制当前窗口内容
        elseif eventType == "MOUSESCROLL_U" or eventType == "MOUSESCROLL_D" then    -- 若检测到鼠标滚轮事件，则对图片进行缩放显示
            -- [[ 未完成功能，代码待补充 ]]
        elseif eventType == "KEYDOWN_F11" then
            isFullScreen = not isFullScreen     -- F11按下后反转当前是否全屏标志
            if isFullScreen then QG.SetWindowMode(2) else QG.SetWindowMode(0) end   -- 根据是否全屏标志设置窗口显示模式
            width, height = QG.GetWindowSize()  -- 重新获取当前的窗口的宽度和高度
            redraw(width, height)   -- 重新绘制当前窗口内容
        elseif eventType == "KEYDOWN_F5" then
            isStartSlide = true     -- F5按下后开始播放幻灯片
            isFullScreen = true
            QG.SetWindowMode(2)     -- 设置窗口全屏
            width, height = QG.GetWindowSize()  -- 重新获取当前的窗口的宽度和高度
            redraw(width, height)   -- 重新绘制当前窗口内容
        elseif imgList and eventType == "KEYDOWN_HOME" then -- 将imgList是否定义加入判断条件，从而使当前事件只在图片正常显示的情况下被处理
            index = 1   -- Home键按下后将当前图片索引重置到图片列表的第一张图片
            redraw(width, height)   -- 重新绘制当前窗口内容
        elseif imgList and eventType == "KEYDOWN_END" then  -- 将imgList是否定义加入判断条件，从而使当前事件只在图片正常显示的情况下被处理
            index = #imgList    -- End键按下后将当前图片索引重置到图片列表的最后一张图片
            redraw(width, height)   -- 重新绘制当前窗口内容
        end
    end

    if not x then x, y = QG.GetCursorPosition() end  -- 如果鼠标x坐标未定义则获取鼠标位置坐标
    PgUpBtnSize.y = height / 2 - PgUpBtnSize.height / 2     -- 根据当前窗口尺寸计算上一页按钮显示位置y坐标（x坐标始终位于窗口左上角，故不需要计算）
    PgDnBtnSize.x = width - PgDnBtnSize.width               -- 根据当前窗口尺寸计算下一页按钮显示位置x坐标
    PgDnBtnSize.y = height / 2 - PgDnBtnSize.height / 2     -- 根据当前窗口尺寸计算下一页按钮显示位置y坐标
    if x <= PgUpBtnSize.width and not isFirstImg then
        QG.ShowImage(img_pgUp, PgUpBtnSize.x, PgUpBtnSize.y, PgUpBtnSize.width, PgUpBtnSize.height)    -- 如果当前鼠标所在位置在"上一页"按钮位置则显示此按钮
    elseif x >= width - PgDnBtnSize.width and not isLastImg then
        QG.ShowImage(img_pgDn, PgDnBtnSize.x, PgDnBtnSize.y, PgDnBtnSize.width, PgDnBtnSize.height)    -- 如果当前鼠标所在位置在"下一页"按钮位置则显示此按钮
    else    -- 若鼠标不位于按钮位置，则使用填充矩形覆盖按钮位置，达到按钮消失的效果
        QG.SetDrawColor(DRAW_COLOR.R, DRAW_COLOR.G, DRAW_COLOR.B, DRAW_COLOR.A)
        QG.FillRectangle(PgUpBtnSize.x, PgUpBtnSize.y, PgUpBtnSize.width, PgUpBtnSize.height)
        QG.FillRectangle(PgDnBtnSize.x, PgDnBtnSize.y, PgDnBtnSize.width, PgDnBtnSize.height)
    end
    QG.Update()     -- 刷新渲染缓冲区内容

    QG.Sleep(FRAME_DELAY)   -- 延迟帧间隔
end

os.exit()
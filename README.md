# QGame

### *注意：本项目已停止维护，请使用 [EtherEngine](https://github.com/VoidmatrixHeathcliff/EtherEngine) 构建您所需要的项目*

[![](https://img.shields.io/github/stars/VoidmatrixHeathcliff/QGame.svg?style=flat&labelColor=3f48cc)](https://github.com/VoidmatrixHeathcliff/QGame/stargazers)  [![](https://img.shields.io/github/forks/VoidmatrixHeathcliff/QGame.svg?style=flat&labelColor=3f48cc)](https://github.com/VoidmatrixHeathcliff/QGame/network/members)  [![](https://img.shields.io/github/issues/VoidmatrixHeathcliff/QGame.svg?style=flat&labelColor=3f48cc)](https://github.com/VoidmatrixHeathcliff/QGame/issues)  ![](https://img.shields.io/github/license/VoidmatrixHeathcliff/QGame.svg?style=flat&label=license&message=notspecified&labelColor=3f48cc)

QGame意为Quick Game或Cute Game，是一个基于[SDL](http://www.libsdl.org/)及其附加库开发的轻量级跨平台Lua游戏库。

Qgame, which means *Quick game* or *Cute game*, is a [SDL]( http://www.libsdl.org/ ) and additional library based lightweight cross platform Lua game library.

若要阅读更多语言版本的README文档，请点击[此处](./.readme/README.md)。

For Multi Language README files，please click [here](./.readme/README.md) to read.

## QGame介绍

通过QGame，开发者可以使用简单的Lua脚本制作出效率和体积都十分出色的游戏程序。目前版本的QGame可以提供图像渲染、媒体播放控制，以及系统信息的获取和完善的交互事件处理等功能。

QGame的代码目前是一个独立的.cpp文件，您可以直接在编译器中编译它。

本项目不附带SDL的头文件，您需要自行在SDL的官网上[下载](http://www.libsdl.org/download-2.0.php)它们

## QGame文档

您可以根据您的使用需求，选择不同的文档。

此外要说明的是，不同语言的文档由不同团队分别完成，我们保证其函数介绍的内容是正确的，但模板和组织形式不一定完全对应。

### 面向使用者的学习指导

|            | 中文(zh) | English(en)  | 日本語(ja) |
| ---------- | -------- | ------------ | ---- |
| 入门手册   | [入门手册](./.manual/zh/入门手册.md) | [Guidebook](./.manual/en/Guidebook.md)    | [入門編](./.manual/ja/入門編.md) |
| 了解QGame  | 认识框架 | Introduction | 紹介 |
| 第一个程序 | 你好世界 | Helloworld   | Helloworld |

### 面向开发者的学习流程和API参考

|          | 中文(zh) | English(en)                            | 日本語(ja)               |
| -------- | -------- | --------- | -------- |
| 快速开始 | [快速开始](./.docs/zh/快速开始.md) | [Quickstart](./.docs/en/quickstart.md) | 開始                     |
| 基础功能 | [基础功能](./.docs/zh/Basic.md) | [Basic](./.docs/en/api/basic.md)                                  | 基本機能                 |
| 窗口操作 | [窗口操作](./.docs/zh/Window.md) | [Window](./.docs/en/api/window.md)                                 | ウインドウ　コントロール |
| 图形     | [图形](./.docs/zh/Graphic.md)     | [Graphic](./.docs/en/api/graphics.md)                                | グラフィックス           |
| 媒体     | [媒体](./.docs/zh/Media.md)     | [Media](./.docs/en/api/media.md)                                  | 媒体                     |
| 交互事件 | [交互事件](./.docs/zh/Action.md) | [Interactive](./.docs/en/api/interactive.md)                            | 対話                     |
| 其他     | [其他](./.docs/zh/Others.md)     | ~~Others~~                             | その他の機能             |

## QGame与开源社区

### 协议

QGame目前正处于开发阶段，具体选用何种协议尚待社区讨论。

### 交叉支持

QGame并非一款专精某一领域的游戏引擎，而是一个试图提供一套通用解决方法的通用游戏引擎。因此它理论上将可用于ACT、RPG、AVG等多种类型的游戏开发。具体类型由您二次开发的框架决定。
为了节省开发者的开发成本，本引擎的AVG部分除了允许使用本引擎的lua语言脚本控制外，还将引入对[UniGal-Script](https://github.com/Uni-Gal/UniGal-Script)的支持。UniGal是一个基于XML的通用的用于引擎间交换演出脚本核心数据的标准。对它的支持将在未来开发。

## TODO

完善文档


## 联系开发组

如果在使用过程中出现任何问题或有任何建议，请直接在本仓库中提交issue。

也欢迎您直接发送邮件至Voidmatrix@qq.com

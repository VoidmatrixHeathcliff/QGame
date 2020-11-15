# Window(s) and operations

## Overview  

* [Creation](#1)  
  * [CreateWindow](#11) : create a window
* [Message box](#2)  
  * [ShowMessageBox](#21) : show a message-box
* [window settings](#3)  
  * [window title](#31)
    * [Get](#311) : get the title of the window  
    * [Set](#312) : set the title of the window
  * [window position](#32)  
    * [Get](#321) : get the position of the window  
    * [Set](#322) : set the position of the window  
  * [window size](#33)  
    * [Get](#331) : get the size of the window  
    * [Set](#332) : set the size of the window  
    * [MaxLimit](#333)  
      * [GetWindowMaxSize](#3331) : get the maximum size of the window  
      * [SetWindowMaxSize](#3332) : set the maximum size of the window  
    * [MinLimit](#334)  
      * [GetWindowMinSize](#3331) : get the minimum size of the window  
      * [SetWindowMinSize](#3332) : set the minimum size of the window  
  * [window mode](#34)  
  * [resizability](#35)  
  * [opacity](#36)  

---

## <span id="1">Creation</span>  

* <span id="11">CreateWindow</span>  

    _`discription`_: Create a window and use this window as the context for graphics drawing and other operations.  

    _`API usage`_:  

    ```lua
    CreateWindow(title, x, y, width, height, flags)
    ```

    _`arguments`_:  
    |name|type|discription|note|  
    |:---:|:---:|:---:|:---:|  
    |title|string|the title of the window|Na|  
    |x|number|the x coordinate of the window position, a negative value means the default position|Na|  
    |y|number|the y coordinate of the window position, a negative value means the default position|Na|  
    |width|number|window width|Na|  
    |height|number|window height|Na|  
    |flags|string|The window attribute flag can be a string composed of the following values ->|"F" : Full screen (realized by changing the video mode); "D" : ~~Pseudo~~ full screen (this option does not change the video mode, it uses the current device resolution to display the window); "B" : Borderless; "R" : Resizeable; "M" : Maximum on creation; "N" : Minimum on creation;|  

    _`returns`_:  
    Returns nothing

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM") -- Create a window titled Hello World, maximize it and adjust its size, and display it in the default position. When using the "maximize" property to set the window, the set width and height will be ignored.
    QG.Sleep(5000)
    os.exit() -- exit after five secs
    ```

---

# [!] Not the final release.  
# Window(s) and operations

## Overview  

* [Creation](#1)  
  * [CreateWindow](#11) : create a window
* [Message box](#2)  
  * [ShowMessageBox](#21) : show a message-box
* [Window settings](#3)  
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
    |  name  |  type  |                                     discription                                      |                                                                                                                                            note                                                                                                                                            |
    | :----: | :----: | :----------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
    | title  | string |                               the title of the window                                |                                                                                                                                             Na                                                                                                                                             |
    |   x    | number | the x coordinate of the window position, a negative value means the default position |                                                                                                                                             Na                                                                                                                                             |
    |   y    | number | the y coordinate of the window position, a negative value means the default position |                                                                                                                                             Na                                                                                                                                             |
    | width  | number |                                     window width                                     |                                                                                                                                             Na                                                                                                                                             |
    | height | number |                                    window height                                     |                                                                                                                                             Na                                                                                                                                             |
    | flags  | string |    The window attribute flag can be a string composed of the following values ->     | "F" : Full screen (realized by changing the video mode); "D" : ~~Pseudo~~ full screen (this option does not change the video mode, it uses the current device resolution to display the window); "B" : Borderless; "R" : Resizeable; "M" : Maximum on creation; "N" : Minimum on creation; |

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

## <span id="2">Message box</span>  

* <span id="21">ShowMessageBox</span>  

    _`discription`_: Simply show a message box.  

    _`API usage`_:  

    ```lua
    ShowMessageBox(type, title, content)
    ```

    _`arguments`_:  
    |  name   |  type  |                           discription                            |                                                  note                                                   |
    | :-----: | :----: | :--------------------------------------------------------------: | :-----------------------------------------------------------------------------------------------------: |
    |  type   | string | the type of the window, could be one of the following values: -> | "ERROR" means show as error; "WARNING" means show as warning; "INFO"(default) means show as infomation. |
    |  title  | string |                     the title of the window                      |                                                   Na                                                    |
    | content | string |                    the content of the window                     |                                                   Na                                                    |


    _`returns`_:  
    Returns nothing

    _`Example`_:  

    ```lua
    QG = require("QGame")=QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
    QG.ShowMessageBox("ERROR", "Error!", "Program launch failed!")
    QG.Sleep(5000)
    QG.Quit()
    os.exit()
    ```

---

## <span id="3">Window settings</span>  

### <span id="31">title</span>    
  
* <span id="311">get (title)</span>  

    _`discription`_:  get the title of the window.

    _`API usage`_:  

    ```lua
    title = GetWindowTitle()
    ```

    _`arguments`_:  
    Pass nothing

    _`returns`_:  
    | name  |  type  |       discription       | note  |
    | :---: | :----: | :---------------------: | :---: |
    | title | string | the title of the window |  Na   |

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
    print(QG.GetWindowTitle())    -- print the window title
    QG.Pause()
    QG.Quit()
    os.exit()
    ```

    ---

* <span id="312">set (title)</span>  

    _`discription`_:  set the title of the window.

    _`API usage`_:  

    ```lua
    SetWindowTitle(title)
    ```

    _`arguments`_:  
    | name  |  type  |       discription       | note  |
    | :---: | :----: | :---------------------: | :---: |
    | title | string | the title of the window |  Na   |

    _`returns`_:  
    Returns nothing

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
    QG.Sleep(3000)  -- change the window title after 3 seconds
    QG.SetWindowTitle("This is new Title")
    QG.Sleep(5000)
    QG.Quit()
    os.exit()
    ```

---

### <span id="32">window position</span>    
  
* <span id="321">get (window position)</span>  

    _`discription`_:  get the x-y position of the window.  

    _`API usage`_:  

    ```lua
    x, y = GetWindowPosition()
    ```

    _`arguments`_:  
    Pass nothing

    _`returns`_:  
    | name  |  type  |            discription            | note  |
    | :---: | :----: | :-------------------------------: | :---: |
    |   x   | number | the x coordination of the window  |  Na   |
    |   y   | number | the y coordination of the w indow |  Na   |

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
    print(QG.GetWindowPosition())    -- print the position of the window
    QG.Pause()
    QG.Quit()
    os.exit()
    ````
    ---

* <span id="322">set (window position)</span>  

    _`discription`_:  set the x-y position of the window.  

    _`API usage`_:  

    ```lua
    SetWindowTitle(title)
    ```

    _`arguments`_:  
    | name  |  type  |    discription     | note  |
    | :---: | :----: | :----------------: | :---: |
    |   x   | number | the x coordination |  Na   |
    |   y   | number | the y coordination |  Na   |

    _`returns`_:  
    Returns nothing

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
    QG.Sleep(3000)  -- move the window to the left-up corner of the screen after 3 seconds.
    QG.SetWindowPosition(0, 0)
    QG.Sleep(5000)
    QG.Quit()
    os.exit()
    ```

---

### <span id="33">window size</span>    
  
* <span id="331">get (window size)</span>  

    _`discription`_:  get the x-y position of the window.  

    _`API usage`_:  

    ```lua
    x, y = GetWindowPosition()
    ```

    _`arguments`_:  
    Pass nothing

    _`returns`_:  
    | name  |  type  |            discription            | note  |
    | :---: | :----: | :-------------------------------: | :---: |
    |   x   | number | the x coordination of the window  |  Na   |
    |   y   | number | the y coordination of the w indow |  Na   |

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
    print(QG.GetWindowPosition())    -- print the position of the window
    QG.Pause()
    QG.Quit()
    os.exit()
    ```

    ---

* <span id="332">set (window size)</span>  

    _`discription`_:  set the x-y position of the window.  

    _`API usage`_:  

    ```lua
    SetWindowTitle(title)
    ```

    _`arguments`_:  
    | name  |  type  |    discription     | note  |
    | :---: | :----: | :----------------: | :---: |
    |   x   | number | the x coordination |  Na   |
    |   y   | number | the y coordination |  Na   |

    _`returns`_:  
    Returns nothing

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
    QG.Sleep(3000)  -- move the window to the left-up corner of the screen after 3 seconds.
    QG.SetWindowPosition(0, 0)
    QG.Sleep(5000)
    QG.Quit()
    os.exit()
    ```

#### <span id="333">Limit (of window size)</span>  

  ##### <span id="3331">maximum size (of window size)</span>  
  * Get:
  
    _`discription`_:  Get the maxinum size of the window.

    _`API usage`_:  

    ```lua
    width, height = GetWindowMaxSize()
    ```

    _`arguments`_:  
    Pass notrhing

    _`returns`_:  
    | name  |  type  |    discription     | note  |
    | :---: | :----: | :----------------: | :---: |
    |   width   | number | the maxinum width of the window |  Na   |
    |   height  | number | the maxinum height of the window |  Na   |

    _`Example`_:  

    ```lua
    QG = require("QGame")

    QG.Init()

    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
    QG.SetWindowMaxSize(1920, 1080) -- set the max window size to 1920x1080
    print(QG.GetWindowMaxSize())    -- print the max window size
    QG.Pause()

    QG.Quit()
    os.exit()
    ```

  ---

  * Set

  _`discription`_:  Set the maxinum size of the window.

    _`API usage`_:  

    ```lua
    SetWindowMaxSize(width, height)
    ```

    _`arguments`_:  
    | name  |  type  |    discription     | note  |
    | :---: | :----: | :----------------: | :---: |
    |   width   | number | the maxinum width of the window |  Na   |
    |   height  | number | the maxinum height of the window |  Na   |

    _`returns`_:  
    returns nothing

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
    QG.SetWindowMaxSize(1920, 1080) -- Set the maximum size to 1920x1080
    QG.Sleep(5000)
    QG.Quit()
    os.exit()
    ```

  ---

  ##### <span id="3332">minimum size (of window size)</span>  

  * Get

    _`discription`_:  Get the minimum size of the window.

    _`API usage`_:  

    ```lua
    width, height = GetWindowMinSize()
    ```

    _`arguments`_:  
    Pass notrhing

    _`returns`_:  
    | name  |  type  |    discription     | note  |
    | :---: | :----: | :----------------: | :---: |
    |   width   | number | the minimum width of the window |  Na   |
    |   height  | number | the minimum height of the window |  Na   |

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    QG.CreateWindow("Hello World", -1, -1, 1280, 720, "RM")
    QG.SetWindowMinSize(640, 360) -- set the minimum size to 1920x1080
    print(QG.GetWindowMinSize())    -- print out the minimums size
    QG.Pause()
    QG.Quit()
    os.exit()
    ```  

---

  * Set
    _`discription`_:  set the minimum size of window.  

    _`API usage`_:  

    ```lua
    SetWindowMinSize(width, height)
    ```

    _`arguments`_:  
    | name  |  type  |    discription     | note  |
    | :---: | :----: | :----------------: | :---: |
    |   width   | number | minimum width of the window |  Na   |
    |   height   | number | minimum height of the window |  Na   |

    _`returns`_:  
    Returns nothing

    _`Example`_:  

    ```lua
    QG = require("QGame")
    QG.Init()
    Window("Hello World", -1, -1, 1280, 720, "R")
    dowMinSize(640, 360) -- set the minimum size to 640x360
    5000)
    QG.Quit()
    os.exit()
    ```

---

### <span id="34">window mode</span>  

  _`discription`_:  apply different styles to the window  

  _`API usage`_:  

  ```lua
  SetWindowMode(mode)
  ```

  _`arguments`_:  
  | name  |  type  |           discription            | note  |
  | :---: | :----: |:-------------------------------: | :---: |
  |   mode   | number | style to be applied. Values can be ->  |  0: window mode ; 1: Full screen mode (with video mode changed) ; 2: Full screen mode (without video mode changed)   |

  _`returns`_:  
  returns nothing


  _`Example`_:  

  ```lua
  QG = require("QGame")
  QG.Init()
  QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
  QG.Sleep(3000)
  QG.SetWindowMode(1) -- Set the window to full screen mode
  QG.Sleep(5000)
  QG.Quit()
  os.exit()
  ```

---

### <span id="35">window resizeable</span>  

  _`discription`_:  apply resizeable attribute to the window    

  _`API usage`_:  

  ```lua
  SetWindowResizable(value)
  ```

  _`arguments`_:  
  | name  |  type  |           discription            | note  |
  | :---: | :----: |:-------------------------------: | :---: |
  |   value   | boolean | boolean flag  |  can be true or false   |

  _`returns`_:  
  returns nothing


  _`Example`_:  

  ```lua
  QG = require("QGame")
  QG.Init()
  QG.CreateWindow("Hello World", -1, -1, 1280, 720, "M")
  QG.SetWindowResizable(true) -- set window resizeable , same as -M when creating window.
  QG.Sleep(5000)
  QG.Quit()
  os.exit()
  ```

---

### <span id="36">window opacity</span>  

  _`discription`_:  apply resizeable attribute to the window    

  _`API usage`_:  

  ```lua
  SetWindowOpacity(value)
  ```

  _`arguments`_:  
  | name  |  type  |           discription            | note  |
  | :---: | :----: |:-------------------------------: | :---: |
  |   value   | number | the opacity of window  |  varies from 0.0 to 1.0   |

  _`returns`_:  
  returns nothing


  _`Example`_:  

  ```lua
  QG = require("QGame")
  QG.Init()
  QG.CreateWindow("Hello World", -1, -1, 1280, 720, "R")
  QG.SetWindowOpacity(0.5) -- set the window opacity to 0.5
  QG.Sleep(5000)
  QG.Quit()
  os.exit()
  ```

---
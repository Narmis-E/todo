# A Simple Todo TUI Written in C++

This program allows the creation, deletion and modification of todo items inside the terminal.

Note: Cannot be compiled as is, you must add a directory for todo items to be stored in first (full path).

![](https://github.com/Narmis-E/todo/blob/main/images/todo.png)

It displays current todo items, and also checks to see if there are none left:

![](https://github.com/Narmis-E/todo/blob/main/images/todo-nothing.png)


make sure to install the
```
ncurses-\
```
library. Everything else should be standard.

Also make sure to compile with the libraries linked:
```
g++ todo.cpp -o todo -lstdc++fs -lncurses
```


You can print todo items on startup by using the following script (add your item path):
```
#!/usr/bin/env zsh

todo=$(awk '{print}END{print "\n"}' PATH_TO_ITEMS*)

notify-send TODO: $todo
```

### Current Limitations:

$EDITOR is used for the editing function, so make sure to have it defined inside your current session!

As my c++ knowledge is fairly basic, the creation and deletion of items in done through parsing commands into the shell, however I might be able to improve it in some other way. 

Currently only one worded item names (of the actual file) can be used because of how the shell interprets strings.



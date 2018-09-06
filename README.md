# emtumble

![demo](https://raw.githubusercontent.com/wiki/OUDON/emtumble/images/demo.gif)

This software is an emulator of [Turing Tumble](https://www.turingtumble.com/) written in C++, and this is inspired by [jstumble](https://www.lodev.org/jstumble/), which is the simulator running on blowers.
Turing Tumble is a marble-powered mechanical computer.
By using this tool, you can play with Turing Tumble on your PC.
The key feature is that the board size is variable. So, you can construct more complicated circuits with this.


## Features
### Implemented
- [x] Basic simulation
- [x] Change a board size
- [x] Item pallet
- [x] Load a board from a text file
- [x] Export a board to an image file

### Planning 
- [ ] Save a board to a text file
- [ ] Select/Copy/Paste/Delete multiple objects 
- [ ] Use OpenGL to render faster


## Installation
### Mac OSX (10.13 or later)
Download the executable from [here](https://github.com/OUDON/emtumble/releases).

### Others

Build from the sources as:

``` sh
git clone git@github.com:OUDON/emtumble.git
qmake
make
```


## Requirements to Build
- Qt5


## Usage
``` sh
./bin/emtumble [--cli FILE_NAME]
```

If you want to use in GUI, then run the command `./bin/emtumble`.


## License
This software is released under the MIT License, see `LICENSE.txt`.

# emtumble

![demo](https://raw.githubusercontent.com/wiki/OUDON/emtumble/images/demo.gif)

This software is an emulator of [Turing Tumble](https://www.turingtumble.com/) written in C++.
Turing Tumble is a marble-powered mechanical computer.
By using this tool, you can play with Turing Tumble on your PC.
The key feature is that the board size is variable. So, you can construct more complicated circuits with this.

## Requirements
- Qt5

## Installation
``` sh
git clone git@github.com:OUDON/emtumble.git
qmake
make
```

## Usage
``` sh
./bin/emtumble [--cli FILE_NAME]
```

If you want to use in GUI, then run the command `./bin/emtumble`.

## License
This software is released under the MIT License, see `LICENSE.txt`.

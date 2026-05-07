# Intel8080 Emulator

## Installation

The project is written in C, and relies on raylib for sound and rendering. To build the emulator,
ensure you have the following:

#### Build Tool
  - gcc
  - Make (for Unix)

#### Required Libraries
  - raylib
  - X11 (for Unix)
  - Standard math library

### Building

1. Update and install necessary libraries
```
sudo apt-get update
sudo apt-get install build-essential pkg-config libraylib-dev libx11-dev
```
2. Clone the repo
```
git clone https://github.com/ezachle/intel8080-emulator.git
cd intel8080-emulator
```

3. make and run
```
make
./Intel8080 <path to ROM>
```

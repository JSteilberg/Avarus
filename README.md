# Avarus
Avarus is/will be a game written in C++, using mainly SFML and Box2D.

The aim is to create something along the lines of a space game, complete with planets, stars, orbits, and spacecraft. 

## Installation
Naturally, all these instructions begin with _cloning the repository_. `git clone https://github.com/JSteilberg/Avarus.git`.
### GNU/Linux
1. Run `sudo apt-get install libsfml-dev libbox2d-dev`
2. Unfortunately the libsfml-dev library may not be new enough for Avarus. Run `apt show libsfml-dev`, and if the version is less than 2.5 then you have to install by hand. To do so, follow the instructions on https://www.sfml-dev.org/tutorials/2.5/start-linux.php (option 3 most likely).
3. Install Lua JIT (or just Lua, but JIT should be better) http://luajit.org/install.html. Move the headers into `./lua_jit/`, and if necessary move the lib file (`libluajit.a`) into `./lib`.
4. Enter the repo, run `make`, and then run `./Avarus.out`

### Windows
Should be possible<sup>[citation needed]</sup>, I did it around February 2019.

You have to download and install SFML, Box2D, and Lua JIT by hand then add their includes/libs to the project for whatever IDE you're using.

Maybe the codeblocks project file I shipped will work as a boilerplate? You still need to add the SFML/Box2D include/lib search directories on your own though. 

Follow the instructions for https://www.sfml-dev.org/tutorials/2.5/start-cb.php and try to mirror for Box2D

### macOS
1. First, you need brew. Install it from https://brew.sh.
2. Now you need the OpenGL libraries somehow. You can either install them standalone or with Xcode (I haven't tried the Xcode method myself though)
    * Standalone method: Run `brew cask install xquartz` then `brew install freeglut`.
    * Xcode method: Just install Xcode https://developer.apple.com/download.
3. Now you need to build Box2D. Follow the instructions on https://www.iforce2d.net/b2dtut/setup-osx. Then move the internal `Box2D` folder (the one that has `Box2D.h` within it) into `Avarus/include`
4. Now you need to install SFML. If you're using Xcode, follow the full instructions on https://www.sfml-dev.org/tutorials/2.5/start-osx.php. Otherwise just do the 'Installing SFML' section. Then find the folder called `include` within the downloaded archive, and move the `SFML` folder within that folder into `Avarus/include`.
5. Install Lua JIT (or just Lua, but JIT should be better) http://luajit.org/install.html. Move the headers into `./lua_jit/`, and if necessary move the lib file (`libluajit.a`) into `./lib`.
6. Now you should be able to run `make` inside the `Avarus` folder. Then within that folder run `./Avarus.out`

## Inspiration
Inspiration taken (so far) from: 
* Terraria lmao

## Official dependencies
* SFML 2.5+
* Box2D 2.3+
* Lua JIT 2.0+
* OpenGL

## TODO: 
* ~~Add a debugging overlay~~
* Add an in-game console
* Figure out world data system

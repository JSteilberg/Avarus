# Avarus
Avarus is/will be a game written in C++, using mainly SFML and Box2D.

The aim is to create something along the lines of a space game, complete with planets, stars, orbits, and spacecraft. 

## Installation
### GNU/Linux
Run `sudo apt-get install libsfml-dev libboost-all-dev libbox2d-dev`

Then run `make`,
and then run `./Avarus`

### Windows
Should be possible<sup>[citation needed]</sup>, I did it around February 2019.
You have to download and install sfml and box2d by hand (I think boost should have a pleasant installer?) then add their includes/libs to whatever project file for whatever IDE you're using (maybe the codeblocks one I shipped will work as a boilerplate? You still need to add the sfml/box2d include/lib search directories on your own though)

### MacOS
Will look into adding support someday.

## Inspiration
Inspiration taken (so far) from: 
* Terraria lmao


## TODO: 
* ~~Add a debugging overlay~~
* Add an in-game console
* Figure out world data system

# 2dGameEngine

This engine is based on [Gustavo Pezzi's course](https://www.udemy.com/course/cpp-2d-game-engine/).

To run it all you have to do is download it. install SDL2 libraries, build it with `make` and run it with `make run`.

## HOW THIS ENGINE WORKS

First, one must understand that there's a difference between an engine and an editor. An editor is a graphic interface which allows you to tweak the game's engine. Very much like what you do with Unity, Unreal, Game Maker, etc (This engine doesn't have an editor!!!). An engine is everything behind that editor, all the code, building files and folder structure, following a specific architecture.

Knowing this, let's see what the engine implements:

- Sprite management.
- Component (modularity) structure.
- Scripting for level creation (using Lua).

**NOTES:**

- I was creating an editor for this, yet I decided to build a new version of the engine which can run on mobile devices. You check the project using [this link](https://github.com/santyarellano/CrossEngine).
- I also wrote a more detailed guide on how to get things running. It's in the project described in the line above.

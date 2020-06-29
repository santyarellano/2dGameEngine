#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class AssetManager;

class Editor {
	private:
		bool isRunning;
		SDL_Window* window;
	public:
		Editor();
		~Editor();
		void Destroy();
		void Initialize(int width, int height);
		void Update();
		void Render();
		void ProcessInput();
		bool IsRunning();
		static SDL_Renderer* renderer;
		static AssetManager* AssetManager;
		static SDL_Event event;
		int ticksLastFrame = 0;

};

#endif

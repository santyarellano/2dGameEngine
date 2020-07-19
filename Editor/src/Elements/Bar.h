#ifndef BAR_H
#define BAR_H

#include <SDL2/SDL.h>
#include "../Constants.h"
#include "../TextureManager.h"

class Bar{
	private:
		SDL_Texture* texture;
		int width;
		int height;
	
	public:
		SDL_RendererFlip sprFlip = SDL_FLIP_NONE;

		Bar() {
			this->width = WINDOW_WIDTH;
			this->height = WINDOW_HEIGHT;
		}

		void Update(float deltaTime) {

		}

		void Render() {
			SDL_Rect r;
			r.x = 0;
			r.y = height;
			r.w = width;
			r.h = height;

			SDL_SetRenderDrawColor(Editor::renderer, 0, 0, 255, 255);
			SDL_RenderFillRect(Editor::renderer, &r);
		}
};

#endif

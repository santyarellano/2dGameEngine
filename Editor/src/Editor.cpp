#include <iostream>
#include "./Editor.h"
#include "./Constants.h"

SDL_Renderer* Editor::renderer;
SDL_Event Editor::event;

Editor::Editor() {
	this->isRunning = false;
}

Editor::~Editor() {
}

void Editor::Initialize(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL" << std::endl;
		return;
	}
	if (TTF_Init() != 0) {
		std::cerr << "Error initializing SDL TTF" << std::endl;
		return;
	}
	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			0
		);
	if (!window) {
		std::cerr << "Error creating window" << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cerr << "Error creating SDL renderer" << std::endl;
		return;
	}

	isRunning = true;

	return;
}

bool Editor::IsRunning() {
	return this->isRunning;
}

void Editor::ProcessInput() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			// check keys
			auto key = event.key.keysym.sym;
			if (key == SDLK_ESCAPE) {
				isRunning = false;
			}
		}
		default: {
			break;
		}
	}
}

void Editor::Update() {
	// Wait until ms have ellapsed since last frame
	int timeToWait = FRAME_TARGET_TIME -(SDL_GetTicks() - ticksLastFrame);

	// Only call delay if we are too far to process this frame
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}

	// Delta time is the difference in ticks from the last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	// Clamp deltaTime to a maximum value
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	// Sets the new ticks for the current frame to be used in the next pass
	ticksLastFrame = SDL_GetTicks();
}

void Editor::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Editor::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

#include <iostream>
#include <string>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

Game::Game() {
	this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
	return this->isRunning;
}

void Game::Initialize(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL." << std::endl;
		return;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		std::cerr << "Error creating SDL window." << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1,0);
	if (!renderer) {
		std::cerr << "Error creating SDL renderer." << std::endl;
	}

	LoadLevel(0);

	isRunning = true;
	return;
}

void Game::LoadLevel(int levelNumber) {
	// Start including new assets to the asset manager list
	std::string textureFilePath = "./assets/images/tank-big-right.png";
	assetManager->AddTexture("tank-image", textureFilePath.c_str());

	// Create entities
	Entity& newEntity(manager.AddEntity("tank"));
	newEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	newEntity.AddComponent<SpriteComponent>("tank-image");

	// print all entities data
	manager.ListAllEntities();
}

void Game::ProcessInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
		default:
			break;
	}
}

void Game::Update() {
	// Sleep the execution until we reach the target frame in ms
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

	// Only call delay if we are too fast to process this frame
	if (timeToWait > 0 && timeToWait <= (int)FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}

	// Delta time is the difference in ticks from last fram converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame)/1000.0f;

	// Clamp delta time to a maximum value
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
	
	// Sets the new ticks for the current fram to be used in the next pass.
	ticksLastFrame = SDL_GetTicks();

	manager.Update(deltaTime);
}

void Game::Render() {
	// Set the background color
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);

	// Clear the back buffer
	SDL_RenderClear(renderer);

	// Draw all objects of the scene
	if (manager.HasNoEntities()) {
		return;
	}

	manager.Render();

	// Swap front and back buffers
	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

#include <iostream>
#include <string>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "../lib/glm/glm.hpp"
#include "./Map.h"
#include "./Components/ColliderComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

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

Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber) {
	// Start including new assets to the asset manager list
	assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
	assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
	assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());

	map = new Map("jungle-tiletexture", 2, 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

	// Create entities
	player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	player.AddComponent<KeyboardControlComponent>("up", "down","right", "left", "space");
	player.AddComponent<ColliderComponent>("player", 240, 106, 32, 32);

	Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
	tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");
	tankEntity.AddComponent<ColliderComponent>("enemy", 150, 495, 32, 32);

	Entity& radarEntity(manager.AddEntity("Radar", UI_LAYER));
	radarEntity.AddComponent<TransformComponent>(720,15,0,0,64,64,1);
	radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

	// print all entities data
	manager.ListAllEntities();
}

void Game::ProcessInput() {
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

	HandleCameraMovement();
	CheckCollisions();
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

void Game::HandleCameraMovement() {
	TransformComponent *mainPlayerTransform = player.GetComponent<TransformComponent>();

	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH/2);
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT/2);

	// Check boundaries (clamping)
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions() {
	std::string collisionTagType = manager.CheckEntityCollisions(player);
	if (collisionTagType.compare("enemy") == 0) {
		// TODO: Do something when collision is identified with an enemy
		isRunning = false;
	}
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

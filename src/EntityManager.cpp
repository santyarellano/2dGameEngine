#include <iostream>
#include <string>
#include <vector>
#include "./EntityManager.h"
#include "./Collision.h"
#include "./Components/ColliderComponent.h"

void EntityManager::ClearData() {
	for (auto& entity: entities) {
		entity->Destroy();
	}
}

bool EntityManager::HasNoEntities() {
	return entities.size() == 0;
}

void EntityManager::Update(float deltaTime) {
	/*for (auto& entity: entities) {
		entity->Update(deltaTime);
	}
	DestroyInactiveEntities();*/
	for (int i=0; i<(int)entities.size(); i++) {
		entities[i]->Update(deltaTime);
		if (!entities[i]->IsActive()) {
			entities.erase(entities.begin() + i);
		}
	}

}

void EntityManager::DestroyInactiveEntities() {
	for (int i=0; i<(int)entities.size(); i++) {
		if (!entities[i]->IsActive()) {
			entities.erase(entities.begin() + i);
		}
	}
}

void EntityManager::Render() {
	for (unsigned int layerNumer=0; layerNumer < NUM_LAYERS; layerNumer++) {
		for (auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumer))) {
			entity->Render();
		}
	}
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
	Entity *entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
	return entities;
}

unsigned int EntityManager::GetEntityCount() {
	return entities.size();
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
	std::vector<Entity*> selectedEntities;
	for (auto& entity: entities) {
		if (entity->layer == layer) {
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

void EntityManager::ListAllEntities() const {
	unsigned int i = 0;
	for (auto& entity: entities) {
		std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
		entity->ListAllComponents();
		i++;
	}

}

CollisionType EntityManager::CheckCollisions() {
	for (auto& thisEntity: entities) {
		if (thisEntity->HasComponent<ColliderComponent>()) {
			ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
			for (auto& thatEntity: entities) {
				if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>()) {
					ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
					if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider)) {
						if (
							thisCollider->colliderTag.compare("player") == 0 &&
							thatCollider->colliderTag.compare("enemy") == 0
						   ) {
							return PLAYER_ENEMY_COLLISION;
						}
						if (
							thisCollider->colliderTag.compare("player") == 0 &&
							thatCollider->colliderTag.compare("PROJECTILE") == 0
						   ) {
							return PLAYER_PROJECTILE_COLLISION; }
						if (
							thisCollider->colliderTag.compare("enemy") == 0 &&
							thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0
						   ) {
							return ENEMY_PROJECTILE_COLLISION;
						}
						if (
							thisCollider->colliderTag.compare("player") == 0 &&
							thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0
						   ) {
							return PLAYER_LEVEL_COMPLETE_COLLISION;
						}
					}
				}
			}
		}
	}
	return NO_COLLISION;
}

void EntityManager::setCollisionsVisibility(bool visibility) {
	for (auto& entity: entities) {
		if (entity->HasComponent<ColliderComponent>()) {
			entity->setCollisionVisibility(visibility);
		}
	}
}

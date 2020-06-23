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
	for (auto& entity: entities) {
		entity->Update(deltaTime);
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

std::string EntityManager::CheckEntityCollisions(Entity& myEntity) const {
	ColliderComponent* myCollider = myEntity.GetComponent<ColliderComponent>();
	for (auto& entity: entities) {
		if (entity->name.compare(myEntity.name) != 0 && entity->name.compare("Tile") != 0) {
			if (entity->HasComponent<ColliderComponent>()) {
				ColliderComponent* otherCollider = entity->GetComponent<ColliderComponent>();
				if (Collision::CheckRectangleCollision(myCollider->collider, otherCollider->collider)) {
					return otherCollider->colliderTag;
				}
			}
		}
	}
	return std::string();
}

void EntityManager::setCollisionsVisibility(bool visibility) {
	for (auto& entity: entities) {
		if (entity->HasComponent<ColliderComponent>()) {
			entity->setCollisionVisibility(visibility);
		}
	}
}

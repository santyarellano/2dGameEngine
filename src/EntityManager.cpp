#include "./EntityManager.h"
#include <iostream>
#include <vector>

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

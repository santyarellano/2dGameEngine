#include "./Entity.h"
#include <iostream>
#include <string>

Entity::Entity(EntityManager& manager): manager(manager) {
	this->isActive = true;
	collisionVisibility = false;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer): manager(manager), name(name), layer(layer) {
	this->isActive = true;
	collisionVisibility = false;
}

void Entity::Update(float deltaTime) {
	for (auto& component: components) {
		component->Update(deltaTime);
	}
}

void Entity::Render() {
	for (auto& component: components) {
		component->Render();
	}
}

void Entity::Destroy() {
	this->isActive = false;
}

bool Entity::IsActive() const {
	return this->isActive;
}

void Entity::ListAllComponents() const {
	for (auto mapElement: componentTypeMap) {
		std::cout << "	Component<" << mapElement.first->name() << ">" << std::endl;
	}
}

std::string Entity::ToString() {
	std::string s = "Entity Name: " + this->name + "\n";
	for (int i=0, size=this->components.size(); i<size; i++) {
		s += "	" + this->components[i]->typeName + "\n";
	}
	return s;
}

bool Entity::isCollisionVisible() const {
	return collisionVisibility;
}

void Entity::setCollisionVisibility(bool visibility) {
	collisionVisibility = visibility;
}

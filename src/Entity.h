#ifndef ENTITY_H
#define ENTITY_H

#include <typeinfo>
#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "./Constants.h"
#include "./EntityManager.h"
#include "./Component.h"

class Component;
class EntityManager;

class Entity {
	private:
		EntityManager& manager;
		bool isActive;
		bool collisionVisibility;
		std::vector<Component*> components;
		std::map<const std::type_info*, Component*> componentTypeMap;
	public:
		LayerType layer;
		std::string name;
		Entity(EntityManager& manager);
		Entity(EntityManager& manager, std::string name, LayerType layer);
		void Update(float deltaTime);
		void Render();
		void Destroy();
		bool IsActive() const;
		bool isCollisionVisible() const;
		void setCollisionVisibility(bool visibility);
		void ListAllComponents() const;
		std::string ToString();

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args) {
			T* newComponent(new T(std::forward<TArgs>(args)...));
			newComponent->owner = this;
			components.emplace_back(newComponent);
			componentTypeMap[&typeid(*newComponent)] = newComponent;
			newComponent->Initialize();
			return *newComponent;
		}
		
		template <typename T>
		T* GetComponent() {
			return static_cast<T*>(componentTypeMap[&typeid(T)]);
		}

		template <typename T>
		bool HasComponent() const {
			return componentTypeMap.count(&typeid(T));
		}
};

#endif

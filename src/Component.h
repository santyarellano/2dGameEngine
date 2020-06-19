#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Entity;

class Component {
	public:
		std::string typeName;
		Entity* owner;
		virtual ~Component() {}
		virtual void Initialize() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
};

#endif

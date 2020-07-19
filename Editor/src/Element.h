#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include "./ElementManager.h"
#include "./Constants.h"

class ElementManager;

class Element {
	private:
		ElementManager& manager;

	public:
		std::string name;

		Element(ElementManager& manager): manager(manager) {
		}

		void Update(float deltaTime) {
		}

		void Render() {
		}
};

#endif

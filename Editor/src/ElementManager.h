#ifndef ELEMENTMANAGER_H
#define ELEMENTMANAGER_H

#include <string>
#include <vector>
#include "./Element.h"

class ElementManager {
	private:
		std::vector<Element*> elements;
	
	public:
		void ClearData(){
		}

		void Update(float deltaTime) {
			for (auto& element: elements) {
				element->Update(deltaTime);
			}
		}

		void Render() {
			for (auto& element: elements) {
				element->Render();
			}
		}

		Element& AddElement() {
			Element* element = new Element(*this);
			elements.emplace_back(element);
			return *element;
		}
};

#endif

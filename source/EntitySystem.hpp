#pragma once

#include <vector>

namespace engine2d {
	namespace EntitySystem {
		std::vector<Entity*> entities;

		void init() {}

		void update() {
			for (int i = 0; i < entities.size(); i++) {
				entities.at(i)->update();
			}
		}

		void add(Entity* entity) {
			entities.push_back(entity);
		}

		void remove(Entity* entity) {
			for (int i = 0; i < entities.size(); i++) {
				if (entities.at(i) == entity) {
					entities.erase((entities.begin() + i));
				}
			}
		}
	}
}
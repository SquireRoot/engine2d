#pragma once

#include <vector>

namespace engine2d {
	namespace EntitySystem {
		std::vector<Entity*> entities;

		void update() {
			for (int i = 0; i < entities.size(); i++) {
				entities[i]->updateChildren();
				entities[i]->update();
			}
		}

		void add(Entity* entity) {
			entities.push_back(entity);
		}

		void remove(Entity* entity) {
			for (int i = 0; i < entities.size(); i++) {
				if (entities[i]->id == entity->id) {
					entities.erase((entities.begin() + i));
				}
			}
		}
	}
}
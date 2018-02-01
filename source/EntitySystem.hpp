#pragma once

#include <vector>

namespace engine2d {
	namespace EntitySystem {
		DLinkedList<Entity> entities;

		void update() {
			entities.setItBegin();
			Entity* entity = entities.current();
			while (entity != NULL) {
				entity->updateChildren();
				entity->update();
				entity = entities.next();
			}
		}

		void add(Entity* entity) {
			entities.add(entity);
		}

		void remove(GUID id) {
			entities.setItBegin();
			Entity* component = entities.current();
			while (component != NULL) {
				if (id == component->id) {
					delete component;
					entities.remove();
				}
				component = entities.next();
			}
		}
	}
}
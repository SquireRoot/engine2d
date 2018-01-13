#pragma once

#include <glm\glm.hpp>

#include <Windows.h>
#include <vector>

namespace engine2d {
	struct Entity {
		GUID id;

		Transform transformComponent = Transform(this);
		Transform localTransformComponent = Transform(this);

		GraphicsComponent* graphicsComponent;

		std::vector<Entity*> children;
		Entity* parent = nullptr;

		Entity() {
			CoCreateGuid(&id);
			EntitySystem::add(this);
		}

		Entity(Transform transform) {
			transformComponent = transform;
			transformComponent.attatchedEntity = this;
			CoCreateGuid(&id);
			EntitySystem::add(this);
		}

		void updateChildren() {
			for (int i = 0; i < children.size(); i++) {
				children[i]->transformComponent.position = (transformComponent.position + children[i]->localTransformComponent.position); 
			}
		}

		bool addChild(Entity* entity) {
			Entity* ent;
			while (entity != NULL) {
				if (id == entity->id) {
					return false;
				}
				
				ent = entity;
				entity = entity->parent;
			}

			children.push_back(ent);
			return true;
		}

		virtual void init() = 0;
		virtual void update() = 0;
	};
}
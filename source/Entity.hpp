#pragma once

#include <glm\glm.hpp>

#include <Windows.h>
#include <vector>

namespace engine2d {
	struct Entity {
		GUID id;

		Transform transformComponent = Transform(this);
		GraphicsComponent* graphicsComponent;

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

		virtual void init() = 0;
		virtual void update() = 0;
	};
}
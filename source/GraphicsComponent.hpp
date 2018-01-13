#pragma once

#include <cstring>
#include <glm\glm.hpp>
#include <GLEW\glew.h>

namespace engine2d {
	struct GraphicsComponent : Component {
		glm::mat4 modelMatrix;
		glm::mat4 modelViewProjection;

		Texture* texture;

		//some mesh object
		GraphicsComponent(Entity* entity,  Texture* tex) : Component(entity) {
			modelViewProjection = GraphicsSystem::Projection * GraphicsSystem::View * modelMatrix;
			texture = tex;
		}

		void update() {
			modelMatrix = attatchedEntity->transformComponent.getTransform();
			modelViewProjection = GraphicsSystem::Projection * GraphicsSystem::View * modelMatrix;
		}
	};
}
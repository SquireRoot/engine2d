#pragma once

#include <cstring>
#include <glm\glm.hpp>
#include <GLEW\glew.h>

namespace engine2d {
	struct GraphicsComponent : Component {
		static uint32 textureCount; // initialized to 0

		glm::mat4 modelMatrix;
		glm::mat4 modelViewProjection;

		GLuint vertexBuffer;
		GLuint uvBuffer;
		GLuint textureID;

		//some mesh object
		GraphicsComponent(Entity* entity, Sprite sprite) : Component(entity) {
			modelViewProjection = GraphicsSystem::Projection * GraphicsSystem::View * modelMatrix;

			// create vertex buffer
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(sprite.verticies), sprite.verticies, GL_STATIC_DRAW);

			// create uv buffer
			glGenBuffers(1, &uvBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(sprite.textureUVs), sprite.textureUVs, GL_STATIC_DRAW);

			// create texture
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sprite.width, sprite.height, 0, GL_BGR, GL_UNSIGNED_BYTE, sprite.imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			// TODO: switch active texture or have a sprite sheet for multiple textures
		}

		void update() {
			modelMatrix = attatchedEntity->transformComponent.getTransform();
			modelViewProjection = GraphicsSystem::Projection * GraphicsSystem::View * modelMatrix;
		}
	};

	uint32 GraphicsComponent::textureCount = 0;
}
#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace engine2d {
	struct Player : Entity {

		Player(Texture* tex) : Entity() {
			transformComponent.scale = glm::vec3(1.0f, 1.0f, 1.0f);
			graphicsComponent = GraphicsSystem::createComponent(this, tex);
		}

		Player(Texture* tex, Transform transform) : Entity(transform) {
			graphicsComponent = GraphicsSystem::createComponent(this, tex);
		}

		void init() {}

		void update() {
			if (GetAsyncKeyState(0x57)) { // w
				transformComponent.position += glm::vec3(0.0f, 0.025f, 0.0f);
			} if (GetAsyncKeyState(0x41)) {// a
				transformComponent.position += glm::vec3(-0.025f, 0.0f, 0.0f);
			} if (GetAsyncKeyState(0x53)) {// s
				transformComponent.position += glm::vec3(0.0f, -0.025f, 0.0f);
			} if (GetAsyncKeyState(0x44)) {// d
				transformComponent.position += glm::vec3(0.025f, 0.0f, 0.0f);
			}

			if (GetAsyncKeyState(VK_LEFT)) {
				transformComponent.scale += glm::vec3(-0.025f, 0.0f, 0.0f);
			} if (GetAsyncKeyState(VK_RIGHT)) {
				transformComponent.scale += glm::vec3(0.025f, 0.0f, 0.0f);
			} if (GetAsyncKeyState(VK_UP)) {
				transformComponent.scale += glm::vec3(0.0f, 0.025f, 0.0f);
			} if (GetAsyncKeyState(VK_DOWN)) {
				transformComponent.scale += glm::vec3(0.0f, -0.025f, 0.0f);
			}
		}
	};

	struct Player2 : Entity {
		Player2(Texture* tex) : Entity() {
			transformComponent.scale = glm::vec3(1.0f, 1.0f, 1.0f);
			graphicsComponent = GraphicsSystem::createComponent(this, tex);
		}

		Player2(Texture* tex, Transform transform) : Entity(transform) {
			graphicsComponent = GraphicsSystem::createComponent(this, tex);
		}

		void init() {}
		void update() {}
	};
}
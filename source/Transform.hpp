#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\transform.hpp>

namespace engine2d {
	struct Transform : Component {
		glm::quat rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

		Transform() : Component(NULL) {}

		Transform(Entity* entity) : Component(entity) {}

		Transform(Entity* entity, glm::vec3 posi, glm::vec3 scalei, glm::vec3 eulerroti) : Component(entity) {
			position = posi;
			scale = scalei;
		}

		Transform(Entity* entity, glm::vec3 posi, glm::vec3 scalei, glm::quat roti) : Component(entity) {
			position = posi;
			scale = scalei;
			rotation = roti;
		}

		glm::mat4 getTransform() {
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, position);
			transform = transform * glm::toMat4(rotation);
			transform = glm::scale(transform, scale);
			return transform;
		}

		glm::vec3 getEulerRotation() { return glm::eulerAngles(rotation); }
		void setEulerRotation(glm::vec3 eulerRotation) { rotation = glm::quat(eulerRotation); }
	};
}
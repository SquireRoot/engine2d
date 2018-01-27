#pragma once

#include <FoxLib\Log.hpp>
#include <FoxLib\Types.hpp>

#include <glm\glm.hpp>
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

namespace engine2d {
	enum GameState {
		INIT,
		LOOP,
		EXIT
	};

	GameState state;
	foxlib::Log log;


	// forward declarations
	struct Entity;
	struct GraphicsComponent;
	namespace EntitySystem {
		void add(Entity* entity);
	}
	namespace GraphicsSystem {
		glm::mat4 Projection;
		glm::mat4 View;
	}
	namespace Engine {
		GLFWwindow* window;
	}
}

// game includes, order is important
#include "Texture.hpp"
#include "Component.hpp"
#include "Transform.hpp"
#include "Entity.hpp"
#include "GraphicsComponent.hpp"

#include "EntitySystem.hpp"

#include "GraphicsSystem.hpp"
#include "InputSystem.hpp"

// add entities here
#include "Player.hpp"

#include "Engine.hpp"

namespace engine2d {
	void start() {
		state = GameState::INIT;
		log.init();
		log.write("Initializing\n");
		Engine::init();

		//begin textures
		//Texture* backgroundtex = GraphicsSystem::createTexture("res/spacepng.png", false);
		Texture* cat = GraphicsSystem::createTexture("res/fontsheet.png", false);
		// end textures

		// begin entities
		Player player = Player(cat);
		//player.transformComponent.position = glm::vec3(0.0f, 0.0f, 1.0f);

		//Payer2 background = Player2(backgroundtex);
		//child.transformComponent.scale = glm::vec3(10.0f, 10.0f, 1.0f);
		//child.transformComponent.position = glm::vec3(0.0f, 0.0f, 0.0f);
		// child.localTransformComponent.position = glm::vec3(5.0f, 0.0f, 0.0f);
		// player.addChild(&child);
		// end entities

		log.write("Starting main loop\n");
		state = GameState::LOOP;
		Engine::loop();
	}

	void exit(int status) {
		log.write("Log Closed\n");
		ExitProcess(status);
	}
}
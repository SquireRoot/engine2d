#pragma once

#include <Windows.h>

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#define SAMPLING 4 //antialiasing 
#define RES_X 1024
#define RES_Y 768

namespace engine2d {
	namespace Engine {
		extern GLFWwindow* window;
		
		float32 optimalDT = (1.0f / 60.0f) * 1000.0f; // multiply by 1000 to convert to miliseconds

		void init() {
			if (!glfwInit()) {
				log.write("GLFW: Initialization failed!\n");
				exit(-1);
			}

			glfwWindowHint(GLFW_SAMPLES, SAMPLING);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

			window = glfwCreateWindow(RES_X, RES_Y, "engine2d", NULL, NULL);

			if (window == NULL) {
				log.write("GLFW: Window Initialization failed!\n");
				glfwTerminate();
				exit(-1);
			}

			glfwMakeContextCurrent(window);

			if (glewInit() != GLEW_OK) {
				log.write("GLEW: Initialization failed!\n");
				exit(-1);
			}

			GraphicsSystem::init();
		}

		void loop() {
			const float64 starttime = GetTickCount64();
			float64 timei = 0;
			float64 time;
			float64 dtime;
	
			float64 accumulator = 0.0;

			float64 fps = 0;

			while (state == GameState::LOOP &&
				   !InputSystem::isKeyDown(VK_ESCAPE) &&
				   !glfwWindowShouldClose(window)) {

				time = GetTickCount64() - starttime;
				dtime = time - timei;
				accumulator += dtime;

				int framecount = 0;
				while (accumulator >= optimalDT) {
					// creation of a single frame happens every optimalDT milliseconds
					EntitySystem::update();
					GraphicsSystem::update();

					accumulator -= optimalDT;
					framecount++;
				}

				fps = framecount / ((GetTickCount64() - starttime) - time);
				timei = time;

				glfwPollEvents();
			}
		}
	};
}
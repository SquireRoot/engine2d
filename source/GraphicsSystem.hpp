#pragma once

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

//GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <list>
#include <string>
#include <fstream>
#include <algorithm> 

namespace engine2d {
	namespace GraphicsSystem {
		DLinkedList<GraphicsComponent> graphicsComponents;

		GLuint VertexArrayID;
		GLuint ShaderID;
		GLuint VertexBufferID;
		GLuint uvBufferID;

		extern glm::mat4 Projection;
		extern glm::mat4 View;

		GLuint compileShaders() {
			/* loading shaders */
			GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			// read vertex shader from file
			std::string VertexShaderCode;
			std::ifstream VertexShaderStream("res/shaders/VertexShader.shader", std::ios::in);
			if (VertexShaderStream.is_open()) {
				std::string Line = "";
				while (getline(VertexShaderStream, Line))
					VertexShaderCode += "\n" + Line;
				VertexShaderStream.close();
			} else {
				log.write("Failed to load Vertex Shader code!!\n");
				return 0;
			}

			// read fragment shader from file
			std::string FragmentShaderCode;
			std::ifstream FragmentShaderStream("res/shaders/FragmentShader.shader", std::ios::in);
			if (FragmentShaderStream.is_open()) {
				std::string Line = "";
				while (getline(FragmentShaderStream, Line))
					FragmentShaderCode += "\n" + Line;
				FragmentShaderStream.close();
			} else {
				log.write("Failed to load Fragment Shader code!!\n");
				exit(-1);
			}

			// compile vertex shader
			char const * VertexSourcePointer = VertexShaderCode.c_str();
			glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
			glCompileShader(VertexShaderID);

			// check vertex shader
			GLint Result = GL_FALSE;
			int numLogChars;
			glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
			glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &numLogChars);
			if (numLogChars > 1) {
				char* errormsg = new char[numLogChars];
				glGetShaderInfoLog(VertexShaderID, numLogChars, NULL, errormsg);
				log.write("begin vertex shader log\n");
				log.write(errormsg);
				log.write("end vertex shader log\n");
				delete[] errormsg;
			}

			// compile Fragment shader
			char const * FragmentSourcePointer = FragmentShaderCode.c_str();
			glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
			glCompileShader(FragmentShaderID);

			// check Fragment shader
			glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
			glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &numLogChars);
			if (numLogChars > 1) {
				char* errormsg = new char[numLogChars];
				glGetShaderInfoLog(FragmentShaderID, numLogChars, NULL, errormsg);
				log.write("begin fragment shader log\n");
				log.write(errormsg);
				log.write("end fragment shader log\n");
				delete[] errormsg;
			}

			// link the shaders
			GLuint ProgramID = glCreateProgram();
			glAttachShader(ProgramID, VertexShaderID);
			glAttachShader(ProgramID, FragmentShaderID);
			glLinkProgram(ProgramID);

			// check linking
			glGetShaderiv(ProgramID, GL_LINK_STATUS, &Result);
			glGetShaderiv(ProgramID, GL_INFO_LOG_LENGTH, &numLogChars);
			if (numLogChars > 1) {
				char* errormsg = new char[numLogChars];
				glGetProgramInfoLog(FragmentShaderID, numLogChars, NULL, errormsg);
				log.write("begin shader linker log\n");
				log.write(errormsg);
				log.write("end shader linker log\n");
				delete[] errormsg;
			}

			glDetachShader(ProgramID, VertexShaderID);
			glDetachShader(ProgramID, FragmentShaderID);

			glDeleteShader(VertexShaderID);
			glDeleteShader(FragmentShaderID);

			return ProgramID;
		}

		void init() {
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glDisable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

			glGenVertexArrays(1, &VertexArrayID);
			glBindVertexArray(VertexArrayID);

			ShaderID = compileShaders();

			Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 10.0f, -10.0f);
			View = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			// load the vertex buffer
			const GLfloat verticies[18] = {
				// triangle 1: top left
				-1.0f, -1.0f, 0.0f,
				-1.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 0.0f,
				// triangle 2: bottom right
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				1.0f, 1.0f, 0.0f
			};

			glGenBuffers(1, &VertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

			// load the UV buffer
			const GLfloat uvs[12] = {
				// triangle 1: top left
				0.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 1.0f,
				// triangle 2: bottom right
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f
			};

			glGenBuffers(1, &uvBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
		}

		void update() {
			//TODO: sort graphics components (insertion sort)

			// clear and start rendering
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(ShaderID);

			GLuint mvpMatrixID = glGetUniformLocation(ShaderID, "MVP");
			GLuint SamplerID = glGetUniformLocation(ShaderID, "sampler");

			graphicsComponents.setItBegin();
			GraphicsComponent* component = graphicsComponents.current();
			while (component != NULL) {
				component->update();

				glm::mat4 mvp = component->modelViewProjection;
				glUniformMatrix4fv(mvpMatrixID, 1, GL_FALSE, &mvp[0][0]);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, component->texture->TextureID);
				glUniform1i(SamplerID, 0);

				// verts
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

				// uvs
				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

				glDrawArrays(GL_TRIANGLES, 0, 6);
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);

				component = graphicsComponents.next();
			}
			glfwSwapBuffers(Engine::window);
		}

		GraphicsComponent* createComponent(Entity* entity, Texture* texture) {
			GraphicsComponent* component = new GraphicsComponent(entity, texture);
			graphicsComponents.add(component);
			return component;
		}

		void destroyComponent(GUID id) {
			graphicsComponents.setItBegin();
			GraphicsComponent* component = graphicsComponents.current();
			while (component != NULL) {
				if (id == component->id) {
					delete component;
					graphicsComponents.remove();
				}
				component = graphicsComponents.next();
			} 
		}
	}
}
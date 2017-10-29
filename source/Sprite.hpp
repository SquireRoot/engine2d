#pragma once

#include "glm\glm.hpp"
#include <fstream>

namespace engine2d {
	struct Sprite {
		glm::vec3 normal = glm::vec3(0,0,1);

		GLfloat verticies[18] = {
			// triangle 1: top left
			-1.0f, -1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			// triangle 2: bottom right
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			1.0f, 1.0f, 0.0f
		};

		GLfloat textureUVs[12];

		uint32 width;
		uint32 height;
		uint32 imagesize;

		char* imageData;

		Sprite(const char* filepath) {
			std::ifstream bmpfile;
			bmpfile.open(filepath, std::ios::in | std::ios::binary);
			if (!bmpfile.good()) { 
				log.write(filepath); 
				log.write(" could not be opened!\n");
				exit(1);
			}

			char header[54]; // bmp file has 54 byte header
			bmpfile.read(header, 54);
			if (header[0] != 'B' || header[1] != 'M') {
				log.write(filepath);
				log.write(" has bad header!\n");
				exit(1);
			}

			uint32 datapos;
			datapos = *((int *)&header[0x0A]);
			imagesize = *((int *)&header[0x22]);
			width = *((int *)&header[0x12]);
			height = *((int *)&header[0x16]);
			if (datapos == 0) datapos = 54;
			if (imagesize == 0) imagesize = width * height * 3;

			imageData = new char[imagesize];
			bmpfile.read(imageData, imagesize);
			bmpfile.close();
			
			// triangle 1: top left
			textureUVs[0] = 0.0f; textureUVs[1] = 0.0f; //vert 1
			textureUVs[2] = 0.0f; textureUVs[3] = 1.0f; //vert 2
			textureUVs[4] = 1.0f; textureUVs[5] = 1.0f; //vert 3
			//triangle 2: top right
			textureUVs[6] = 0.0f; textureUVs[7] = 0.0f; //vert 1
			textureUVs[8] = 1.0f; textureUVs[9] = 0.0f; //vert 2
			textureUVs[10] = 1.0f; textureUVs[11] = 1.0f; //vert 3
		}
	};
}
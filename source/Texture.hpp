#include <fstream>

namespace engine2d {
	struct Texture {
		GLfloat uv[12];

		uint32 width;
		uint32 height;
		uint32 imageSize;

		GLuint TextureID;
		
		Texture(const char* filepath) {
			if (state == GameState::INIT) {
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
				imageSize = *((int*)&header[0x22]);
				width = *((int *)&header[0x12]);
				height = *((int *)&header[0x16]);
				if (datapos == 0) datapos = 54;

				char* imageData = new char[imageSize];
				bmpfile.read(imageData, imageSize);

				if (bmpfile.eof()) {
					log.write("Error: eof bit set on ");
					log.write(filepath);
					log.write("\n");
				}

				if (bmpfile.fail()) {
					log.write("Error: fail bit set on ");
					log.write(filepath);
					log.write("\n");
				}

				if (bmpfile.bad()) {
					log.write("Error: bad bit set on ");
					log.write(filepath);
					log.write("\n");
				}

				bmpfile.close();

				// load textures into a buffer
				glGenTextures(1, &TextureID);
				glBindTexture(GL_TEXTURE_2D, TextureID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);

				delete[] imageData;

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glGenerateMipmap(GL_TEXTURE_2D);

				glBindTexture(GL_TEXTURE_2D, 0);

			} else {
				log.write("Error: Cannot load texture ");
				log.write(filepath);
				log.write(" after initialization!\n");
			}
		}
	};
}
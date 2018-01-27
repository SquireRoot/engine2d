#include <fstream>

// cimg stuff
#define cimg_display 0
#define cimg_use_png 1
#include "CImg\CImg.h"

namespace engine2d {
	struct Texture {
		uint32 width;
		uint32 height;
		uint32 imageSize;

		GLuint TextureID;
		
		Texture(const char* filepath, bool isTransparent) {
			if (state == GameState::INIT) {
				cimg_library::CImg<unsigned char> pngImage = cimg_library::CImg<char>(filepath);
				unsigned char* imageData = new unsigned char[pngImage.width()*pngImage.height()*3];

				if (isTransparent) {
					for (int y = 0; y < pngImage.height(); y++) {
						for (int x = 0; x < pngImage.width(); x++) {
							uint32 pixelIndex = y*pngImage.width() + x;
							imageData[pixelIndex] = pngImage(x, y, 0);
							imageData[pixelIndex + 1] = pngImage(x, y, 1);
							imageData[pixelIndex + 2] = pngImage(x, y, 2);
							//imageData[pixelIndex + 3] = pngImage(x, y, 3);
						}
					}
				} else {
					for (int y = 0; y < pngImage.height(); y++) {
						for (int x = 0; x < pngImage.width(); x++) {
							uint32 pixelIndex = y*pngImage.width() + x;
							imageData[pixelIndex] = pngImage(x, y, 0);
							imageData[pixelIndex + 1] = pngImage(x, y, 1);
							imageData[pixelIndex + 2] = pngImage(x, y, 2);
							//imageData[pixelIndex + 3] = 255;
						}
					}
				}

				width = pngImage.width();
				height = pngImage.height();
				imageSize = width * height * 3;

				// load textures into a buffer
				glGenTextures(1, &TextureID);
				glBindTexture(GL_TEXTURE_2D, TextureID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pngImage.data());

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
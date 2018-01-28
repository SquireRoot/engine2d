#include <fstream>

// cimg stuff
#define cimg_display 0
#define cimg_use_png 1
#include "CImg\CImg.h"

namespace engine2d {
	struct Texture {
		uint32 width;
		uint32 height;
		uint32 spectrum;
		uint32 imageSize;

		GLuint TextureID;
		
		Texture(const char* filepath) {
			if (state == GameState::INIT) {
				cimg_library::CImg<unsigned char> pngImage = cimg_library::CImg<char>(filepath);

				width = pngImage.width();
				height = pngImage.height();
				spectrum = pngImage.spectrum();
				imageSize = width * height * spectrum;

				// convert image from planar to interleived RGBA format
				unsigned char* imageData = new unsigned char[width*height*4];
				if (spectrum == 3) {
					for (int y = 0; y < height; y++) {
						for (int x = 0; x < width; x++) {
							uint32 pixelIndex =  4 * (y*width + x);
							imageData[pixelIndex] = pngImage(x, height - y, 0);
							imageData[pixelIndex + 1] = pngImage(x, height - y, 1);
							imageData[pixelIndex + 2] = pngImage(x, height - y, 2);
							imageData[pixelIndex + 3] = 255;
						}
					}
				} else if (spectrum == 4) {
					for (int y = 0; y < height; y++) {
						for (int x = 0; x < width; x++) {
							uint32 pixelIndex = 4 * (y*width + x);
							imageData[pixelIndex] = pngImage(x, height - y, 0);
							imageData[pixelIndex + 1] = pngImage(x, height - y, 1);
							imageData[pixelIndex + 2] = pngImage(x, height - y, 2);
							imageData[pixelIndex + 3] = pngImage(x, height - y, 3);
						}
					}
				}

				// load textures into a buffer
				glGenTextures(1, &TextureID);
				glBindTexture(GL_TEXTURE_2D, TextureID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

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
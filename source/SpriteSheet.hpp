#pragma once

#include <vector>

namespace engine2d {
	struct SpriteSheet {
		std::vector<Sprite> sprites;

		SpriteSheet(char* filename, uint16 xstep, uint16 ystep) {}
	};
}
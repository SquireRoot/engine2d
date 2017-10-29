#pragma once

#include <Windows.h>
#include <list>

namespace engine2d {
	namespace InputSystem {
		std::list<int> keybuffer;

		void update() {}

		short isKeyDown(int key) {
			return GetAsyncKeyState(key);
		}
	}
}
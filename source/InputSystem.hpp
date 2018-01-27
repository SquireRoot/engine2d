#pragma once

#include <Windows.h>
#include <list>

namespace engine2d {
	namespace InputSystem {
		short isKeyDown(int key) {
			return GetAsyncKeyState(key);
		}
	}
}
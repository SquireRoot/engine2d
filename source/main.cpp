#include <Windows.h>

#include "Game.hpp"

int32 __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	engine2d::start();
	engine2d::exit(0);
}
/*Logs data to log.txt.*/
#pragma once
#ifdef _WIN32
#	include "windows/Log.hpp"
#else
#	error Unsupported platform for log.hpp
#endif

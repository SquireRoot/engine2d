cmake_minimum_required(VERSION 3.8)

project(engine2d)

#Make sure we can include everything in project directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty")

link_directories("${CMAKE_CURRENT_SOURCE_DIR}")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty")

#Find all source, header, and shader files to add to build 
file(GLOB_RECURSE allCodeFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.hpp" "*.cpp")

#Compile them to an executable
if(WIN32)
  add_executable(engine2d WIN32 ${allCodeFiles})
  target_compile_definitions(engine2d
	PRIVATE engine2dPlatWin)
  target_link_libraries(engine2d OpenGL32)
  #Warning level 4
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  set_target_properties(engine2d PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
elseif(UNIX)
  add_executable(engine2d ${allCodeFiles})
  if(NOT APPLE)
	target_compile_definitions(engine2d
	  PRIVATE engine2dPlatLinux)
	target_link_libraries(engine2d gl)
  endif(NOT APPLE)
endif()

#Fix Visual studio source groups to correspond to the folder they're in
foreach(src ${allCodeFiles})
  get_filename_component(dir ${src} DIRECTORY)
  if(dir)
	string(REPLACE "/" "\\" fixedDir ${dir})
	source_group(${fixedDir} FILES ${src})
  else()
	source_group("\\\\" FILES ${src})
  endif()
endforeach()

#Load libraries (must come after add_executable)
target_link_libraries(engine2d glew32)
target_link_libraries(engine2d glew32s)
target_link_libraries(engine2d glfw3)
target_link_libraries(engine2d glfw3dll)

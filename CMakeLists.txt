cmake_minimum_required(VERSION 3.8)

project(engine2d)
add_subdirectory("source")

#Copy appropriate files to build directory
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew32.dll" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glfw3.dll" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/opengl32.dll" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res" DESTINATION "${CMAKE_BINARY_DIR}")
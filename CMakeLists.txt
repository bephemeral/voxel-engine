cmake_minimum_required(VERSION 3.15)
project(voxel-engine LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(engine src/main.cpp src/shader.cpp src/camera.cpp src/window.cpp src/chunk.cpp external/glad/src/glad.c)

target_include_directories(engine PUBLIC external/glad/include)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(engine PRIVATE glfw OpenGL::GL glm::glm)

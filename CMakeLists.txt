cmake_minimum_required(VERSION 3.15)
project(voxel-engine LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB IMGUI_SRC
    external/imgui/*.cpp
)

set(IMGUI_BACKENDS
    external/imgui/backends/imgui_impl_opengl3.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
)

add_executable(engine 
    src/main.cpp 
    src/shader.cpp 
    src/camera.cpp 
    src/window.cpp 
    src/chunk.cpp 
    external/glad/src/glad.c
    ${IMGUI_SRC}
    ${IMGUI_BACKENDS}
)

# Include directories
target_include_directories(engine PUBLIC 
    external/glad/include 
    external/imgui 
    external/imgui/backends
    external/noise
)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(engine PRIVATE glfw OpenGL::GL glm::glm)

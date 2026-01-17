#pragma once
#include <GLFW/glfw3.h>

inline constexpr unsigned int SCR_WIDTH{800};
inline constexpr unsigned int SCR_HEIGHT{600};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);
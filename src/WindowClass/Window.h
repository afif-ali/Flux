#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{
private:
    inline static unsigned int width = 0;
    inline static unsigned int height = 0;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    inline static GLFWwindow* ID = nullptr;
    Window(unsigned int width, unsigned int height, const char* title);

    static bool isOpen();
    static unsigned int getWidth();
    static unsigned int getHeight();
};
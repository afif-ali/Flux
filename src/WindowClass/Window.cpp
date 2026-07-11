#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const char* title)
{
    Window::width = width;
    Window::height = height;

    ID = glfwCreateWindow(width, height, title, NULL, NULL);
    if (ID == nullptr)
    {
        std::cout << "ERROR: Failed to create GLFW window" << std::endl;
    }
    glfwMakeContextCurrent(ID);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to initialize GLAD" << std::endl;
    }
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(ID, framebuffer_size_callback);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window::width = width;
    Window::height = height;
}  

bool Window::isOpen()
{
    return !glfwWindowShouldClose(ID);
}

unsigned int Window::getWidth()
{
    return width;
}

unsigned int Window::getHeight()
{
    return height;
}

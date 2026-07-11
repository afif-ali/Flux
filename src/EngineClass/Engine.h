#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "WindowClass/Window.h"
#include "ShaderClass/Shader.h"

#include "particle.comp.hpp"
#include "particle.vert.hpp"
#include "particle.frag.hpp"


class Engine
{
public:
    inline static std::unique_ptr<Window> window = nullptr;

    inline static float fps = 0;

    static void Initialize(unsigned int width, unsigned int height, const char* title);
    static void Run();
    static void InitGUI();
    static void Begin();
    static void Update(float deltaTime);
    static void PhysicsUpdate(float deltaTime);
    static void UpdateGUI(float deltaTime);
    static void Render();
    static void ShutDownGUI();
    static void Shutdown();
};
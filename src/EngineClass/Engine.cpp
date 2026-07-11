#include "Engine.h"

void Engine::Initialize(unsigned int width, unsigned int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = std::make_unique<Window>(width, height, title);
}

void Engine::Run()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Engine::InitGUI();
    Engine::Begin();

    float lastFrame = glfwGetTime();
    float deltaTime = 0.0f;
    
    float fpsTimer = 0.0f;
    int frameCount = 0;
    
    const float fixedDeltaTime = 1.0f / 120.0f;
    float accumulator = 0.0f;

    while(window->isOpen())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        accumulator += deltaTime;

        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 0.25f)
        {
            fps = frameCount / fpsTimer;

            frameCount = 0;
            fpsTimer = 0.0f;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        Engine::Update(deltaTime);

        while (accumulator >= fixedDeltaTime)
        {
            Engine::PhysicsUpdate(fixedDeltaTime);
            accumulator -= fixedDeltaTime;
        }

        Engine::Render();
        Engine::UpdateGUI(deltaTime);

        glfwSwapBuffers(window->ID);
        glfwPollEvents();
    }

    
}

void Engine::InitGUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->ID, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void Engine::ShutDownGUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Engine::Shutdown()
{
    Engine::ShutDownGUI();
    glfwTerminate();
}
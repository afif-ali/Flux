#include "EngineClass/Engine.h"



float particleRadius = 32.0;


struct Particle
{
    glm::vec2 position;
    glm::vec2 velocity;
};
std::vector<Particle> particles;
unsigned int particleSSBO;

std::unique_ptr<Shader> particleCompute = nullptr;
std::unique_ptr<Shader> shader = nullptr;

unsigned int VAO;


void Engine::Begin()
{
    glEnable(GL_PROGRAM_POINT_SIZE);

    particleCompute = std::make_unique<Shader>(std::initializer_list<ShaderStage>{
        {GL_COMPUTE_SHADER, PARTICLE_COMP}
    });

    shader = std::make_unique<Shader>(std::initializer_list<ShaderStage>{
        {GL_VERTEX_SHADER, PARTICLE_VERT},
        {GL_FRAGMENT_SHADER, PARTICLE_FRAG}
    });


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    for (int i = 0; i < 1; i++)
    {
        particles.push_back({glm::vec2(400.0f, 300.0f), glm::vec2(0.0f, 0.0f)});
    }

    glGenBuffers(1, &particleSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleSSBO);
}

void Engine::Update(float deltaTime)
{
}

void Engine::PhysicsUpdate(float deltaTime)
{
    particleCompute->Bind();
    particleCompute->SetFloat("deltaTime", deltaTime);
    particleCompute->SetVec2("boundSize", glm::vec2(window->getWidth(), window->getHeight()));
    particleCompute->SetFloat("particleRadius", particleRadius);

    glDispatchCompute((particles.size() + 255) / 256, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void Engine::Render()
{
    shader->Bind();
    shader->SetVec2("screenSize", glm::vec2(window->getWidth(), window->getHeight()));
    shader->SetFloat("particleRadius", particleRadius);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, particles.size());
}

void Engine::UpdateGUI(float deltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Debug");

    ImGui::Text("FPS: %.1f", fps);
    ImGui::Text("Frame Time: %.3f ms", deltaTime * 1000.0f);
    ImGui::Text("Particles: %d", particles.size());

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
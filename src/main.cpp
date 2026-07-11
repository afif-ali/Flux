#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "particle.comp.hpp"
#include "particle.vert.hpp"
#include "particle.frag.hpp"


struct Particle
{
    glm::vec2 position;
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Flux", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_PROGRAM_POINT_SIZE);



    unsigned int compute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute, 1, &PARTICLE_COMP, NULL);
    glCompileShader(compute);
    int  success;
    char infoLog[512];
    glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(compute, 512, NULL, infoLog);
        std::cout << "ERROR: FAILED TO COMPILE COMPUTE SHADER: \n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SUCCESS: COMPILED COMPUTE SHADER" << std::endl;
    }
    unsigned int computeProg = glCreateProgram();
    glAttachShader(computeProg, compute);
    glLinkProgram(computeProg);
    glGetProgramiv(computeProg, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(computeProg, 512, NULL, infoLog);
        std::cout << "ERROR: FAILED TO LINK COMPUTE SHADER PROGRAM: \n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SUCCESS: LINKED COMPUTE SHADER PROGRAM" << std::endl;
    }

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &PARTICLE_VERT, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR: FAILED TO COMPILE VERTEX SHADER: \n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SUCCESS: COMPILED VERTEX SHADER" << std::endl;
    }
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &PARTICLE_FRAG, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR: FAILED TO COMPILE FRAGMENT SHADER: \n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SUCCESS: COMPILED FRAGMENT SHADER" << std::endl;
    }
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: FAILED TO LINK SHADER PROGRAM: \n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SUCCESS: LINKED SHADER PROGRAM" << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);





    std::vector<Particle> particles;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> RandomFloat(-1.0f, 1.0f);

    for (int i = 0; i < 1000; i++)
    {
        particles.push_back({
            glm::vec2(
                RandomFloat(gen),
                RandomFloat(gen)
            )
        });
    }

    unsigned int particleSSBO;
    glGenBuffers(1, &particleSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleSSBO);





    

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(computeProg);
        glDispatchCompute((particles.size() + 255)/256, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, particles.size());


        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
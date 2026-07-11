#include "Shader.h"



int Shader::GetUniformLocation(const char* name)
{
    auto it = uniformLocationCache.find(name);
    if (it!= uniformLocationCache.end())
        return it->second;
    
    int location = glGetUniformLocation(ID, name);
    uniformLocationCache[name] = location;

    return location;
}

Shader::Shader(std::initializer_list<ShaderStage> stages)
{
    int  success;
    char infoLog[512];

    
    ID = glCreateProgram();

    std::vector<GLuint> shaderIDs;
    for (const auto& stage : stages)
    {
        std::string shadertypename;
        switch (stage.type) {
            case GL_VERTEX_SHADER:
                shadertypename = "VERTEX"; break;
            case GL_FRAGMENT_SHADER:
                shadertypename = "FRAGMENT"; break;
            case GL_COMPUTE_SHADER:
                shadertypename = "COMPUTE"; break;
        }

        unsigned int shader;
        shader = glCreateShader(stage.type);
        glShaderSource(shader, 1, &stage.source, NULL);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR: FAILED TO COMPILE " << shadertypename << " SHADER: \n" << infoLog << std::endl;
        }
        else
        {
            std::cout << "SUCCESS: COMPILED " << shadertypename << " SHADER" << std::endl;
        }
        glAttachShader(ID, shader);

        shaderIDs.push_back(shader);
    }
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR: FAILED TO LINK SHADER PROGRAM: \n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SUCCESS: LINKED SHADER PROGRAM" << std::endl;
    }
    
    for (GLuint shader : shaderIDs)
        glDeleteShader(shader);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::Bind()
{
    glUseProgram(ID);
}

void Shader::SetBool(const char* name, bool value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetInt(const char* name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUInt(const char* name, unsigned int value)
{
    glUniform1ui(GetUniformLocation(name), value);
}

void Shader::SetFloat(const char* name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec2(const char* name, const glm::vec2& value)
{
    glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetVec3(const char* name, const glm::vec3& value)
{
    glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetVec4(const char* name, const glm::vec4& value)
{
    glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetIVec2(const char* name, const glm::ivec2& value)
{
    glUniform2iv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetIVec3(const char* name, const glm::ivec3& value)
{
    glUniform3iv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetIVec4(const char* name, const glm::ivec4& value)
{
    glUniform4iv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetUVec2(const char* name, const glm::uvec2& value)
{
    glUniform2uiv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetUVec3(const char* name, const glm::uvec3& value)
{
    glUniform3uiv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetUVec4(const char* name, const glm::uvec4& value)
{
    glUniform4uiv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetMat2(const char* name, const glm::mat2& value)
{
    glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3(const char* name, const glm::mat3& value)
{
    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const char* name, const glm::mat4& value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
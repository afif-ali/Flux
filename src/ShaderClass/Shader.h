#pragma once

#include <glad/glad.h>

#include <iostream>
#include <unordered_map>
#include <initializer_list>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderStage
{
    GLenum type;
    const char* source;
};

class Shader
{
private:
    unsigned int ID;
    std::unordered_map<std::string, int> uniformLocationCache;

    int GetUniformLocation(const char* name);

public:
    Shader(std::initializer_list<ShaderStage> stages);
    ~Shader();

    void Bind();

    void SetBool(const char* name, bool value);
    void SetInt(const char* name, int value);
    void SetUInt(const char* name, unsigned int value);
    void SetFloat(const char* name, float value);

    void SetVec2(const char* name, const glm::vec2& value);
    void SetVec3(const char* name, const glm::vec3& value);
    void SetVec4(const char* name, const glm::vec4& value);

    void SetIVec2(const char* name, const glm::ivec2& value);
    void SetIVec3(const char* name, const glm::ivec3& value);
    void SetIVec4(const char* name, const glm::ivec4& value);

    void SetUVec2(const char* name, const glm::uvec2& value);
    void SetUVec3(const char* name, const glm::uvec3& value);
    void SetUVec4(const char* name, const glm::uvec4& value);

    void SetMat2(const char* name, const glm::mat2& value);
    void SetMat3(const char* name, const glm::mat3& value);
    void SetMat4(const char* name, const glm::mat4& value);
};
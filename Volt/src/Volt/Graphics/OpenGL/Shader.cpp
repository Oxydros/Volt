#include "vpch.h"

#include "Volt/Graphics/OpenGL/Shader.hpp"

#include <glad/glad.h>

namespace Volt::Graphics::OpenGL
{

    GLuint CompileShader(GLchar const *src, GLenum shaderType, int &success, char *infoLog)
    {
        GLuint vertexShaderID = glCreateShader(shaderType);

        if (vertexShaderID == 0)
        {
            success = 0;
            std::strncpy(infoLog, "Call to glCreateShader failed", 512);
            return -1;
        }

        glShaderSource(vertexShaderID, 1, &src, NULL);
        glCompileShader(vertexShaderID);

        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        }
        return vertexShaderID;
    }

    Shader::Shader(std::string const &shaderPath)
        : m_shaderPath(shaderPath) ,m_programId(0)
    {
        std::string vertexSrc, pixelSrc;

        Shader::GetSourcesFromFile(shaderPath, vertexSrc, pixelSrc);

        int  success;
        char infoLog[512];

        GLuint vertexShaderID = CompileShader(vertexSrc.c_str(), GL_VERTEX_SHADER, success, infoLog);
        if (!success)
        {
            VOLT_ASSERT(false, "Error while compiling vertex shader : {}", infoLog);
        }

        GLuint pixelShaderID = CompileShader(pixelSrc.c_str(), GL_FRAGMENT_SHADER, success, infoLog);
        if (!success)
        {
            VOLT_ASSERT(false, "Error while compiling pixel shader : {}", infoLog);
        }

        m_programId = glCreateProgram();

        glAttachShader(m_programId, vertexShaderID);
        glAttachShader(m_programId, pixelShaderID);
        glLinkProgram(m_programId);

        glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
            VOLT_ASSERT(false, "Error while LINKING shaders in program : {}", infoLog);
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(pixelShaderID);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_programId);
    }

    void Shader::Bind()
    {
        glUseProgram(m_programId);
    }

    void Shader::Reload()
    {
        std::string vertexSrc, pixelSrc;
        VOLT_DEB("Reloading shader {}...", m_shaderPath);

        Shader::GetSourcesFromFile(m_shaderPath, vertexSrc, pixelSrc);

        int  success;
        char infoLog[512];

        GLuint vertexShaderID = CompileShader(vertexSrc.c_str(), GL_VERTEX_SHADER, success, infoLog);
        if (!success)
        {
            VOLT_DEB("Error while compiling vertex shader : {}", infoLog);
            return;
        }

        GLuint pixelShaderID = CompileShader(pixelSrc.c_str(), GL_FRAGMENT_SHADER, success, infoLog);
        if (!success)
        {
            VOLT_DEB("Error while compiling pixel shader : {}", infoLog);
            return;
        }

        //Re-create program
        glDeleteProgram(m_programId);
        uint32_t new_program = glCreateProgram();

        glAttachShader(new_program, vertexShaderID);
        glAttachShader(new_program, pixelShaderID);
        glLinkProgram(new_program);

        glGetProgramiv(new_program, GL_LINK_STATUS, &success);
        glDeleteShader(vertexShaderID);
        glDeleteShader(pixelShaderID);        
        if(!success) {
            glGetProgramInfoLog(new_program, 512, NULL, infoLog);
            VOLT_DEB("Error while LINKING shaders in program : {}", infoLog);
            return;
        }
        glDeleteProgram(m_programId);
        VOLT_DEB("Shader successfully recompiled");
        m_programId = new_program;
    }

    //Quick and dirty to setup camera system asap
    void Shader::SetInt(std::string const &uniform_name, int value)
    {
        int uniformLocation = glGetUniformLocation(m_programId, uniform_name.c_str());
        VOLT_ASSERT(uniformLocation != -1, "Unable to find uniform {} in shader", uniform_name);
        glUniform1i(uniformLocation, value);
    }

    void Shader::SetFloat(std::string const &uniform_name, float value)
    {
        int uniformLocation = glGetUniformLocation(m_programId, uniform_name.c_str());
        VOLT_ASSERT(uniformLocation != -1, "Unable to find uniform {} in shader", uniform_name);
        glUniform1f(uniformLocation, value);
    }

    void Shader::SetVec3f(std::string const &uniform_name, glm::vec3 const &value)
    {
        int uniformLocation = glGetUniformLocation(m_programId, uniform_name.c_str());
        VOLT_ASSERT(uniformLocation != -1, "Unable to find uniform {} in shader", uniform_name);
        glUniform3f(uniformLocation, value.x, value.y, value.z);
    }

    void Shader::SetVec4f(std::string const &uniform_name, glm::vec4 const &value)
    {
        int uniformLocation = glGetUniformLocation(m_programId, uniform_name.c_str());
        VOLT_ASSERT(uniformLocation != -1, "Unable to find uniform {} in shader", uniform_name);
        glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
    }

    void Shader::SetMat3f(std::string const &uniform_name, glm::mat3 const &value)
    {
        int uniformLocation = glGetUniformLocation(m_programId, uniform_name.c_str());
        VOLT_ASSERT(uniformLocation != -1, "Unable to find uniform {} in shader", uniform_name);
        glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::SetMat4f(std::string const &uniform_name, glm::mat4 const &value)
    {
        int uniformLocation = glGetUniformLocation(m_programId, uniform_name.c_str());
        VOLT_ASSERT(uniformLocation != -1, "Unable to find uniform {} in shader", uniform_name);
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
    }
}

Volt::Graphics::Shader::ShaderPtr Volt::Graphics::Shader::CreateShader(std::string const &shaderFile)
{
    return std::make_unique<Volt::Graphics::OpenGL::Shader>(shaderFile);
}
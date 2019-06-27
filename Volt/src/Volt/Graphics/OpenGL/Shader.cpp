#include "vpch.h"

#include "Volt/Graphics/OpenGL/Shader.hpp"

#include <glad/glad.h>

namespace Volt::Graphics::OpenGL
{
    Shader::Shader(std::string const &vertexSrc, std::string const &pixelSrc)
        : m_programID(0)
    {

        int  success;
        char infoLog[512];

        GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        VOLT_ASSERT(vertexShaderID != 0, "Couldn't create vertex Shader")


        const GLchar *src = vertexSrc.c_str();

        glShaderSource(vertexShaderID, 1, &src, NULL);
        glCompileShader(vertexShaderID);

        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
            VOLT_ASSERT(false, "Error while COMPILING vertex shader : {}", infoLog);
        }

        GLuint pixelShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        VOLT_ASSERT(pixelShaderID != 0, "Couldn't create pixel Shader")


        src = pixelSrc.c_str();

        glShaderSource(pixelShaderID, 1, &src, NULL);
        glCompileShader(pixelShaderID);

        glGetShaderiv(pixelShaderID, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(pixelShaderID, 512, NULL, infoLog);
            VOLT_ASSERT(false, "Error while COMPILING pixel shader : {}", infoLog);
        }

        m_programID = glCreateProgram();

        glAttachShader(m_programID, vertexShaderID);
        glAttachShader(m_programID, pixelShaderID);
        glLinkProgram(m_programID);

        glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
            VOLT_ASSERT(false, "Error while LINKING shaders in program : {}", infoLog);
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(pixelShaderID);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_programID);
    }

    void Shader::Bind()
    {
        glUseProgram(m_programID);
    }
}

Volt::Graphics::Shader::ShaderPtr Volt::Graphics::Shader::CreateShader(std::string const &vertexSrc, std::string const &pixelSrc)
{
    return std::make_unique<Volt::Graphics::OpenGL::Shader>(vertexSrc, pixelSrc);
}
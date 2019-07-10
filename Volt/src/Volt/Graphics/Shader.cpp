#include "vpch.h"

#include "Shader.hpp"

namespace Volt::Graphics
{
    void Shader::GetSourcesFromFile(std::string const &filePath, std::string &vertexSrc, std::string &pixelSrc)
    {
        std::ifstream file(filePath);
        std::string line;
        char writeMode = -1;

        while (std::getline(file, line))
        {
            if (line == ">>Vertex")
                writeMode = 0;
            else if (line == ">>Pixel")
                writeMode = 1;
            else if (line.find_first_of(">>") == 0)
                continue;
            else {
                switch (writeMode)
                {
                    case 0:
                        vertexSrc += line + "\n";
                        break;
                    case 1:
                        pixelSrc += line + "\n";
                        break;
                    default:
                        VOLT_WARN("Strange line ignored while reading shader file {}: {}", filePath, line);
                }
            }
        }
    }
}
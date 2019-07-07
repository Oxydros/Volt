#include "vpch.h"

#include "Volt/Graphics/OpenGL/Buffers.hpp"

#include <glad/glad.h>

GLenum VertexElementTypeToOpenGL(Volt::Graphics::VertexElementType type)
{
    using Volt::Graphics::VertexElementType;

    switch (type)
    {
        //FLOAT
        case VertexElementType::FLOAT:
        case VertexElementType::VEC_2F:
        case VertexElementType::VEC_3F:
        case VertexElementType::VEC_4F:
        case VertexElementType::MAT_3F:
        case VertexElementType::MAT_4F:
            return GL_FLOAT;
        //INT
        case VertexElementType::INT:
        case VertexElementType::VEC_2I:
        case VertexElementType::VEC_3I:
        case VertexElementType::VEC_4I:
        case VertexElementType::MAT_3I:
        case VertexElementType::MAT_4I:
            return GL_INT;

        //UNKNOWN
        default: {
            VOLT_ASSERT(false, "Unknown VertexElementType !");
            return -1;
        }
    }
}

namespace Volt::Graphics::OpenGL
{
    //Vertex buffer
    VertexBuffer::VertexBuffer(float const *vertices, size_t count)
    {
        //Create buffer and bind it
        glGenBuffers(1, &m_bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
        //Fill it
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_bufferId);
    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    }

    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //Index buffer
    IndexBuffer::IndexBuffer(int const *indices, size_t count)
        : m_count(count)
    {
        glGenBuffers(1, &m_bufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_bufferId);
    }

    void IndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
    }

    void IndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    //VertayArray
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_arrayObjectId);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_arrayObjectId);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_arrayObjectId);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(VertexBuffer::VertexBufferPtr const &vertexBuffer)
    {
        uint32_t index = 0;

        auto layout = vertexBuffer->GetLayout();

        glBindVertexArray(m_arrayObjectId);
        vertexBuffer->Bind();
        for (auto const &element : layout.GetElements())
        {
            GLenum type = VertexElementTypeToOpenGL(element.type);
            glVertexAttribPointer(index, element.primitiveCount, type, element.normalized ? GL_TRUE : GL_FALSE,
                                    layout.GetStride(), (void*)element.offset);
            glEnableVertexAttribArray(index);
            index++;
        }
        glBindVertexArray(0);
        m_vertexBufferVec.push_back(vertexBuffer);
    }

    void VertexArray::SetIndexBuffer(IndexBuffer::IndexBufferPtr const &indexBuffer)
    {
        glBindVertexArray(m_arrayObjectId);
        indexBuffer->Bind();
        m_indexBuffer = indexBuffer;
    }
}

namespace Volt::Graphics
{
    VertexArray::VertexArrayPtr VertexArray::Create()
    {
        return std::make_shared<Volt::Graphics::OpenGL::VertexArray>();
    }    

    VertexBuffer::VertexBufferPtr VertexBuffer::Create(float const *vertices, size_t count)
    {
        return std::make_shared<Volt::Graphics::OpenGL::VertexBuffer>(vertices, count);
    }

    VertexBuffer::VertexBufferPtr VertexBuffer::Create(std::vector<float> const &vertices)
    {
        return std::make_shared<Volt::Graphics::OpenGL::VertexBuffer>(vertices.data(), vertices.size());
    }

    IndexBuffer::IndexBufferPtr IndexBuffer::Create(int const *indices, size_t count)
    {
        return std::make_shared<Volt::Graphics::OpenGL::IndexBuffer>(indices, count);
    }

    IndexBuffer::IndexBufferPtr IndexBuffer::Create(std::vector<int> const &indices)
    {
        return std::make_shared<Volt::Graphics::OpenGL::IndexBuffer>(indices.data(), indices.size());
    }
}
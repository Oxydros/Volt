#pragma once

#include "Volt/Graphics/Buffers.hpp"

namespace Volt::Graphics::OpenGL
{
    //OpenGL implementation of Volt::Graphics::VertexBuffer
    class VertexBuffer : public Volt::Graphics::VertexBuffer
    {
    public:
        VertexBuffer(float const *vertices, size_t count);
        virtual ~VertexBuffer();

    public:
        void Bind() override;
        void Unbind() override;
        void SetLayout(VertexBufferLayout const &&layout) override { m_layout = layout; }
        void SetLayout(VertexBufferLayout const &layout) override { m_layout = layout; }
        VertexBufferLayout const &GetLayout() const override { return m_layout; }

    private:
        VertexBufferLayout  m_layout;
        uint32_t            m_bufferId;
    };

    //OpenGL implementation of Volt::Graphics::IndexBuffer
    class IndexBuffer : public Volt::Graphics::IndexBuffer
    {
    public:
        IndexBuffer(int const *indices, size_t count);
        virtual ~IndexBuffer();

    public:
        void Bind() override;
        void Unbind() override;

        size_t GetCount() const override { return m_count; }

    private:
        size_t              m_count;
        uint32_t            m_bufferId;
    };

    //OpenGL implementation of Volt::Graphics::VertexArray
    class VertexArray : public Volt::Graphics::VertexArray
    {
    public:
        VertexArray();
        virtual ~VertexArray();

        void Bind() override;
        void Unbind() override;

        void AddVertexBuffer(VertexBuffer::VertexBufferPtr const &vertexBuffer) override;
        std::vector<VertexBuffer::VertexBufferPtr> GetVertexBuffers() const override { return m_vertexBufferVec; }

        void SetIndexBuffer(IndexBuffer::IndexBufferPtr const &indexBuffer) override;
        IndexBuffer::IndexBufferPtr const &GetIndexBuffer() const override { return m_indexBuffer; }

    private:
        uint32_t                                    m_arrayObjectId;
        std::vector<VertexBuffer::VertexBufferPtr>  m_vertexBufferVec;
        IndexBuffer::IndexBufferPtr                 m_indexBuffer;
    };
}
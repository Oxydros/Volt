#pragma once

#include <memory>
#include <vector>

#include "Volt/Core.hpp"

namespace Volt::Graphics
{
    //Type of an element being inside a vertex
    enum class VertexElementType : u_int8_t
    {
        UNKNOWN = 0,
        FLOAT, VEC_3F, VEC_4F, MAT_3F, MAT_4F,
        INT, VEC_3I, VEC_4I, MAT_3I, MAT_4I
    };

    //Return the size in byte of a VertexElementType
    size_t GetVertexElementSize(VertexElementType type);

    //Return the number of primitive of a VertexElementType
    //eg. VEC_3F is composed of 3 floats, so this function will return 3
    size_t GetVertexElementCount(VertexElementType type);

    //Describe the layout of a Vertex
    class VertexBufferLayout
    {
    public:
        struct Element
        {
            VertexElementType   type;
            bool                normalized;
            size_t              byteSize;
            size_t              primitiveCount;
            size_t              offset;

            Element(VertexElementType type, bool normalized = false)
                : type(type), normalized(normalized),
                byteSize(GetVertexElementSize(type)), primitiveCount(GetVertexElementCount(type)), offset(0)
            {}
        };

    public:
        VertexBufferLayout() {}
        VertexBufferLayout(std::initializer_list<Element> const &elements);
        ~VertexBufferLayout() = default;

    public:
        inline std::vector<Element> const &GetElements() const { return m_elements; }
        inline size_t GetStride () const { return m_stride; }

    private:
        std::vector<Element>    m_elements;
        size_t                  m_stride;
    };

    //Logic representation of the vertices
    class VertexBuffer
    {
    public:
        typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;

        static VertexBufferPtr Create(float const *vertices, size_t count);
        static VertexBufferPtr Create(std::vector<float> const &vertices);

    public:
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;

    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetLayout(VertexBufferLayout const &&) = 0;
        virtual void SetLayout(VertexBufferLayout const &) = 0;
        virtual VertexBufferLayout const &GetLayout() const = 0;
    };

    //Logic representation of the indices
    class IndexBuffer
    {
    public:
        typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;

        static IndexBufferPtr Create(int const *indices, size_t count);
        static IndexBufferPtr Create(std::vector<int> const &indices);

    public:
        IndexBuffer() = default;
        virtual ~IndexBuffer() = default;

    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual size_t GetCount() const = 0;
    };


    //Logic representation of a VertexArray
    class VertexArray
    {
    public:
        typedef std::shared_ptr<VertexArray> VertexArrayPtr;

        static VertexArrayPtr Create();

    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void AddVertexBuffer(VertexBuffer::VertexBufferPtr const &vertexBuffer) = 0;
        virtual std::vector<VertexBuffer::VertexBufferPtr> GetVertexBuffers() const = 0;

        virtual void SetIndexBuffer(IndexBuffer::IndexBufferPtr const &indexBuffer) = 0;
        virtual IndexBuffer::IndexBufferPtr const &GetIndexBuffer() const = 0;
    };
}
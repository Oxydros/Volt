#include "vpch.h"

#include "Volt/Graphics/Buffers.hpp"

namespace Volt::Graphics
{
    size_t GetVertexElementSize(VertexElementType type)
    {
        switch (type)
        {
            //FLOAT
            case VertexElementType::FLOAT:  return sizeof(float);
            case VertexElementType::VEC_3F: return sizeof(float) * 3;
            case VertexElementType::VEC_4F: return sizeof(float) * 4;
            case VertexElementType::MAT_3F: return sizeof(float) * 3 * 3;
            case VertexElementType::MAT_4F: return sizeof(float) * 4 * 4;   
            //INT
            case VertexElementType::INT:    return sizeof(int);
            case VertexElementType::VEC_3I: return sizeof(int) * 3;
            case VertexElementType::VEC_4I: return sizeof(int) * 4;
            case VertexElementType::MAT_3I: return sizeof(int) * 3 * 3;
            case VertexElementType::MAT_4I: return sizeof(int) * 4 * 4; 
            //UNKNOWN
            default: {
                VOLT_ASSERT(false, "Unknown VertexElementType !");
                return -1;
            }
        };
    }   
    size_t GetVertexElementCount(VertexElementType type)
    {
        switch (type)
        {
            //FLOAT
            case VertexElementType::FLOAT:  return 1;
            case VertexElementType::VEC_3F: return 3;
            case VertexElementType::VEC_4F: return 4;
            case VertexElementType::MAT_3F: return 3 * 3;
            case VertexElementType::MAT_4F: return 4 * 4;   
            //INT
            case VertexElementType::INT:    return 1;
            case VertexElementType::VEC_3I: return 3;
            case VertexElementType::VEC_4I: return 4;
            case VertexElementType::MAT_3I: return 3 * 3;
            case VertexElementType::MAT_4I: return 4 * 4;   
            //UNKNOWN
            default: {
                VOLT_ASSERT(false, "Unknown VertexElementType !");
                return -1;
            }
        };
    }

    VertexBufferLayout::VertexBufferLayout(std::initializer_list<Element> const &elements)
        : m_elements(elements)
    {
        size_t offset = 0;
        m_stride = 0;

        for (auto &elem : m_elements)
        {
            elem.offset = offset;
            offset += elem.byteSize;
        }
        m_stride = offset;
    }
}
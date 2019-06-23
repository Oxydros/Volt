#pragma once

#include <memory>
#include <string>
#include "Volt/Logger.hpp"

namespace Volt
{
    //Rendering Layer Logic
    class Layer
    {
    public:
        typedef std::shared_ptr<Layer>     LayerPtr;

    public:
        template <class LayerType>
        static LayerPtr Create() { return std::move(std::make_shared<LayerType>()); }

    public:
        Layer(std::string const &layerName) : m_name(layerName) {
            VOLT_DEB("Creating layer {}", layerName);
        }
        virtual ~Layer() {
            VOLT_DEB("Deleting layer {}", m_name);
        }

        inline std::string const &GetName() const { return m_name; }

        //Here we will add DeltaTime
        virtual void OnUpdate() = 0;
        virtual void OnImGUI() = 0;

    private:
        std::string const   m_name;
    };
}
#pragma once

#include <vector>

#include "Volt/Layer.hpp"

namespace Volt
{
    // -- Overlay over a std::vector to handle Volt::Layer
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        //Add a layer at the top of the rendering stack
        void PushLayer(Layer::LayerPtr layer);
        void PopLayer(Layer::LayerPtr const &layer);
        //Add a layer at the end of the rendering stack
        void PushOverlay(Layer::LayerPtr layer);
        void PopOverlay(Layer::LayerPtr const &layer);

        // -- Iterators
        inline auto begin() { return m_layerStack.begin(); }
        inline auto begin() const { return m_layerStack.begin(); }
        inline auto cbegin() const { return m_layerStack.cbegin(); }

        inline auto end() { return m_layerStack.end(); }
        inline auto end() const { return m_layerStack.end(); }
        inline auto cend() const { return m_layerStack.cend(); }

        inline void clear() { m_layerStack.clear(); }

        inline std::size_t size() const { return m_layerStack.size(); }

    private:
        std::vector<Layer::LayerPtr>    m_layerStack;
        size_t                          m_overlayIndex;
    };
}
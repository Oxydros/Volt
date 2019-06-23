#include "vpch.h"

#include "Volt/LayerStack.hpp"

namespace Volt
{
    LayerStack::LayerStack()
        : m_overlayIndex(0)
    {}

    LayerStack::~LayerStack()
    {}

    void LayerStack::PushLayer(Layer::LayerPtr layer)
    {
        VOLT_DEB("Pushing layer {} at pos {}", layer->GetName(), m_overlayIndex);
        //Making sure we insert Layer before the overlay section
        m_layerStack.emplace(m_layerStack.begin() + m_overlayIndex, std::move(layer));
        m_overlayIndex++;
    }

    void LayerStack::PopLayer(Layer::LayerPtr const &layer)
    {
        auto it = std::find(m_layerStack.begin(), m_layerStack.end(), layer);
        if (it != m_layerStack.end())
        {
            VOLT_DEB("Poping layer {}", (*it)->GetName());
            m_layerStack.erase(it);
            m_overlayIndex--;
        }
    }

    void LayerStack::PushOverlay(Layer::LayerPtr layer)
    {
        VOLT_DEB("Pushing overlay layer {}", layer->GetName());
        m_layerStack.emplace_back(std::move(layer));
    }

    void LayerStack::PopOverlay(Layer::LayerPtr const &layer)
    {
        auto it = std::find(m_layerStack.begin(), m_layerStack.end(), layer);
        if (it != m_layerStack.end())
        {
            VOLT_DEB("Poping overlay layer {}", (*it)->GetName());
            m_layerStack.erase(it);
        }
    }
}
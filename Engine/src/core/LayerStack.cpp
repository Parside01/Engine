#include "../include/layer/LayerStack.hpp"
#include "LayerStack.hpp"

namespace Engine
{
    LayerStack::LayerStack() {
        m_LayerInsert = m_Layers.begin();
    }

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer *layer)
    {
    }

    void LayerStack::PushOverlay(Layer *overlay)
    {
    }

    void LayerStack::PopLayer(Layer layer)
    {
    }

} // namespace Engine

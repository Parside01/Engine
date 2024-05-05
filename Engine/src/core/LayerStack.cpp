#include "../include/layer/LayerStack.hpp"

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


} // namespace Engine

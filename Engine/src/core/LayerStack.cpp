// #include "../include/layer/LayerStack.hpp"

#include "Engine/layer/LayerStack.hpp"

namespace Engine
{
    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer *layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }


    void LayerStack::PushOverlay(Layer *overlay) {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer) {   
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
    }

    void LayerStack::PopOverlay(Layer* layer) {
        auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
		}
    }
} // namespace Engine

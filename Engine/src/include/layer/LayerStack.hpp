#ifndef ENGINE_LAYERSTACK_HPP
#define ENGINE_LAYERSTACK_HPP


#include "../Core.hpp"
#include "../events/Event.hpp"
#include "Layer.hpp"

namespace Engine
{
    
    class ENGINE_API LayerStack {
    public:

        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer layer);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        std::vector<Layer*>::iterator m_LayerInsert;
    }

} // namespace Engine


#endif
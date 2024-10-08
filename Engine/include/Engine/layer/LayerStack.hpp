#ifndef ENGINE_LAYERSTACK_HPP
#define ENGINE_LAYERSTACK_HPP


// #include "../Core.hpp"
// #include "../events/Event.hpp"

#include "Layer.hpp"

#include "Engine/Core.hpp"
#include "Engine/events/Event.hpp"

namespace Engine
{
    
    class ENGINE_API LayerStack {
    public:

        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
        std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

        std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
        std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
        std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
    private:
        std::vector<Layer*> m_Layers;
        uint32_t m_LayerInsertIndex = 0;
    };

} // namespace Engine


#endif
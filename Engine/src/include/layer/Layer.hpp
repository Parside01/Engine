#ifndef ENGINE_LAYER_HPP
#define ENGINE_LAYER_HPP

#include "../Core.hpp"
#include "../events/Event.hpp"

namespace Engine
{
    
    class ENGINE_API Layer {
    public:
        Layer(const std::string& name = "BaseLayer") : m_LayerName(name) {}
        virtual ~Layer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
        virtual void OnEvent(Event& event);

        inline const std::string& GetName() const { return m_LayerName; }
    private:
        std::string m_LayerName;
    };

} // namespace Engine



#endif

#ifndef ENGINE_TIMESTEP_HPP
#define ENGINE_TIMESTEP_HPP

namespace Engine
{
    class Timestep 
    {
    public:
        Timestep(float time = 0.0f)
            : m_Time(time) 
        {

        }

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000.f; }
        
    private:
        float m_Time;
    };
    
} // namespace Engine


#endif

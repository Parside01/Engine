#ifndef ENGINE_CORE_HPP
#define ENGINE_CORE_HPP

#ifdef __linux__

  #define ENGINE_PLATFORM_LINUX
  #define ENGINE_API __attribute__((visibility("default")))

  #ifndef ENGINE_BUILD_SO

    #define ENGINE_API __attribute__((visibility("default")))

  #endif

#endif

#define BIT(x) (1 << x)

namespace Engine
{
    class ENGINE_API Core
    {
    private:
        
    public:
        Core();
        virtual ~Core();
    };
  
    
} // namespace Engine

#endif
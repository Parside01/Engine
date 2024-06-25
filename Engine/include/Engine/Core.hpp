#ifndef ENGINE_CORE_HPP
#define ENGINE_CORE_HPP

#include <memory>

#ifdef __linux__

  #define ENGINE_PLATFORM_LINUX
  #define ENGINE_API __attribute__((visibility("default")))

  #ifndef ENGINE_BUILD_SO

    #define ENGINE_API __attribute__((visibility("default")))

  #endif

#endif

namespace Engine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
    class ENGINE_API Core
    {
    private:
        
    public:
        Core();
        virtual ~Core();
    };
  
    
} // namespace Engine

#endif
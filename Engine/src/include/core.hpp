#ifdef __linux__
  #define ENGINE_PLATFORM_LINUX
  #define ENGINE_API __attribute__((visibility("default")))
  #ifndef ENGINE_BUILD_SO
    #define ENGINE_API __attribute__((visibility("default")))
  #endif
#endif

#ifndef ENGINE_CORE_HPP
#define ENGINE_CORE_HPP

namespace Engine
{
  class ENGINE_API Core
  {
  private:
      /* data */
  public:
      Core(/* args */);
      virtual ~Core();
  };
    
} // namespace Engine

#endif
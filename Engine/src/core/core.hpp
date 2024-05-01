#ifdef __linux__
  #define ENGINE_PLATFORM_LINUX
  #define ENGINE_API __attribute__((dllexport))
  #ifndef ENGINE_BUILD_SO
    #define ENGINE_API __attribute__((dllimport))
  #endif
#endif
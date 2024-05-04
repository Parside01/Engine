#ifndef ENGINE_BASE_HPP
#define ENGINE_BASE_HPP

    #if defined(__linux__) 
        #include "signal.h"
        #define EG_DEBUG_BREAK() raise(SIGTRAP)
    #endif

    #define BIT(x) (1 << x)

    #define EG_EXPAND_MACRO(x) x
    #define EG_STRINGIFY_MACRO(x) #x

    #define EG_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { EG##type##ERROR(msg, __VA_ARGS__); EG_DEBUG_BREAK(); } }
	#define EG_INTERNAL_ASSERT_WITH_MSG(type, check, ...) EG_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define EG_INTERNAL_ASSERT_NO_MSG(type, check) EG_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", EG_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define EG_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define EG_INTERNAL_ASSERT_GET_MACRO(...) EG_EXPAND_MACRO( EG_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, EG_INTERNAL_ASSERT_WITH_MSG, EG_INTERNAL_ASSERT_NO_MSG) )

	#define EG_ASSERT(...) EG_EXPAND_MACRO( EG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define EG_CORE_ASSERT(...) EG_EXPAND_MACRO( EG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

#endif
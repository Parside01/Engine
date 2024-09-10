#ifndef ENGINE_UNIFORMBUFFER_HPP
#define ENGINE_UNIFORMBUFFER_HPP

#include <Engine/engine_precompile_headers.hpp>


namespace Engine {
    class UniformBuffer {
    public:
        virtual ~UniformBuffer() = default;
        virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

        static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
    };
}


#endif //ENGINE_UNIFORMBUFFER_HPP

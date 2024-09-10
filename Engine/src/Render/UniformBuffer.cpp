#include <Engine/Render/UniformBuffer.hpp>

#include <Engine/Render/Renderer.hpp>

namespace Engine {
    Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding) {
        RendererAPI::API api = Renderer::GetAPI();
#if ENGINE_API_OPENGL
        return std::make_shared<OpenGLUniformBuffer>(size, binding);
#endif
    }
}

#include "Engine/Render/FrameBuffer.hpp"

#include "Engine/Render/Renderer.hpp"
#include "Engine/Render/OpenGL/FrameBuffer_OpenGL.hpp"

namespace Engine {

    Ref<FrameBuffer> FrameBuffer::Create(const FramebufferSpec &initData) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: EG_CORE_ASSERT(false, "Не поддерживает такой апи");
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFrameBuffer>(initData);
        }
        EG_CORE_ASSERT(false, "Неизвестное апи");
        return nullptr;
    }

}

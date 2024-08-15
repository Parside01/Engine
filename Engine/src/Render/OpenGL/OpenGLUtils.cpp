#include "Engine/Render/OpenGL/OpenGLUtils.hpp"

namespace Engine {
    std::pair<uint32_t, uint32_t> OpenGLUtils::GetOpenGLFormatFromChannels(uint32_t channels) {
        std::pair<uint32_t, uint32_t> res(0, 0);
        switch (channels) {
            case 1:
                res.first = GL_R;
                res.second = GL_R8;
            case 2:
                res.first = GL_RG;
                res.second = GL_RG8;
            case 3:
                res.first = GL_RGB;
                res.second = GL_RGB8;
            case 4:
                res.first = GL_RGBA;
                res.second = GL_RGBA8;
            default:
                break;
        }
        return res;
    }

    GLenum OpenGLUtils::TextureParamNameToOpenGL(const TextureParamName &name) {
        switch (name) {
            case TextureParamName::TEXTURE_MAG_FILTER: return GL_TEXTURE_MAG_FILTER;
            case TextureParamName::TEXTURE_MIN_FILTER: return GL_TEXTURE_MIN_FILTER;
            case TextureParamName::TEXTURE_WRAP_R: return GL_TEXTURE_WRAP_R;
            case TextureParamName::TEXTURE_WRAP_S: return GL_TEXTURE_WRAP_S;
            case TextureParamName::TEXTURE_WRAP_T: return GL_TEXTURE_WRAP_T;
        }
        EG_CORE_ASSERT(false, "Неизвестное имя типа");
        return -1;
    }

    GLenum OpenGLUtils::TextureParamValueToOpenGL(const TextureParamValue &value) {
        switch (value) {
            case TextureParamValue::LINEAR: return GL_LINEAR;
            case TextureParamValue::NEAREST: return GL_NEAREST;
            case TextureParamValue::REPEAT: return GL_REPEAT;
            case TextureParamValue::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
            case TextureParamValue::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
        }
        EG_CORE_ASSERT(false, "Неизвестный тип значения");
        return -1;
    }

    GLenum OpenGLUtils::TextureTargetToOpenGL(const TextureTarget &target) {
        switch (target) {
            case TextureTarget::TEXTURE2D: return GL_TEXTURE_2D;
            case TextureTarget::TEXTURE_CUBE_MAP: return GL_TEXTURE_CUBE_MAP;
        }
        EG_CORE_ASSERT(false, "Неизвестное имя для таргета");
        return -1;
    }
}

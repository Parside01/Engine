#ifndef ENGINE_OPENGLUTILS_HPP
#define ENGINE_OPENGLUTILS_HPP


#ifdef ENGINE_API_OPENGL
#include <Engine/engine_precompile_headers.hpp>
#include <GL/glew.h>
#include <Engine/Render/Texture/TextureTypes.hpp>
#include <Engine/log/Log.hpp>

namespace Engine {
    class OpenGLUtils {

    public:
        static std::pair<uint32_t, uint32_t> GetOpenGLFormatFromChannels(uint32_t channels);

        static GLenum TextureParamNameToOpenGL(const TextureParamName &name);

        static GLenum TextureParamValueToOpenGL(const TextureParamValue &value);

        static GLenum TextureTargetToOpenGL(const TextureTarget &target);
    };
}

#endif
#endif //ENGINE_OPENGLUTILS_HPP

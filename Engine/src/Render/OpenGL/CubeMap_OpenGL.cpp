#include <Engine/Render/OpenGL/CubeMap_OpenGL.hpp>
#include <Engine/Render/OpenGL/OpenGLUtils.hpp>
#include <GL/glew.h>
#include <Engine/Utils.hpp>

namespace Engine {
    OpenGLCubeMap::OpenGLCubeMap(const std::array<Ref<Texture2D>, 6> faces) {
        mFaces = faces;
        GLCall(glGenTextures(1, &mTextureID));
        GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID));

        for (uint32_t i{0}; i < 6; ++i) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB,  mFaces[i]->mWidth, mFaces[i]->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mFaces[i]->mTextureData.get()
            );
        }

        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT));
    }

    void OpenGLCubeMap::Bind() const {
        GLCall(glBindTextureUnit(0, mTextureID));
    }

    void OpenGLCubeMap::Unbind() const {
    }
}

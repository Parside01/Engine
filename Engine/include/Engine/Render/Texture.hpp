#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Engine/engine_precompile_headers.hpp"
#include <glm/glm.hpp>

namespace Engine {
    class Texture {
    public:
        virtual ~Texture() = default;

        [[nodiscard]] virtual uint32_t GetWidth() const = 0;
        [[nodiscard]] virtual uint32_t GetHeight() const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;
        virtual void Bind(uint32_t slot = 0) const = 0;
        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture {
    public:
        static Ref<Texture2D> Create(uint32_t width, uint32_t height, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});
        static Ref<Texture2D> Create(const std::string& path);

        virtual uint32_t GetTextureID() const = 0;
        virtual const  std::string& GetTexturePath() const = 0;
    };
}

#endif //TEXTURE_HPP

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Core.hpp"

namespace Engine {
    class Texture {
    public:
        virtual ~Texture() = default;

        [[nodiscard]] virtual uint32_t GetWidth() const = 0;
        [[nodiscard]] virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture {
    public:
        static Ref<Texture2D> Create(const std::string& path);
    };
}

#endif //TEXTURE_HPP

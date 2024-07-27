#ifndef ENGINE_BASECOMPONENTS_HPP
#define ENGINE_BASECOMPONENTS_HPP

#include "Engine/engine_precompile_headers.hpp"
#include <glm/glm.hpp>

namespace Engine {

    struct TagComponent {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent& tagComponent) = default;

        explicit TagComponent(const std::string& tag) : Tag(tag) {}
    };

}

#endif //ENGINE_BASECOMPONENTS_HPP

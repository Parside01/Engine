#ifndef ENGINE_MESHMANAGER_HPP
#define ENGINE_MESHMANAGER_HPP

#include "Engine/Render/Mesh.hpp"

namespace Engine {

    class MeshManager {
    public:
        static Ref<Mesh> CreateMesh(const std::string& path);
    };

}

#endif //ENGINE_MESHMANAGER_HPP

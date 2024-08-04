#ifndef ENGINE_RENDERER3D_HPP
#define ENGINE_RENDERER3D_HPP
#include <Engine/Scene/EditorCamera.hpp>
#include <Engine/Render/Mesh.hpp>
#include <Engine/Scene/TransfromComponent.hpp>

namespace Engine {

    class Renderer3D {
    public:

        static void Init();
        static void Shutdown();

        static void BeginScene(const Ref<EditorCamera>& camera);
        static void EndScene();

        static void Flush();

        static void StartBatch();
        static void NextBatch();

        // Временно
        static void DrawMesh(const Ref<Mesh>& mesh, const TransformComponent& transform);
    };

}

#endif //ENGINE_RENDERER3D_HPP

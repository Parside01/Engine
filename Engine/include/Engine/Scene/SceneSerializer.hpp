#ifndef ENGINE_SCENE_SERIALIZER_HPP 
#define ENGINE_SCENE_SERIALIZER_HPP

#include "Engine/Scene/Scene.hpp"
#include "Engine/Core.hpp"
#include <yaml-cpp/yaml.h>


namespace Engine
{
    // TODO: Решение временное, надо подумать как автоматизировать эту фигню.
    // Ладно, даже временного не будет, лучше сразу норм сделать, а пока что забили.
    class SceneSerializer {
    public: 
        SceneSerializer(const Ref<Scene>& scene);
        virtual ~SceneSerializer() = default;

        void SerializeToYAML(const std::string& filepath);
        bool DeserializeFromYAML(const std::string& filepath);
    private:

        void SerializeEntity(YAML::Emitter& out, Entity entity);

    private:
        Ref<Scene> m_Scene; 
    };

} // namespace Engine



#endif 
#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Scene/SceneSerializer.hpp"
#include "Engine/Scene/Entity.hpp"
#include "Engine/log/Log.hpp"

namespace Engine
{
    
    SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : m_Scene(scene) {}

    void SceneSerializer::SerializeToYAML(const std::string& filepath) {
        YAML::Emitter out;

        out << YAML::BeginMap;
        out << YAML::Key << "Scene";
        out << YAML::Value << "Name";
        out << YAML::Key << "Entities";
        out << YAML::Value << YAML::BeginSeq; 
        m_Scene->GetRegistry().view<entt::entity>().each([&](entt::entity id){
            Entity entity(id, m_Scene.get()); 
            if (!entity) return; 

            SerializeEntity(out, entity);
        });

        out << YAML::EndSeq;
        out << YAML::EndMap; 
        std::ofstream file(filepath); 
        file << out.c_str();
    }

    void SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity entity) {
        out << YAML::BeginMap; 
        out << YAML::Key << "Entity" << YAML::Value << static_cast<uint32_t>(entity);

        out << YAML::EndMap;
    }

    bool SceneSerializer::DeserializeFromYAML(const std::string& filepath) {
        
    }
    
} // namespace Engine


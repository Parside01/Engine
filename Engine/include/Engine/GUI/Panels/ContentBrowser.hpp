#ifndef ENGINE_CONTENTBROWSER_HPP
#define ENGINE_CONTENTBROWSER_HPP

#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/Texture.hpp"

namespace Engine {

    class ContentBrowser {
    public:
        ContentBrowser(); 
        virtual ~ContentBrowser() = default;

        void OnImGuiRender();
    private:
        std::filesystem::path m_CurrentDir;

        Ref<Texture2D> m_DirIcon;
        Ref<Texture2D> m_FileIcon;
    };

} // Engine

#endif //ENGINE_CONTENTBROWSER_HPP

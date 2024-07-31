#ifndef ENGINE_UIRENDERER_HPP
#define ENGINE_UIRENDERER_HPP

#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    class UIRenderer {
    public: 
        UIRenderer() = default;
        virtual ~UIRenderer() = default;

        static void DrawInputText(const char* label, std::string& input);

        struct UIStyle {
            uint32_t Input_DefautlBufferSize = 256;
            float Column_DefaultSize = 100.f;
        };
        static UIStyle m_Style;
    };
} // namespace Engine


#endif //ENGINE_UIRENDERER_HPP

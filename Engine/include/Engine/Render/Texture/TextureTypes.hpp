#ifndef ENGINE_TEXTURETYPES_HPP
#define ENGINE_TEXTURETYPES_HPP

namespace Engine {

    enum class TextureTarget : uint8_t {
        TEXTURE2D = 0,
        TEXTURE_CUBE_MAP = 1,
    };

    enum class TextureDataFormat : uint8_t {
        R = 0,
        R8 = 0,

        RG = 1,
        RG8 = 1,

        RGB = 2,
        RGB8 = 2,

        RGBA = 3,
        RGBA8 = 3,
    };

    enum class TextureParamName : uint8_t {
        /* Possible values:
        *   NEAREST
        *   LINEAR
        */
        TEXTURE_MIN_FILTER = 0,

        /* Possible values:
        *   NEAREST
        *   LINEAR
        */
        TEXTURE_MAG_FILTER = 1,

        /* Possible values:
        *   CLAMP_TO_EDGE
        *   REPEAT
        *   CLAMP_TO_BORDER
        */
        TEXTURE_WRAP_T = 2,
        TEXTURE_WRAP_S = 3,
        TEXTURE_WRAP_R = 4,
    };

    enum class TextureParamValue : uint8_t {
        NEAREST = 0,
        LINEAR = 1,

        REPEAT = 2,
        CLAMP_TO_EDGE = 3,
        CLAMP_TO_BORDER = 4,
    };

    struct TextureSpec {
        TextureTarget mTarget;
        std::unordered_map<TextureParamName, TextureParamValue> mParams;
        uint32_t mWidth = 2048;
        uint32_t mHeight = 2048;
        uint32_t mChannelsNum = 4;
    };

}

#endif //ENGINE_TEXTURETYPES_HPP

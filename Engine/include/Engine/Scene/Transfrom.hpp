#ifndef ENGINE_TRANSFROM_HPP
#define ENGINE_TRANSFROM_HPP

namespace Engine {

    struct Position {
        float x;
        float y;
        float z;
    };

    struct Rotation {
        float Roll;
        float Pitch;
        float Yaw;

        float rx; // Similary Roll.
        float ry; // Similary Pitch.
        float rz; // Similary Yaw.
    };

    struct Scale {
        float sx;
        float sy;
        float sz;
    };
}

#endif //ENGINE_TRANSFROM_HPP

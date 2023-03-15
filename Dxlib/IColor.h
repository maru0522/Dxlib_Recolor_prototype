#pragma once
#include "IBlock.h"
class IColor
{
public:
    // íËã`
    enum class Color
    {
        RED,
        BLUE,
        GREEN,
        YELLOW,
        MAGENTA,
        CYAN,
    };

    // ä÷êî
    virtual ~IColor(void) = default;

    inline void SetColor(Color color) { color_ = color; }
    inline Color GetColor(void) { return color_; }
    int32_t GetColorValue(void);

private:
    Color color_{ Color::RED };
};

#ifndef NON_USING_NAMESPACE_COLOR

using Color = IColor::Color;

#endif // !NON_USING_NAMESPACE_COLOR

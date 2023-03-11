#pragma once
#include "IBlock.h"
class IColorBlock
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
    virtual ~IColorBlock(void) = default;

    inline void SetColor(Color color) { color_ = color; }
    inline Color GetColor(void) { return color_; }
    uint32_t GetColorValue(void);

private:
    Color color_{ Color::RED };
};

#ifndef NON_USING_NAMESPACE_COLOR

using Color = IColorBlock::Color;

#endif // !NON_USING_NAMESPACE_COLOR

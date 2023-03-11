#include "IColorBlock.h"

uint32_t IColorBlock::GetColorValue(void)
{
    switch (color_)
    {
    case IColorBlock::Color::RED:
        return 0xff0000;
        break;

    case IColorBlock::Color::BLUE:
        return 0x0000ff;
        break;

    case IColorBlock::Color::GREEN:
        return 0x00ff00;
        break;

    case IColorBlock::Color::YELLOW:
        return 0xffff00;
        break;

    case IColorBlock::Color::MAGENTA:
        return 0xff00ff;
        break;

    case IColorBlock::Color::CYAN:
        return 0x00ffff;
        break;

    default:
        return 0xffffff;
        break;
    }
}

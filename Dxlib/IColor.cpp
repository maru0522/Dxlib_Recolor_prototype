#include "IColor.h"

uint32_t IColor::GetColorValue(void)
{
    switch (color_)
    {
    case IColor::Color::RED:
        return 0xff0000;
        break;

    case IColor::Color::BLUE:
        return 0x0000ff;
        break;

    case IColor::Color::GREEN:
        return 0x00ff00;
        break;

    case IColor::Color::YELLOW:
        return 0xffff00;
        break;

    case IColor::Color::MAGENTA:
        return 0xff00ff;
        break;

    case IColor::Color::CYAN:
        return 0x00ffff;
        break;

    default:
        return 0xffffff;
        break;
    }
}

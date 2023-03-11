#pragma once
#include "IEntity.h"
#include "IColor.h"

class Player : public IEntity, public IColor
{
public:
    // íËêî
    static constexpr uint32_t defaultPlayerSize_{};

    Player(const Vector2 pos, const Vector2 size, const Color color);
};


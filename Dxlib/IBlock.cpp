#include "IBlock.h"

IBlock::IBlock(const Vector2& pos, const Vector2& radius) :
    IEntity(pos, radius)
{
    SetType(Type::NONE);
}

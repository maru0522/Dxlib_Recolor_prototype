#include "BlockFactory.h"
#include "Vector2.h"

IBlock* BlockFactory::CreateBlock(const std::string& type, const Vector2& pos, const Vector2& radius)
{
    if (type == "BASIC") return std::move(new BasicBlock{ pos,radius });

    return nullptr;
}

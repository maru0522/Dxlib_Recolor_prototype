#include "BlockFactory.h"
#include "Vector2.h"
#include "BasicBlock.h"
#include "StoneBlock.h"

std::unique_ptr<IBlock> BlockFactory::CreateBlock(const std::string& type, const Vector2& pos, const Vector2& radius)
{
    if (type == "NONE") return std::make_unique<IBlock>(pos, radius);
    if (type == "BASIC") return std::make_unique<BasicBlock>(pos, radius);
    if (type == "STONE") return std::make_unique<StoneBlock>(pos, radius);

    return nullptr;
}

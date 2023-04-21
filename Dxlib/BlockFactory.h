#pragma once
#include "BasicBlock.h"
#include <string>
#include "Vector2.h"

class BlockFactory
{
public:
    // ä÷êî
    BlockFactory(void) = default;

    IBlock* CreateBlock(const std::string& type, const Vector2& pos, const Vector2& radius = { IBlock::defaultRadius_,IBlock::defaultRadius_ });
};


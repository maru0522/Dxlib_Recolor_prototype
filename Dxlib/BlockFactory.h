#pragma once
#include "BasicBlock.h"
#include <string>
#include "Vector2.h"
#include <memory>

class BlockFactory
{
public:
    // ä÷êî
    static std::unique_ptr<IBlock> CreateBlock(const std::string& type, const Vector2& pos, const Vector2& radius = { IBlock::defaultRadius_,IBlock::defaultRadius_ });

private:
    BlockFactory(void) = default;
};


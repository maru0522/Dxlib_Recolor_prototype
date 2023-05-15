#include "GoalBlock.h"

GoalBlock::GoalBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::GOAL);
}

void GoalBlock::Update(void)
{
}

void GoalBlock::Draw(void)
{
}

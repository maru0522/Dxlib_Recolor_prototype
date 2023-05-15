#pragma once
#include "IBlock.h"
class GoalBlock :
    public IBlock
{
public:
    // ä÷êî
    GoalBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius = { 1,1 });
    ~GoalBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};

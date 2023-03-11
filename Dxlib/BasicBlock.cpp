#include "BasicBlock.h"
#include <DxLib.h>

BasicBlock::BasicBlock(const Vector2& pos, const Vector2& size)
{
    SetPos(pos);
    SetSize(size);
}

void BasicBlock::Update(void)
{
}

void BasicBlock::Draw(void)
{
    DrawBoxAA(
        GetPos().x - GetSize().x / 2, GetPos().y - GetSize().y / 2, // x1,y1
        GetPos().x + GetSize().x / 2, GetPos().y + GetSize().y / 2, // x2,y2
        0xffffff, false);
} 

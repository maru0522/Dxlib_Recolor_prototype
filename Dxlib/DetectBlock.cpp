#include "DetectBlock.h"
#include <DxLib.h>

DetectBlock::DetectBlock(const Vector2& pos, const Vector2& size)
{
    SetPos(pos);
    SetSize(size);
    SetBlockType(IBlock::Type::detect);
}

void DetectBlock::Update(void)
{
}

void DetectBlock::Draw(void)
{
    DrawBoxAA(
        GetPos().x - GetSize().x / 2, GetPos().y - GetSize().y / 2, // x1,y1
        GetPos().x + GetSize().x / 2, GetPos().y + GetSize().y / 2, // x2,y2
        0x0000ff, false);
}

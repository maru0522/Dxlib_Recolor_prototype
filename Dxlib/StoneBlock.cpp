#include "StoneBlock.h"
#include <DxLib.h>

StoneBlock::StoneBlock(const Vector2& pos, const Vector2& size, Color color)
{
    SetPos(pos);
    SetSize(size);
    SetColor(color);
}

void StoneBlock::Update(void)
{
}

void StoneBlock::Draw(void)
{
    DrawBoxAA(GetPos().x - GetSize().x / 2, GetPos().y - GetSize().y / 2, // x1,y1
              GetPos().x + GetSize().x / 2, GetPos().y + GetSize().y / 2, // x2,y2
              GetColorValue(), false);
}

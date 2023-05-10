#include "PieceEntranceBlock.h"

PieceEntranceBlock::PieceEntranceBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius) :
    IBlock(pos, offset, radius)
{
    SetType(Type::PIECEENTRANCE);
}

void PieceEntranceBlock::Update(void)
{
}

void PieceEntranceBlock::Draw(void)
{
    int posX{ static_cast<int>(GetPos().x) }, posY{ static_cast<int>(GetPos().y) };
    int radiusX{ static_cast<int>(GetRadius().x) }, radiusY{ static_cast<int>(GetRadius().y) };

    if (GetEntranceOpen() == false)
        DrawBox(
            posX - radiusX, posY - radiusY,
            posX + radiusX, posY + radiusY,
            0x0000ff, true
        );

    //DrawCircle(static_cast<int>(GetPos().x), static_cast<int>(GetPos().y), 4, 0xff00ff, true, 1);
}

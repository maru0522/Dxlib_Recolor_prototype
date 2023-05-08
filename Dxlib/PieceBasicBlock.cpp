#include "PieceBasicBlock.h"

PieceBasicBlock::PieceBasicBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius) :
    IBlock(pos,offset,radius)
{
    SetType(Type::PIECEBASIC);
}

void PieceBasicBlock::Update(void)
{
}

void PieceBasicBlock::Draw(void)
{
    int posX{ static_cast<int>(GetPos().x) }, posY{ static_cast<int>(GetPos().y) };
    int radiusX{ static_cast<int>(GetRadius().x) }, radiusY{ static_cast<int>(GetRadius().y) };

    DrawBox(
        posX - radiusX, posY - radiusY,
        posX + radiusX, posY + radiusY,
        0x00ff00, true
    );

    //DrawCircle(static_cast<int>(GetPos().x), static_cast<int>(GetPos().y), 4, 0xff0000, true, 1);
}

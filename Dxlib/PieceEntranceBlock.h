#pragma once
#include "IBlock.h"
class PieceEntranceBlock :
    public IBlock
{
public:
    // �֐�
    PieceEntranceBlock(const Vector2& pos, const Vector2& radius = { 1,1 });
    ~PieceEntranceBlock(void) {};

    void Update(void) override;
    void Draw(void) override;

private:
    // �ϐ�
    bool isInPiece_;

public:
    // setter�Egetter
    void SetInPiece(bool inPiece) { isInPiece_ = inPiece; }

    bool GetInPiece(void) { return isInPiece_; }
};


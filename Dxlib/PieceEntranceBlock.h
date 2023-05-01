#pragma once
#include "IBlock.h"
class PieceEntranceBlock :
    public IBlock
{
public:
    // 関数
    PieceEntranceBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius = { 1,1 });
    ~PieceEntranceBlock(void) {};

    void Update(void) override;
    void Draw(void) override;

private:
    // 変数
    bool isInPiece_;

public:
    // setter・getter
    void SetInPiece(bool inPiece) { isInPiece_ = inPiece; }

    bool GetInPiece(void) { return isInPiece_; }
};


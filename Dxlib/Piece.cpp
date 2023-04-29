#include "Piece.h"
#include <cmath>

Piece::Piece(const Vector2& pos, const Vector2& radius) :
    pos_(pos), radius_(radius), rotate_(0),
    isTabTop_(true), isTabRight_(true), isTabLeft_(true), isTabBottom_(true),
    isInPlace_(false)
{
}

void Piece::Update(void)
{
    for (auto& block : blockList_) {
        block->Update();
    }
}

void Piece::Draw(void)
{
    for (auto& block : blockList_) {
        block->Draw();
    }

    DrawBox(
        static_cast<int>(pos_.x - radius_.x), static_cast<int>(pos_.y - radius_.y),
        static_cast<int>(pos_.x + radius_.x), static_cast<int>(pos_.y + radius_.y),
        0xff0000, false
    );

    DrawCircle(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 4, 0xff0000, false, 1);
}

void Piece::Register(IBlock* ptr)
{
    // offsetとブロックのradiusの取得
    Vector2  offset{ ptr->GetOffset() }, bRadius{ ptr->GetRadius() };

    // オフセットの値がpieceのradiusよりも大きい場合、ローカル座標がピースの枠をはみ出るため追加しない。
    if (std::fabs(offset.x + bRadius.x) > std::fabs(radius_.x)) {
        delete ptr;
        return;
    };
    if (std::fabs(offset.y + bRadius.y) > std::fabs(radius_.y)) {
        delete ptr;
        return;
    }

    // リストへの追加
    blockList_.emplace_back(ptr);

    // ブロックの座標をpieceの原点からのローカル座標をセット
    blockList_.back()->SetPos(pos_ + offset);
}

#include "Piece.h"
#include <cmath>
#include "PieceBasicBlock.h"
#include "PieceEntranceBlock.h"
#include "Input.h"
#include "Util.h"

Piece::Piece(const Vector2& pos, const Vector2& radiusBlockCount) :
    pos_(pos), radiusBlockCount_(radiusBlockCount), rotate_(0),
    isInPlace_(false)
{
    float offset{ IBlock::radiusBase_ };

    // 上辺
    // 0 ~ radiusBlockCount * 2 - 1まで
    for (size_t t = 0; t < radiusBlockCount.x * 2 + 1; t++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ Vector2{(pos.x - radiusBlockCount.x * IBlock::radiusBase_ * 2) + t * IBlock::radiusBase_ * 2, pos.y - radiusBlockCount.y * IBlock::radiusBase_ * 2 - offset}, Vector2{IBlock::radiusBase_,1} });
    }
    // 底辺
    // radiusBlockCount * 2 ~ radiusBlockCount * 4 - 1まで
    for (size_t b = 0; b < radiusBlockCount.x * 2 + 1; b++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ Vector2{(pos.x - radiusBlockCount.x * IBlock::radiusBase_ * 2) + b * IBlock::radiusBase_ * 2, pos.y + radiusBlockCount.y * IBlock::radiusBase_ * 2 + offset}, Vector2{IBlock::radiusBase_,1} });
    }
    // 左辺
    // radiusBlockCount * 4 ~ radiusBlockCount * 6 - 1まで
    for (size_t l = 0; l < radiusBlockCount.x * 2 + 1; l++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ Vector2{ pos.x - radiusBlockCount.x * IBlock::radiusBase_ * 2 - offset, (pos.y - radiusBlockCount.y * IBlock::radiusBase_ * 2) + l * IBlock::radiusBase_ * 2}, Vector2{1,IBlock::radiusBase_} });
    }
    // 右辺
    for (size_t r = 0; r < radiusBlockCount.x * 2 + 1; r++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ Vector2{ pos.x + radiusBlockCount.x * IBlock::radiusBase_ * 2 + offset, (pos.y - radiusBlockCount.y * IBlock::radiusBase_ * 2) + r * IBlock::radiusBase_ * 2}, Vector2{1,IBlock::radiusBase_} });
    }
}

void Piece::Initialize(void)
{
    int t{}, r{}, l{}, b{};

    for (size_t i = 0; i < tabs_.size(); i++)
    {
        switch (tabs_[i].dir_)
        {
        case Piece::Dir::TOP:
            t++;
            break;
        case Piece::Dir::RIGHT:
            r++;
            break;
        case Piece::Dir::LEFT:
            l++;
            break;
        case Piece::Dir::BOTTOM:
            b++;
            break;
        default:
            break;
        }
    }

    // 上方向
    //while (t > 0)
    //{

    //}

    //RegisterBlock(new PieceBasicBlock{ radiusBlockCount_ * IBlock::radiusBase_ })
}

void Piece::Update(void)
{
    for (auto& block : blockVector_) {
        block->Update();
    }

    if (KEY::IsTrigger(KEY_INPUT_0)) {
        rotate_ - 90 < 0 ? // 押したことによって 0 >> -90になるかどうか
            rotate_ = 270 :
            rotate_ -= 90;

        ChangeTabsDir(-90);
        RotateBlocks(-90);
    }
    if (KEY::IsTrigger(KEY_INPUT_1)) {
        rotate_ + 90 > 270 ? // 押したことによって 360 >> 450になるかどうか
            rotate_ = 90 :
            rotate_ += 90;

        ChangeTabsDir(90);
        RotateBlocks(90);
    }
}

void Piece::Draw(void)
{
    for (auto& block : blockVector_) {
        block->Draw();
    }

    // pieceの範囲表示
    DrawBox(
        static_cast<int>(pos_.x - radiusBlockCount_.x * IBlock::radiusBase_), static_cast<int>(pos_.y - radiusBlockCount_.y * IBlock::radiusBase_),
        static_cast<int>(pos_.x + radiusBlockCount_.x * IBlock::radiusBase_), static_cast<int>(pos_.y + radiusBlockCount_.y * IBlock::radiusBase_),
        0xff0000, false
    );

    // 中心点
    DrawCircle(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 4, 0xff0000, false, 1);

    // 各方向へのでっぱり表現
    // 上下
    //isTabTop_ ?
    //    DrawBox(static_cast<int>(pos_.x - 15), static_cast<int>(pos_.y - radiusBlockCount_.y - 15), static_cast<int>(pos_.x + 15), static_cast<int>(pos_.y - radiusBlockCount_.y), 0xff0000, false) :
    //    DrawBox(static_cast<int>(pos_.x - 15), static_cast<int>(pos_.y - radiusBlockCount_.y + 15), static_cast<int>(pos_.x + 15), static_cast<int>(pos_.y - radiusBlockCount_.y), 0xff0000, false);
    //isTabBottom_ ?
    //    DrawBox(static_cast<int>(pos_.x - 15), static_cast<int>(pos_.y + radiusBlockCount_.y + 15), static_cast<int>(pos_.x + 15), static_cast<int>(pos_.y + radiusBlockCount_.y), 0xff0000, false) :
    //    DrawBox(static_cast<int>(pos_.x - 15), static_cast<int>(pos_.y + radiusBlockCount_.y - 15), static_cast<int>(pos_.x + 15), static_cast<int>(pos_.y + radiusBlockCount_.y), 0xff0000, false);
    //// 左右
    //isTabLeft_ ?
    //    DrawBox(static_cast<int>(pos_.x - radiusBlockCount_.x - 15), static_cast<int>(pos_.y - 15), static_cast<int>(pos_.x - radiusBlockCount_.x), static_cast<int>(pos_.y + 15), 0xff0000, false) :
    //    DrawBox(static_cast<int>(pos_.x - radiusBlockCount_.x + 15), static_cast<int>(pos_.y - 15), static_cast<int>(pos_.x - radiusBlockCount_.x), static_cast<int>(pos_.y + 15), 0xff0000, false);
    //isTabRight_ ?
    //    DrawBox(static_cast<int>(pos_.x + radiusBlockCount_.x + 15), static_cast<int>(pos_.y - 15), static_cast<int>(pos_.x + radiusBlockCount_.x), static_cast<int>(pos_.y + 15), 0xff0000, false) :
    //    DrawBox(static_cast<int>(pos_.x + radiusBlockCount_.x - 15), static_cast<int>(pos_.y - 15), static_cast<int>(pos_.x + radiusBlockCount_.x), static_cast<int>(pos_.y + 15), 0xff0000, false);
}

void Piece::RegisterBlock(IBlock* ptr)
{
    //// offsetとブロックのradiusの取得
    //Vector2  offset{ ptr->GetOffset() }, bRadius{ ptr->GetRadius() };

    //// オフセットの値がpieceのradiusよりも大きい場合、ローカル座標がピースの枠をはみ出るため追加しない。
    //if (std::fabs(offset.x + bRadius.x) > std::fabs(radiusBlockCount_.x * IBlock::radiusBase_)) {
    //    delete ptr;
    //    return;
    //};
    //if (std::fabs(offset.y + bRadius.y) > std::fabs(radiusBlockCount_.y * IBlock::radiusBase_)) {
    //    delete ptr;
    //    return;
    //}

    //// リストへの追加
    //blockList_.emplace_back(ptr);

    //// ブロックの座標をpieceの原点からのローカル座標をセット
    //blockList_.back()->SetPos(pos_ + offset);
}

void Piece::RegisterTab(bool isTab, int indexBlockVector, const Dir& dir)
{
    Tab_t tab;
    tab.isTab_ = isTab;
    tab.pos_ = blockVector_[indexBlockVector]->GetPos();
    tab.dir_ = dir;
    tab.indexBlockVector_ = indexBlockVector;

    tabs_.emplace_back(tab);

    blockVector_[indexBlockVector] = std::make_unique<PieceEntranceBlock>(blockVector_[indexBlockVector]->GetPos(), blockVector_[indexBlockVector]->GetRadius());
}

void Piece::ChangeTabsDir(int changeValue)
{
    std::vector<Tab_t> copy = tabs_;

    // changeValueの値は 90/-90 のみの想定
    if (changeValue > 0) {
        for (size_t i = 0; i < tabs_.size(); i++)
        {
            if (copy[i].dir_ == Dir::TOP) tabs_[i].dir_ = Dir::RIGHT;
            if (copy[i].dir_ == Dir::RIGHT) tabs_[i].dir_ = Dir::BOTTOM;
            if (copy[i].dir_ == Dir::BOTTOM) tabs_[i].dir_ = Dir::LEFT;
            if (copy[i].dir_ == Dir::LEFT) tabs_[i].dir_ = Dir::TOP;
        }
    }
    else {
        for (size_t i = 0; i < tabs_.size(); i++)
        {
            if (copy[i].dir_ == Dir::TOP) tabs_[i].dir_ = Dir::LEFT;
            if (copy[i].dir_ == Dir::RIGHT) tabs_[i].dir_ = Dir::TOP;
            if (copy[i].dir_ == Dir::BOTTOM) tabs_[i].dir_ = Dir::RIGHT;
            if (copy[i].dir_ == Dir::LEFT) tabs_[i].dir_ = Dir::BOTTOM;
        }
    }

}

void Piece::RotateBlocks(int rotateValue)
{
    // rotateValueは 90/-90 のみの想定。また度数法とする。

    if (rotateValue > 0) {
        for (size_t i = 0; i < blockVector_.size(); i++)
        {
            // rotate変更。
            int rotate{ blockVector_[i]->GetRotate() };

            rotate + rotateValue >= 450 ?
                blockVector_[i]->SetRotate(90) :
                blockVector_[i]->SetRotate(rotate + 90);


            // 座標変換
            Vector2 bpos{ blockVector_[i]->GetPos() };
            Vector2 diffPos{ bpos.x - pos_.x,bpos.y - pos_.y };
            float rad{ Util::Convert::ToRadian((float)rotateValue) };

            Vector2 result{};
            result.x = diffPos.x * std::cosf(rad) - diffPos.y * std::sinf(rad) + pos_.x;
            result.y = diffPos.x * std::sinf(rad) + diffPos.y * std::cosf(rad) + pos_.y;

            blockVector_[i]->SetPos(result);

            if (blockVector_[i]->GetType() == IBlock::Type::PIECEBASIC ||
                blockVector_[i]->GetType() == IBlock::Type::PIECEENTRANCE) {
                Vector2 bradius{ blockVector_[i]->GetRadius() };

                // 半径変更
                bradius.x > bradius.y ?
                    blockVector_[i]->SetRadius(Vector2{ 1, IBlock::radiusBase_ }) :
                    blockVector_[i]->SetRadius(Vector2{ IBlock::radiusBase_, 1 });
            }
        }
    }
    else {
        for (size_t i = 0; i < blockVector_.size(); i++)
        {
            // rotate変更。
            int rotate{ blockVector_[i]->GetRotate() };

            rotate + rotateValue <= -90 ?
                blockVector_[i]->SetRotate(270) :
                blockVector_[i]->SetRotate(rotate - 90);


            // 座標変換
            Vector2 bpos{ blockVector_[i]->GetPos() };
            Vector2 diffPos{ bpos.x - pos_.x,bpos.y - pos_.y };
            float rad{ Util::Convert::ToRadian((float)rotateValue) };

            Vector2 result{};
            result.x = diffPos.x * std::cosf(rad) - diffPos.y * std::sinf(rad) + pos_.x;
            result.y = diffPos.x * std::sinf(rad) + diffPos.y * std::cosf(rad) + pos_.y;

            blockVector_[i]->SetPos(result);


            if (blockVector_[i]->GetType() == IBlock::Type::PIECEBASIC ||
                blockVector_[i]->GetType() == IBlock::Type::PIECEENTRANCE) {
                Vector2 bradius{ blockVector_[i]->GetRadius() };

                // 半径変更
                bradius.x > bradius.y ?
                    blockVector_[i]->SetRadius(Vector2{ 1, IBlock::radiusBase_ }) :
                    blockVector_[i]->SetRadius(Vector2{ IBlock::radiusBase_, 1 });
            }
        }
    }
}

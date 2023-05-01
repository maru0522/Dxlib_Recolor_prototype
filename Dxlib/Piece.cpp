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

    // ���
    // 0 ~ radiusBlockCount * 2 �܂�
    for (size_t t = 0; t < radiusBlockCount.x * 2 + 1; t++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ Vector2{(pos.x - radiusBlockCount.x * IBlock::radiusBase_ * 2) + t * IBlock::radiusBase_ * 2, pos.y - radiusBlockCount.y * IBlock::radiusBase_ * 2 - offset}, Vector2{ -radiusBlockCount.x * IBlock::radiusBase_ * 2 + t * IBlock::radiusBase_ * 2, -radiusBlockCount.y * IBlock::radiusBase_ * 2 - offset}, Vector2{IBlock::radiusBase_,1} });
    }
    // ���
    // radiusBlockCount * 2 + 1 ~ radiusBlockCount * 4 �܂�
    for (size_t b = 0; b < radiusBlockCount.x * 2 + 1; b++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ Vector2{(pos.x - radiusBlockCount.x * IBlock::radiusBase_ * 2) + b * IBlock::radiusBase_ * 2, pos.y + radiusBlockCount.y * IBlock::radiusBase_ * 2 + offset}, Vector2{ -radiusBlockCount.x * IBlock::radiusBase_ * 2 + b * IBlock::radiusBase_ * 2, radiusBlockCount.y * IBlock::radiusBase_ * 2 + offset }, Vector2{IBlock::radiusBase_,1} });
    }
    // ����
    // radiusBlockCount * 4 + 1 ~ radiusBlockCount * 6 �܂�
    for (size_t l = 0; l < radiusBlockCount.x * 2 + 1; l++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ Vector2{ pos.x - radiusBlockCount.x * IBlock::radiusBase_ * 2 - offset, (pos.y - radiusBlockCount.y * IBlock::radiusBase_ * 2) + l * IBlock::radiusBase_ * 2}, Vector2{ -radiusBlockCount.x * IBlock::radiusBase_ * 2 - offset, -radiusBlockCount.y * IBlock::radiusBase_ * 2 + l * IBlock::radiusBase_ * 2}, Vector2{1,IBlock::radiusBase_} });
    }
    // �E��
    for (size_t r = 0; r < radiusBlockCount.x * 2 + 1; r++)
    {
        blockVector_.emplace_back(new PieceBasicBlock{ Vector2{ pos.x + radiusBlockCount.x * IBlock::radiusBase_ * 2 + offset, (pos.y - radiusBlockCount.y * IBlock::radiusBase_ * 2) + r * IBlock::radiusBase_ * 2}, Vector2{ +radiusBlockCount.x * IBlock::radiusBase_ * 2 + offset,  -radiusBlockCount.y * IBlock::radiusBase_ * 2 + r * IBlock::radiusBase_ * 2},Vector2{1,IBlock::radiusBase_} });
    }
}

void Piece::Update(void)
{
    for (auto& block : blockVector_) {
        block->Update();
    }

    if (isOperator_)
    {
        if (KEY::IsTrigger(KEY_INPUT_J)) {
            rotate_ - 90 < 0 ? // ���������Ƃɂ���� 0 >> -90�ɂȂ邩�ǂ���
                rotate_ = 270 :
                rotate_ -= 90;

            ChangeTabsDir(-90);
            RotateBlocks(-90);
        }
        if (KEY::IsTrigger(KEY_INPUT_K)) {
            rotate_ + 90 > 270 ? // ���������Ƃɂ���� 360 >> 450�ɂȂ邩�ǂ���
                rotate_ = 90 :
                rotate_ += 90;

            ChangeTabsDir(90);
            RotateBlocks(90);
        }

        if (KEY::IsDown(KEY_INPUT_W)) {
            pos_.y -= 5;
            MoveBlocks({ 0,-5 });
        }
        if (KEY::IsDown(KEY_INPUT_S)) {
            pos_.y += 5;
            MoveBlocks({ 0, 5 });
        }
        if (KEY::IsDown(KEY_INPUT_A)) {
            pos_.x -= 5;
            MoveBlocks({ -5, 0 });
        }
        if (KEY::IsDown(KEY_INPUT_D)) {
            pos_.x += 5;
            MoveBlocks({ 5, 0 });
        }

        UpdateTabs();
        WriteBlockPos();
    }
}

void Piece::Draw(void)
{
    for (auto& block : blockVector_) {
        block->Draw();
    }

    // piece�͈͕̔\��
    DrawBox(
        static_cast<int>(pos_.x - radiusBlockCount_.x * IBlock::radiusBase_), static_cast<int>(pos_.y - radiusBlockCount_.y * IBlock::radiusBase_),
        static_cast<int>(pos_.x + radiusBlockCount_.x * IBlock::radiusBase_), static_cast<int>(pos_.y + radiusBlockCount_.y * IBlock::radiusBase_),
        0xff0000, false
    );

    // ���S�_
    DrawCircle(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 4, 0xff0000, false, 1);
}

void Piece::RegisterTab(bool isTab, int indexBlockVector, const Dir& dir)
{
    Tab_t tab;
    tab.isTab_ = isTab;
    tab.pos_ = blockVector_[indexBlockVector]->GetPos();
    tab.dir_ = dir;
    tab.indexBlockVector_ = indexBlockVector;

    tabs_.emplace_back(tab);

    blockVector_[indexBlockVector] = std::make_unique<PieceEntranceBlock>(blockVector_[indexBlockVector]->GetPos(), blockVector_[indexBlockVector]->GetOffset(), blockVector_[indexBlockVector]->GetRadius());
}

void Piece::ChangeTabsDir(int changeValue)
{
    std::vector<Tab_t> copy = tabs_;

    // changeValue�̒l�� 90/-90 �݂̂̑z��
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
    // rotateValue�� 90/-90 �݂̂̑z��B�܂��x���@�Ƃ���B

    if (rotateValue > 0) {
        for (size_t i = 0; i < blockVector_.size(); i++)
        {
            // rotate�ύX�B
            int rotate{ blockVector_[i]->GetRotate() };

            rotate + rotateValue >= 450 ?
                blockVector_[i]->SetRotate(90) :
                blockVector_[i]->SetRotate(rotate + 90);


            // ���W�ϊ�
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

                // ���a�ύX
                bradius.x > bradius.y ?
                    blockVector_[i]->SetRadius(Vector2{ 1, IBlock::radiusBase_ }) :
                    blockVector_[i]->SetRadius(Vector2{ IBlock::radiusBase_, 1 });
            }

            // offset
            blockVector_[i]->SetOffset(Vector2{ result - pos_ });
        }
    }
    else {
        for (size_t i = 0; i < blockVector_.size(); i++)
        {
            // rotate�ύX�B
            int rotate{ blockVector_[i]->GetRotate() };

            rotate + rotateValue <= -90 ?
                blockVector_[i]->SetRotate(270) :
                blockVector_[i]->SetRotate(rotate - 90);


            // ���W�ϊ�
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

                // ���a�ύX
                bradius.x > bradius.y ?
                    blockVector_[i]->SetRadius(Vector2{ 1, IBlock::radiusBase_ }) :
                    blockVector_[i]->SetRadius(Vector2{ IBlock::radiusBase_, 1 });
            }

            // offset
            blockVector_[i]->SetOffset(Vector2{ result - pos_ });
        }
    }
}

void Piece::MoveBlocks(const Vector2& moveValue)
{
    for (size_t i = 0; i < blockVector_.size(); i++)
    {
        // ���W�ϊ�
        Vector2 velocity{ blockVector_[i]->GetPos() + moveValue };
        blockVector_[i]->SetPos(velocity);
    }
}

void Piece::UpdateTabs(void)
{
    for (size_t i = 0; i < tabs_.size(); i++)
    {
        tabs_[i].pos_ = blockVector_[tabs_[i].indexBlockVector_]->GetPos();
    }
}

void Piece::WriteBlockPos(void)
{
    float offset{ IBlock::radiusBase_ };

    for (size_t i = 0; i < blockVector_.size(); i++)
    {
        blockVector_[i]->SetPos(pos_ + blockVector_[i]->GetOffset());
    }
}

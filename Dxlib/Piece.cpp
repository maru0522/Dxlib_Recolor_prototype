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
    // offset�ƃu���b�N��radius�̎擾
    Vector2  offset{ ptr->GetOffset() }, bRadius{ ptr->GetRadius() };

    // �I�t�Z�b�g�̒l��piece��radius�����傫���ꍇ�A���[�J�����W���s�[�X�̘g���͂ݏo�邽�ߒǉ����Ȃ��B
    if (std::fabs(offset.x + bRadius.x) > std::fabs(radius_.x)) {
        delete ptr;
        return;
    };
    if (std::fabs(offset.y + bRadius.y) > std::fabs(radius_.y)) {
        delete ptr;
        return;
    }

    // ���X�g�ւ̒ǉ�
    blockList_.emplace_back(ptr);

    // �u���b�N�̍��W��piece�̌��_����̃��[�J�����W���Z�b�g
    blockList_.back()->SetPos(pos_ + offset);
}

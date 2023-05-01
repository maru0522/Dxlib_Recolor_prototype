#include "IBlock.h"

IBlock::IBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius) :
    type_(Type::NONE), pos_(pos), offset_(offset), radius_(radius), rotate_(0)
{
}

void IBlock::Update(void)
{
}

void IBlock::Draw(void)
{
    DrawBox(
        static_cast<int>(pos_.x - radius_.x), static_cast<int>(pos_.y - radius_.y),
        static_cast<int>(pos_.x + radius_.x), static_cast<int>(pos_.y + radius_.y),
        0x0000ff, false
    );
}

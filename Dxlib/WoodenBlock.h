#pragma once
#include "IBlock.h"
// ����A���߂���Œ肳��Ă�s�[�X�ɓo�^����̂��]�܂���

class WoodenBlock :
    public IBlock
{
public:
    // �֐�
    WoodenBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius = { 1,1 });
    ~WoodenBlock(void) {};

    void Update(void) override;
    void Draw(void) override;
};


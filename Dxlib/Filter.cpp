#include "Filter.h"
#include "Input.h"
#include <DxLib.h>

using KEY = Input::Keyboard;

Filter::Filter(const Vector2& pos, const Vector2& size, const Color& color)
{
    SetPos(pos);
    SetSize(size);
    SetColor(color);
    drawer_.Initialize(GetPosPtr(), GetSize(), GetColorValue());
}

void Filter::Update(void)
{
    Move();
    drawer_.Update();
}

void Filter::Draw(void)
{
    drawer_.Draw();

#ifdef _DEBUG
    DisplayDebug();
#endif // _DEBUG
}

void Filter::DisplayDebug(void)
{
    DrawFormatString(500, 0, 0xffffff, "filter_pos: (%f,%f)", GetPos().x, GetPos().y);
    DrawFormatString(500, 20, 0xffffff, "filter_size: (%f,%f)", GetSize().x, GetSize().y);
}

void Filter::Move(void)
{
    // �ړ���
    Vector2 vel{};

    // ���E���͂̔���ƈړ��ʉ��Z
    vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A));
    // �㉺���͂̔���ƈړ��ʉ��Z
    vel.y += (KEY::IsDown(KEY_INPUT_S) - KEY::IsDown(KEY_INPUT_W));

    // ���K��
    vel = vel.normalize();

    vel *= moveSpeed_;

    // �ʒu
    Vector2 pos{ GetPos() + vel };

    // ���f
    SetPos(pos);;
}

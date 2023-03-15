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
    Draw();
    drawer_.Draw();
}

void Filter::DisplayDebug(void)
{
}

void Filter::Move(void)
{
    Vector2 vel{};

    // ���E���͂̔���ƈړ��ʉ��Z
    vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A)) * moveSpeed_;
    // �㉺���͂̔���ƈړ��ʉ��Z
    vel.y += (KEY::IsDown(KEY_INPUT_S) - KEY::IsDown(KEY_INPUT_W)) * moveSpeed_;

    // ���K��
    vel = vel.normalize();

    // ���f
    SetPos(vel);
}

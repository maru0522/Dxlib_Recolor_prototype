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

Filter::Filter(const Vector2& pos, const Vector2& size, float moveSpeed, const Color& color)
{
    SetPos(pos);
    SetSize(size);
    moveSpeed_ = moveSpeed;
    SetColor(color);
    drawer_.Initialize(GetPosPtr(), GetSize(), GetColorValue());
}

void Filter::Update(bool isInput)
{
    Move(isInput);
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

void Filter::Move(bool isInput)
{
    // à⁄ìÆó 
    Vector2 vel{};

    if (isInput) {
        // ç∂âEì¸óÕÇÃîªíËÇ∆à⁄ìÆó â¡éZ
        vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A));
        // è„â∫ì¸óÕÇÃîªíËÇ∆à⁄ìÆó â¡éZ
        vel.y += (KEY::IsDown(KEY_INPUT_S) - KEY::IsDown(KEY_INPUT_W));
    }

    // ê≥ãKâª
    vel = vel.normalize();

    vel *= moveSpeed_;

    // à íu
    Vector2 pos{ GetPos() + vel };

    // îΩâf
    SetPos(pos);
}

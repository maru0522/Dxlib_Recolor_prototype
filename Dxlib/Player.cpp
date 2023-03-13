#include "Player.h"
#include "Input.h"
#include <DxLib.h>

using KEY = Input::Keyboard;

Player::Player(const Vector2 pos, const Vector2 size, const Color color)
{
}

void Player::Update(void)
{
}

void Player::Draw(void)
{
}

void Player::Move(void)
{
    Vector2 vel{};

    vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A)) * moveSpeed_;
}

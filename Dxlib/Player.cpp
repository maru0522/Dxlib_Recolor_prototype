#include "Player.h"
#include "Input.h"
#include <DxLib.h>
#include "StageManager.h"
#include "Util.h"

using namespace Util::Math;
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
    // 移動量
    Vector2 vel{};

    // x軸
    // 左右入力の判定と移動量加算
    vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A)) * moveSpeed_;

    // y軸
    // ジャンプ処理
    Jump(vel);
    // 重力
    vel.y -= gravity_;

    // 移動量補正
    Collision(vel);

    // 補正済の移動量をposに加算
    Vector2 pos{ GetPos() + vel };
    SetPos(pos);

}

void Player::Jump(Vector2& vel)
{
    static float jumpValue{ 0.f };

    // トリガーでジャンプ
    if (KEY::IsTrigger(KEY_INPUT_SPACE) && isJump_ == false) {
        isJump_ = true;
        jumpValue += jumpPower_;
    }

    // velにジャンプ量(y軸移動量)を加算
    vel.y += jumpValue;
    if (jumpValue > 0.f) {
        jumpValue -= fallValue_;
    }
    else if (jumpValue <= 0.f) {
        isJump_ = false;
    }

    // 0未満の値にならない。
    jumpValue = (std::max)(jumpValue, 0.f);
}

void Player::Collision(Vector2& vel)
{
    for (std::unique_ptr<IBlock>& i : StageManager::GetStage()->blocks_) {
        if (std::abs(i->GetPos().x - GetPos().x) > 5) continue;

        float surplus{};

        // x軸方向
        if (CheckHit(GetPos().x, GetSize().x, vel.x, i->GetPos().x, i->GetSize().x, surplus)) {
            isPositive<float>(vel.x) ? vel.x + surplus : vel.x - surplus;
        }

        // y軸方向
        if (CheckHit(GetPos().y, GetSize().y, vel.y, i->GetPos().y, i->GetSize().y, surplus)) {
            isPositive<float>(vel.y) ? vel.y + surplus : vel.y - surplus;
        }
    }
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize, float& surplus)
{
    surplus = std::abs(pos - blockpos + vel) - size / 2 + blocksize / 2;

    // 値が0未満ならめり込んでる。
    return surplus < 0;
}

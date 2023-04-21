#include "Player.h"
#include "Input.h"
#include <DxLib.h>
#include <memory>
#include "IBlock.h"
#include "StageManager.h"

Player::Player(const Vector2& pos, const Vector2& radius)
{
    SetPos(pos);
    SetRadius(radius);
}

void Player::Update(void)
{
    Move();
}

void Player::Draw(void)
{
    DrawBoxAA(GetPos().x - GetRadius().x, GetPos().y - GetRadius().y, GetPos().x + GetRadius().x, GetPos().y + GetRadius().y, 0xffffff, true);
    DrawCircle((int)GetPos().x, (int)GetPos().y, 10, 0xff0000, 1, 1);
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
    vel.y += gravity_;

    //vel = vel.normalize();

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
    vel.y -= jumpValue;
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
    for (std::unique_ptr<IBlock>& i : StageManager::GetInstance()->GetStagePtr()->blocks_) {
        if (std::abs(i->GetPos().x - GetPos().x) > (IBlock::defaultRadius_ * 2) * 3) {
            continue;
        }

        float surplus{};

        // y軸方向
        if (CheckHit(GetPos().x, GetRadius().x, 0, i->GetPos().x, i->GetRadius().x)) {
            if (CheckHit(GetPos().y, GetRadius().y, vel.y, i->GetPos().y, i->GetRadius().y, surplus)) {
                vel.y > 0 ? vel.y += surplus : vel.y -= surplus;
            }
        }

        // x軸方向
        if (CheckHit(GetPos().y, GetRadius().y, 0, i->GetPos().y, i->GetRadius().y)) {
            if (CheckHit(GetPos().x, GetRadius().x, vel.x, i->GetPos().x, i->GetRadius().x, surplus)) {
                vel.x > 0 ? vel.x += surplus : vel.x -= surplus;
            }
        }
    }
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius)
{
    // 値が0未満ならめり込んでる。
    return std::abs(pos - blockpos + vel) - (radius + blockradius) < 0;
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus)
{
    surplus = std::abs(pos - blockpos + vel) - (radius + blockradius);

    // 値が0未満ならめり込んでる。
    return surplus < 0;
}

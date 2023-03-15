#include "Player.h"
#include "Input.h"
#include <DxLib.h>
#include "StageManager.h"
#include "Util.h"

using namespace Util::Math;
using KEY = Input::Keyboard;

Player::Player(const Vector2 pos, const Vector2 size, const Color color)
{
    SetPos(pos);
    SetSize(size);
    SetColor(color);
    drawer_.Initialize(GetPosPtr(), GetSize(), GetColorValue());
}

void Player::Update(void)
{
    Move();
    drawer_.Update();
}

void Player::Draw(void)
{
    drawer_.Draw();

    DrawBoxAA(GetPos().x - GetSize().x / 2, GetPos().y - GetSize().y / 2, GetPos().x + GetSize().x / 2, GetPos().y + GetSize().y / 2, 0xffffff, true);
    DrawCircle((int)GetPos().x, (int)GetPos().y, 10, 0xff0000, 1, 1);

#ifdef _DEBUG
    DisplayDebug();
#endif // _DEBUG
}

void Player::DisplayDebug(void)
{
    DrawFormatString(0, 0, 0xffffff, "player_pos: (%f,%f)", GetPos().x, GetPos().y);
    DrawFormatString(0, 20, 0xffffff, "player_size: (%f,%f)", GetSize().x, GetSize().y);
    DrawFormatString(0, 40, 0xffffff, isJump_ ? "player_isJump: true" : "player_isJump: false");
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
    for (std::unique_ptr<IBlock>& i : StageManager::GetStage()->blocks_) {
        if (std::abs(i->GetPos().x - GetPos().x) > StageManager::defaultBlockSize_ * 2) {
            continue;
        }

        float surplus{};

        // y軸方向
        if (CheckHit(GetPos().x, GetSize().x, 0, i->GetPos().x, i->GetSize().x)) {
            if (CheckHit(GetPos().y, GetSize().y, vel.y, i->GetPos().y, i->GetSize().y, surplus)) {
                isPositive<float>(vel.y) ? vel.y += surplus : vel.y -= surplus;
            }
        }

        // x軸方向
        if (CheckHit(GetPos().y, GetSize().y, 0, i->GetPos().y, i->GetSize().y)) {
            if (CheckHit(GetPos().x, GetSize().x, vel.x, i->GetPos().x, i->GetSize().x, surplus)) {
                isPositive<float>(vel.x) ? vel.x += surplus : vel.x -= surplus;
            }
        }
    }
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize)
{
    // 値が0未満ならめり込んでる。
    return std::abs(pos - blockpos + vel) - (size / 2 + blocksize / 2) < 0;
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize, float& surplus)
{
    surplus = std::abs(pos - blockpos + vel) - (size / 2 + blocksize / 2);

    // 値が0未満ならめり込んでる。
    return surplus < 0;
}

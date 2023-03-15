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
    // �ړ���
    Vector2 vel{};

    // x��
    // ���E���͂̔���ƈړ��ʉ��Z
    vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A)) * moveSpeed_;

    // y��
    // �W�����v����
    Jump(vel);
    // �d��
    vel.y -= gravity_;

    // �ړ��ʕ␳
    Collision(vel);

    // �␳�ς̈ړ��ʂ�pos�ɉ��Z
    Vector2 pos{ GetPos() + vel };
    SetPos(pos);

}

void Player::Jump(Vector2& vel)
{
    static float jumpValue{ 0.f };

    // �g���K�[�ŃW�����v
    if (KEY::IsTrigger(KEY_INPUT_SPACE) && isJump_ == false) {
        isJump_ = true;
        jumpValue += jumpPower_;
    }

    // vel�ɃW�����v��(y���ړ���)�����Z
    vel.y += jumpValue;
    if (jumpValue > 0.f) {
        jumpValue -= fallValue_;
    }
    else if (jumpValue <= 0.f) {
        isJump_ = false;
    }

    // 0�����̒l�ɂȂ�Ȃ��B
    jumpValue = (std::max)(jumpValue, 0.f);
}

void Player::Collision(Vector2& vel)
{
    for (std::unique_ptr<IBlock>& i : StageManager::GetStage()->blocks_) {
        if (std::abs(i->GetPos().x - GetPos().x) > 5) continue;

        float surplus{};

        // x������
        if (CheckHit(GetPos().x, GetSize().x, vel.x, i->GetPos().x, i->GetSize().x, surplus)) {
            isPositive<float>(vel.x) ? vel.x + surplus : vel.x - surplus;
        }

        // y������
        if (CheckHit(GetPos().y, GetSize().y, vel.y, i->GetPos().y, i->GetSize().y, surplus)) {
            isPositive<float>(vel.y) ? vel.y + surplus : vel.y - surplus;
        }
    }
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize, float& surplus)
{
    surplus = std::abs(pos - blockpos + vel) - size / 2 + blocksize / 2;

    // �l��0�����Ȃ�߂荞��ł�B
    return surplus < 0;
}

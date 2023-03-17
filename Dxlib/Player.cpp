#include "Player.h"
#include "Input.h"
#include <DxLib.h>
#include "StageManager.h"
#include "Util.h"

using namespace Util::Math;
using KEY = Input::Keyboard;

Player::Player(const Vector2& pos, const Vector2& size, const Color& color)
{
    SetPos(pos);
    SetSize(size);
    SetColor(color);
    drawer_.Initialize(GetPosPtr(), GetSize(), GetColorValue());
}

Player::Player(const Vector2& pos, const Vector2& size, float moveSpeed, float jumpPower, float fallValue, float gravity, const Color& color)
{
    SetPos(pos);
    SetSize(size);
    moveSpeed_ = moveSpeed;
    jumpPower_ = jumpPower;
    fallValue_ = fallValue;
    gravity_ = gravity;
    SetColor(color);
    drawer_.Initialize(GetPosPtr(), GetSize(), GetColorValue());
}

void Player::Update(bool isInput)
{
    Move(isInput);
    drawer_.Update();
}

void Player::Draw(void)
{
    drawer_.Draw();

    //DrawBoxAA(GetPos().x - GetSize().x / 2, GetPos().y - GetSize().y / 2, GetPos().x + GetSize().x / 2, GetPos().y + GetSize().y / 2, 0xffffff, true);
    //DrawCircle((int)GetPos().x, (int)GetPos().y, 10, 0xff0000, 1, 1);

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

void Player::Move(bool isInput)
{
    // �ړ���
    Vector2 vel{};

    // x��
    // ���E���͂̔���ƈړ��ʉ��Z
    if (isInput) {
        vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A)) * moveSpeed_;

        // y��
        // �W�����v����
        Jump(vel);
    }
    // �d��
    vel.y += gravity_;

    //vel = vel.normalize();

    // �ړ��ʕ␳
    Collision(vel);

    //if (vel.y <= 0.f) isJump_ = false;

    // �␳�ς̈ړ��ʂ�pos�ɉ��Z
    Vector2 pos{ GetPos() + vel };
    SetPos(pos);
}

void Player::Jump(Vector2& vel)
{
    static float jumpValue{ 0.f };

    // �g���K�[�ŃW�����v
    if (KEY::IsTrigger(KEY_INPUT_SPACE) && isJump_ == false) { // �g���K�[ && �W�����v�t���O��OFF
        // �܂�������ւ̈ړ��ʂ��c���Ă���i0.f���傫���j�ꍇ�͖�����
        if (jumpValue > 0.f) jumpValue = 0.f; // �n�C�W�����v�i�o�O�j�̖�����

        // �W�����v�t���OON
        isJump_ = true;

        // ������ւ̈ړ��ʂ����Z
        jumpValue += jumpPower_;
    }

    // vel�ɃW�����v��(y���ړ���)�����Z
    vel.y -= jumpValue;

    // ������ւ̈ړ��ʂ��c���Ă���i0.f���傫���j�ꍇ
    if (jumpValue > 0.f) {
        // �ړ��ʂ������ʂ������Z
        jumpValue -= fallValue_;
    }

    // 0�����̒l�ɂȂ�Ȃ��B
    jumpValue = (std::max)(jumpValue, 0.f);
}

void Player::Collision(Vector2& vel)
{
    for (std::unique_ptr<IBlock>& i : StageManager::GetStage()->blocks_) {
        if (std::abs(i->GetPos().x - GetPos().x) > StageManager::defaultBlockSize_ * 3) {
            continue;
        }

        float surplus{};

        // y������
        if (CheckHit(GetPos().x, GetSize().x, 0, i->GetPos().x, i->GetSize().x)) {
            if (CheckHit(GetPos().y, GetSize().y, vel.y, i->GetPos().y, i->GetSize().y, surplus)) {
                // �߂荞��ł���ꍇ�A�߂荞��ł���ʂ����ړ��ʂ����炷�B�ꍇ�ɂ���Ă͉����o���B
                isPositive<float>(vel.y) ? vel.y += surplus, isJump_ = false : vel.y -= surplus;
                // ���d�͕�����"+"�����A�Q�Ɠn�������Ă���"surplus"�ɓ���l�͂߂荞��ł����ԂȂ�"-"�l������̂�"true = + surplus"�Ŗ��Ȃ�
            }
        }

        // x������
        if (CheckHit(GetPos().y, GetSize().y, 0, i->GetPos().y, i->GetSize().y)) {
            if (CheckHit(GetPos().x, GetSize().x, vel.x, i->GetPos().x, i->GetSize().x, surplus)) {
                isPositive<float>(vel.x) ? vel.x += surplus : vel.x -= surplus;
            }
        }
    }
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize)
{
    // �l��0�����Ȃ�߂荞��ł�B
    return std::abs(pos - blockpos + vel) - (size / 2 + blocksize / 2) < 0;
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize, float& surplus)
{
    surplus = std::abs(pos - blockpos + vel) - (size / 2 + blocksize / 2);

    // �l��0�����Ȃ�߂荞��ł�B
    return surplus < 0;
}

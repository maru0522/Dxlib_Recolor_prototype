#include "Player.h"
#include "Input.h"
#include <DxLib.h>
#include <memory>
#include "IBlock.h"
#include "StageManager.h"

Player::Player(const Vector2& pos, const Vector2& radius) :
    IEntity(pos,radius), isJump_(true)
{
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
    // �ړ���
    Vector2 vel{};

    // x��
    // ���E���͂̔���ƈړ��ʉ��Z
    vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A)) * moveSpeed_;

    // y��
    // �W�����v����
    Jump(vel);
    // �d��
    vel.y += gravity_;

    //vel = vel.normalize();

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
    vel.y -= jumpValue;
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
    Stage* stgPtr{ StageManager::GetInstance()->GetStagePtr() };

    for (size_t y = 0; y < stgPtr->mapchip_.size(); y++) {
        for (size_t x = 0; x < stgPtr->mapchip_[0].size(); x++)
        {
            
            if (stgPtr->mapchip_[y][x]->GetType() == IBlock::Type::NONE) continue;

            if (std::abs(stgPtr->mapchip_[y][x]->GetPos().x - GetPos().x) > (IBlock::defaultRadius_ * 2) * 3) {
                continue;
            }

            float surplus{};

            // y������
            if (CheckHit(GetPos().x, GetRadius().x, 0, stgPtr->mapchip_[y][x]->GetPos().x, stgPtr->mapchip_[y][x]->GetRadius().x)) {
                if (CheckHit(GetPos().y, GetRadius().y, vel.y, stgPtr->mapchip_[y][x]->GetPos().y, stgPtr->mapchip_[y][x]->GetRadius().y, surplus)) {
                    vel.y > 0 ? vel.y += surplus : vel.y -= surplus;
                }
            }

            // x������
            if (CheckHit(GetPos().y, GetRadius().y, 0, stgPtr->mapchip_[y][x]->GetPos().y, stgPtr->mapchip_[y][x]->GetRadius().y)) {
                if (CheckHit(GetPos().x, GetRadius().x, vel.x, stgPtr->mapchip_[y][x]->GetPos().x, stgPtr->mapchip_[y][x]->GetRadius().x, surplus)) {
                    vel.x > 0 ? vel.x += surplus : vel.x -= surplus;
                }
            }
        }
    }

    //for (IBlock* i : StageManager::GetInstance()->GetStagePtr()->blocks_) {
    //    if (std::abs(i->GetPos().x - GetPos().x) > (IBlock::defaultRadius_ * 2) * 3) {
    //        continue;
    //    }

    //    float surplus{};

    //    // y������
    //    if (CheckHit(GetPos().x, GetRadius().x, 0, i->GetPos().x, i->GetRadius().x)) {
    //        if (CheckHit(GetPos().y, GetRadius().y, vel.y, i->GetPos().y, i->GetRadius().y, surplus)) {
    //            vel.y > 0 ? vel.y += surplus : vel.y -= surplus;
    //        }
    //    }

    //    // x������
    //    if (CheckHit(GetPos().y, GetRadius().y, 0, i->GetPos().y, i->GetRadius().y)) {
    //        if (CheckHit(GetPos().x, GetRadius().x, vel.x, i->GetPos().x, i->GetRadius().x, surplus)) {
    //            vel.x > 0 ? vel.x += surplus : vel.x -= surplus;
    //        }
    //    }
    //}
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius)
{
    // �l��0�����Ȃ�߂荞��ł�B
    return std::abs(pos - blockpos + vel) - (radius + blockradius) < 0;
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus)
{
    surplus = std::abs(pos - blockpos + vel) - (radius + blockradius);

    // �l��0�����Ȃ�߂荞��ł�B
    return surplus < 0;
}

#include "Player.h"
#include <cmath>
#include "Input.h"
#include <DxLib.h>

Player::Player(Stage* stagePtr) :
    stagePtr_(stagePtr), radius_(defaultWidth_, defaultHeight_)
{
}

void Player::Update(void)
{
    Move();

    if (pos_.y > 600)pos_.y = 0;
}

void Player::Draw(void)
{
    DrawBox(GetPos().x - GetRadius().x, GetPos().y - GetRadius().y, GetPos().x + GetRadius().x, GetPos().y + GetRadius().y, 0xffffff, true);
    DrawCircle(GetPos().x, GetPos().y, 5, 0xff0000, 1, 1);
}

void Player::Move(void)
{
    // �ړ���
    Vector2 vel{};

    // x��
    // ���E���͂̔���ƈړ��ʉ��Z
    vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A)) * moveSpeed_;
    vel.y += (KEY::IsDown(KEY_INPUT_S) - KEY::IsDown(KEY_INPUT_W)) * moveSpeed_;

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
    for (size_t i = 0; i < stagePtr_->GetPieceVectorPtr()->size(); i++) {
        if (stagePtr_->GetPieceVectorPtr()->at(i)->GetOperator()) continue;

        for (size_t j = 0; j < stagePtr_->GetPieceVectorPtr()->at(i)->GetBlocksPtr()->size(); j++)
        {
            IBlock* tempBlockPtr{ stagePtr_->GetPieceVectorPtr()->at(i)->GetBlocksPtr()->at(j).get() };

            if (std::abs(tempBlockPtr->GetPos().x - GetPos().x) > IBlock::radiusBase_ * 6) continue;
            if (std::abs(tempBlockPtr->GetPos().y - GetPos().y) > IBlock::radiusBase_ * 6) continue;

            if (tempBlockPtr->GetType() == IBlock::Type::PIECEENTRANCE && stagePtr_->GetPieceVectorPtr()->at(i)->GetFixity()) {
                if (CheckHit(GetPos().x, GetRadius().x, 0, tempBlockPtr->GetPos().x, 8) &&
                    CheckHit(GetPos().y, GetRadius().y, 0, tempBlockPtr->GetPos().y, 8)) {
                    stagePtr_->GetPieceVectorPtr()->at(i)->SetState(Piece::State::IMMUTABLE);
                }

                if (tempBlockPtr->GetEntranceOpen()) 
                    continue;
            }

            float surplus{};

            // y������
            if (CheckHit(GetPos().x, GetRadius().x, 0, tempBlockPtr->GetPos().x, tempBlockPtr->GetRadius().x)) {
                if (CheckHit(GetPos().y, GetRadius().y, vel.y, tempBlockPtr->GetPos().y, tempBlockPtr->GetRadius().y, surplus)) {
                    vel.y > 0 ? vel.y += surplus : vel.y -= surplus;
                }
            }

            // x������
            if (CheckHit(GetPos().y, GetRadius().y, 0, tempBlockPtr->GetPos().y, tempBlockPtr->GetRadius().y)) {
                if (CheckHit(GetPos().x, GetRadius().x, vel.x, tempBlockPtr->GetPos().x, tempBlockPtr->GetRadius().x, surplus)) {
                    vel.x > 0 ? vel.x += surplus : vel.x -= surplus;
                }
            }
        }
    }
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

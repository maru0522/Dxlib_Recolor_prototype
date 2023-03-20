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

    sizeX_.left = size.x / 2.f;
    sizeX_.right = size.x / 2.f;
    sizeY_.top = size.y / 2.f;
    sizeY_.bottom = size.y / 2.f;

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

    sizeX_.left = size.x / 2.f;
    sizeX_.right = size.x / 2.f;
    sizeY_.top = size.y / 2.f;
    sizeY_.bottom = size.y / 2.f;

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
    DrawFormatString(0, 60, 0xffffff, "player_sizeX: (%f,%f)", sizeX_.left, sizeX_.right);
    DrawFormatString(0, 80, 0xffffff, "player_sizeY: (%f,%f)", sizeY_.top, sizeY_.bottom);
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

    // �㉺���E�p�ɐU��ꂽ�l��␳ sizeX/Y
    CheckFilterDistance();

    // �ړ��ʕ␳
    Collision(vel);

    //if (vel.y <= 0.f) isJump_ = false;

    // �␳�ς̈ړ��ʂ�pos�ɉ��Z
    Vector2 pos{ GetPos() + vel };
    SetPos(pos);

    if (GetPos().y > 800) SetPos({ GetPos().x,0.f });
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
        if (CheckHit(GetPos().x, { sizeX_.left,sizeX_.right }, 0, i->GetPos().x, i->GetSize().x)) {
            if (CheckHit(GetPos().y, { sizeY_.top,sizeY_.bottom }, vel.y, i->GetPos().y, i->GetSize().y, surplus)) {
                // �߂荞��ł���ꍇ�A�߂荞��ł���ʂ����ړ��ʂ����炷�B�ꍇ�ɂ���Ă͉����o���B
                isPositive<float>(vel.y) ? vel.y += surplus, isJump_ = false : vel.y -= surplus;
                // ���d�͕�����"+"�����A�Q�Ɠn�������Ă���"surplus"�ɓ���l�͂߂荞��ł����ԂȂ�"-"�l������̂�"true = + surplus"�Ŗ��Ȃ�
            }
        }

        // x������
        if (CheckHit(GetPos().y, { sizeY_.top,sizeY_.bottom }, 0, i->GetPos().y, i->GetSize().y)) {
            if (CheckHit(GetPos().x, { sizeX_.left,sizeX_.right }, vel.x, i->GetPos().x, i->GetSize().x, surplus)) {
                isPositive<float>(vel.x) ? vel.x += surplus : vel.x -= surplus;
            }
        }
    }
}

void Player::CheckFilterDistance(void)
{
    float comparePos{};
    float intrusion{};

    // --- x ---
    comparePos = GetPos().x - p_filter_->GetPos().x;
    // �ǂꂭ�炢player��filter���߂荞��ł��邩
    intrusion = std::abs(comparePos) - (GetSize().x / 2 + p_filter_->GetSize().x / 2);

    DrawFormatString(500, 400, 0xffffff, isNegative<float>(std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2 + p_filter_->GetSize().y / 2)) ? "bool_y: (true)" : "bool_y: (false)");
    // ���E�̏d�Ȃ�̑O�ɏ㉺���߂荞��ł邩��������B ������Ȃ��ƑS�͈͂ɂȂ����Ⴄ�����
    if (isNegative<float>(std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2 + p_filter_->GetSize().y / 2))) {
        if (isNegative<float>(intrusion)) {
            // player���猩��filter�̈ʒu ? �E : ��
            isNegative<float>(comparePos) ? sizeX_.right += intrusion : sizeX_.left += intrusion; // sizeX.value += intrusion(-value)

            if (isNegative<float>(sizeX_.right)) sizeX_.left += sizeX_.right;
            if (isNegative<float>(sizeX_.left)) sizeX_.right += sizeX_.left;

            sizeX_.right = (std::max)(sizeX_.right, 0.f);
            sizeX_.left = (std::max)(sizeX_.left, 0.f);
        }
        else { // �߂荞��ł��Ȃ��ꍇ�A��ɂ��Ƃ�size�l�ɕ␳
            sizeX_.right = GetSize().x / 2;
            sizeX_.left = GetSize().x / 2;
        }
    }
    else { // �߂荞��ł��Ȃ��ꍇ�A��ɂ��Ƃ�size�l�ɕ␳
        sizeX_.right = GetSize().x / 2;
        sizeX_.left = GetSize().x / 2;
    }

    // --- y ---
    comparePos = GetPos().y - p_filter_->GetPos().y;
    intrusion = std::abs(comparePos) - (GetSize().y / 2 + p_filter_->GetSize().y / 2);

    DrawFormatString(500, 420, 0xffffff, isNegative<float>(std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2 + p_filter_->GetSize().x / 2)) ? "bool_x: (true)" : "bool_x: (false)");
    // �㉺�̏d�Ȃ�̑O�ɍ��E���߂荞��ł邩��������B ������Ȃ��ƑS�͈͂ɂȂ����Ⴄ�����
    if (isNegative<float>(std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2 + p_filter_->GetSize().x / 2))) {
        if (isNegative<float>(intrusion)) {
            // player���猩��filter�̈ʒu ? �� : ��
            isNegative<float>(comparePos) ? sizeY_.bottom += intrusion : sizeY_.top += intrusion;

            if (isNegative<float>(sizeY_.bottom)) sizeY_.top += sizeY_.bottom;
            if (isNegative<float>(sizeY_.top)) sizeY_.bottom += sizeY_.top;

            sizeY_.bottom = (std::max)(sizeY_.bottom, 0.f);
            sizeY_.top = (std::max)(sizeY_.top, 0.f);
        }
        else { // �߂荞��ł��Ȃ��ꍇ�A��ɂ��Ƃ�size�l�ɕ␳
            sizeY_.bottom = GetSize().y / 2;
            sizeY_.top = GetSize().y / 2;
        }
    }
    else { // �߂荞��ł��Ȃ��ꍇ�A��ɂ��Ƃ�size�l�ɕ␳
        sizeY_.bottom = GetSize().y / 2;
        sizeY_.top = GetSize().y / 2;
    }

}

bool Player::CheckHit(float pos, const Vector2& size_tElem, float vel, float blockpos, float blocksize)
{
    float comparePos{ pos - blockpos };

    // player�ɑ΂���block�����E�ǂ���ɂ��邩
    if (isPositive<float>(comparePos)) { // filter�������߂̂���size�������������Ŕ��肹����𓾂�
        // �l��0�����Ȃ�߂荞��ł�B
        return std::abs(comparePos + vel) - (size_tElem.x + blocksize / 2) < 0; // size_tElem.x == sizeX_.left
    }
    else {
        // �l��0�����Ȃ�߂荞��ł�B
        return std::abs(comparePos + vel) - (size_tElem.y + blocksize / 2) < 0; // size_tElem.y == sizeX_.right
    }
}

bool Player::CheckHit(float pos, const Vector2& size_tElem, float vel, float blockpos, float blocksize, float& surplus)
{
    float comparePos{ pos - blockpos };

    // player�ɑ΂���block�����E�ǂ���ɂ��邩
    if (isPositive<float>(comparePos)) { // filter�������߂̂���size�������������Ŕ��肹����𓾂�
        surplus = std::abs(comparePos + vel) - (size_tElem.x + blocksize / 2); // size_tElem.x == sizeX_.left
    }
    else {
        surplus = std::abs(comparePos + vel) - (size_tElem.y + blocksize / 2); // size_tElem.y == sizeX_.right
    }

    // �l��0�����Ȃ�߂荞��ł�B
    return surplus < 0;
}

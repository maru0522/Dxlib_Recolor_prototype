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

    width_.fromL2R = size.x;
    width_.fromR2L = size.x;
    height_.fromT2B = size.y;
    height_.fromB2T = size.y;

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

    width_.fromL2R = size.x;
    width_.fromR2L = size.x;
    height_.fromT2B = size.y;
    height_.fromB2T = size.y;

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
    DrawFormatString(0, 60, 0xffffff, "player_width: fL2R(%f,%f)fR2L", width_.fromL2R, width_.fromR2L);
    DrawFormatString(0, 80, 0xffffff, "player_sizeY: fT2B(%f,%f)fB2T", height_.fromT2B, height_.fromB2T);
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

}

int32_t Player::FilterQuadrantFromPlayer(void)
{
    // ��1�ی�
    if (GetPos().x < p_filter_->GetPos().x && GetPos().y > p_filter_->GetPos().y) return 1;
    // ��2�ی�
    if (GetPos().x > p_filter_->GetPos().x && GetPos().y > p_filter_->GetPos().y) return 2;
    // ��3�ی�
    if (GetPos().x > p_filter_->GetPos().x && GetPos().y < p_filter_->GetPos().y) return 3;
    // ��4�ی�
    if (GetPos().x < p_filter_->GetPos().x && GetPos().y < p_filter_->GetPos().y) return 4;

    // ��O
    return 0;
}

void Player::CheckFilterDistance(void)
{
    // player.size.x < filter.size.x / 2 ���O��ƂȂ��Ă���v�Z�����������g�p����Ă��邱�Ƃ��ӎ����邱�ƁB

    float intrusion{};

    // --- x ---
    /*comparePos = GetPos().x - p_filter_->GetPos().x;*/
    // �ǂꂭ�炢player��filter���߂荞��ł��邩
    intrusion = std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2.f + p_filter_->GetSize().x / 2.f);

    DrawFormatString(500, 400, 0xffffff, isNegative<float>(std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2 + p_filter_->GetSize().y / 2)) ? "bool_y: (true)" : "bool_y: (false)");

    // ���E�̏d�Ȃ�̑O�ɏ㉺���߂荞��ł邩��������B ������Ȃ��ƑS�͈͂ɂȂ����Ⴄ�����
    if (isNegative<float>(std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2.f + p_filter_->GetSize().y / 2.f))) {
        // ���E�ł߂荞��ł�ꍇ
        if (isNegative<float>(intrusion)) {
            // player�̍��[(L2R�̌��_ == R2L�̏����l)���猩���Ƃ��Afilter�̒��S���E�ɂ���ꍇ�AL2R�̒l���߂荞��ł��镪�������炷
            if (GetPos().x - GetSize().x / 2.f < p_filter_->GetPos().x) width_.fromL2R = GetSize().x + intrusion;
            // player�̉E�[(R2L�̌��_ == L2R�̏����l)���猩���Ƃ��Afilter�̒��S�����ɂ���ꍇ�AR2L�̒l���߂荞��ł��镪�������炷
            if (GetPos().x + GetSize().x / 2.f > p_filter_->GetPos().x) width_.fromR2L = GetSize().x + intrusion;

            // ��ɒl��0�������Ȃ��B
            width_.fromL2R = (std::max)(width_.fromL2R, 0.f);
            width_.fromR2L = (std::max)(width_.fromR2L, 0.f);
        }
        else { // �߂荞��ł��Ȃ��ꍇ�A��ɂ��Ƃ�size�l�ɕ␳
            width_.fromL2R = GetSize().x;
            width_.fromR2L = GetSize().x;
        }
    }
    else { // �߂荞��ł��Ȃ��ꍇ�A��ɂ��Ƃ�size�l�ɕ␳
        width_.fromL2R = GetSize().x;
        width_.fromR2L = GetSize().x;
    }

    // --- y ---
    /*comparePos = GetPos().y - p_filter_->GetPos().y;*/
    // �ǂꂭ�炢player��filter���߂荞��ł��邩
    intrusion = std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2 + p_filter_->GetSize().y / 2);

    DrawFormatString(500, 420, 0xffffff, isNegative<float>(std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2 + p_filter_->GetSize().x / 2)) ? "bool_x: (true)" : "bool_x: (false)");

    // �㉺�̏d�Ȃ�̑O�ɍ��E���߂荞��ł邩��������B ������Ȃ��ƑS�͈͂ɂȂ����Ⴄ�����
    if (isNegative<float>(std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2 + p_filter_->GetSize().x / 2))) {
        // �㉺�ł߂荞��ł���ꍇ�B
        if (isNegative<float>(intrusion)) {
            // player�̏�[(T2B�̌��_ == B2T�̏����l)���猩���Ƃ��Afilter�̒��S�����ɂ���ꍇ�AT2B�̒l���߂荞��ł��镪�������炷
            if (GetPos().y - GetSize().y / 2.f < p_filter_->GetPos().y) height_.fromT2B = GetSize().y + intrusion;
            // player�̉��[(B2T�̌��_ == T2B�̏����l)���猩���Ƃ��Afilter�̒��S����ɂ���ꍇ�AB2T�̒l���߂荞��ł��镪�������炷
            if (GetPos().y + GetSize().y / 2.f > p_filter_->GetPos().y) height_.fromB2T = GetSize().y + intrusion;

            // ��ɒl��0�������Ȃ��B
            height_.fromT2B = (std::max)(height_.fromT2B, 0.f);
            height_.fromB2T = (std::max)(height_.fromB2T, 0.f);
        }
        else { // �߂荞��ł��Ȃ��ꍇ�A��ɂ��Ƃ�size�l�ɕ␳
            height_.fromT2B = GetSize().y;
            height_.fromB2T = GetSize().y;
        }
    }
    else { // �߂荞��ł��Ȃ��ꍇ�A��ɂ��Ƃ�size�l�ɕ␳
        height_.fromT2B = GetSize().y;
        height_.fromB2T = GetSize().y;
    }
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize, bool isFormer, float correct)
{
    float result{};

    isFormer ? result = pos - correct : result = pos + correct;

    // �l��0�����Ȃ�߂荞��ł�B
    return std::abs(result - blockpos + vel) - (size + blocksize / 2) < 0;
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize, float& surplus, bool isFormer, float correct)
{
    float result{};

    isFormer ? result = pos - correct : result = pos + correct;

    surplus = std::abs(result - blockpos + vel) - (size + blocksize / 2);

    // �l��0�����Ȃ�߂荞��ł�B
    return surplus < 0;
}

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
    // 移動量
    Vector2 vel{};

    // x軸
    // 左右入力の判定と移動量加算
    if (isInput) {
        vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A)) * moveSpeed_;

        // y軸
        // ジャンプ処理
        Jump(vel);
    }
    // 重力
    vel.y += gravity_;

    //vel = vel.normalize();

    // 上下左右用に振られた値を補正 sizeX/Y
    CheckFilterDistance();

    // 移動量補正
    Collision(vel);

    //if (vel.y <= 0.f) isJump_ = false;

    // 補正済の移動量をposに加算
    Vector2 pos{ GetPos() + vel };
    SetPos(pos);

    if (GetPos().y > 800) SetPos({ GetPos().x,0.f });
}

void Player::Jump(Vector2& vel)
{
    static float jumpValue{ 0.f };

    // トリガーでジャンプ
    if (KEY::IsTrigger(KEY_INPUT_SPACE) && isJump_ == false) { // トリガー && ジャンプフラグがOFF
        // まだ上方向への移動量が残っている（0.fより大きい）場合は無くす
        if (jumpValue > 0.f) jumpValue = 0.f; // ハイジャンプ（バグ）の無効化

        // ジャンプフラグON
        isJump_ = true;

        // 上方向への移動量を加算
        jumpValue += jumpPower_;
    }

    // velにジャンプ量(y軸移動量)を加算
    vel.y -= jumpValue;

    // 上方向への移動量が残っている（0.fより大きい）場合
    if (jumpValue > 0.f) {
        // 移動量を減衰量だけ減算
        jumpValue -= fallValue_;
    }

    // 0未満の値にならない。
    jumpValue = (std::max)(jumpValue, 0.f);
}

void Player::Collision(Vector2& vel)
{

}

int32_t Player::FilterQuadrantFromPlayer(void)
{
    // 第1象限
    if (GetPos().x < p_filter_->GetPos().x && GetPos().y > p_filter_->GetPos().y) return 1;
    // 第2象限
    if (GetPos().x > p_filter_->GetPos().x && GetPos().y > p_filter_->GetPos().y) return 2;
    // 第3象限
    if (GetPos().x > p_filter_->GetPos().x && GetPos().y < p_filter_->GetPos().y) return 3;
    // 第4象限
    if (GetPos().x < p_filter_->GetPos().x && GetPos().y < p_filter_->GetPos().y) return 4;

    // 例外
    return 0;
}

void Player::CheckFilterDistance(void)
{
    // player.size.x < filter.size.x / 2 が前提となっている計算式が数多く使用されていることを意識すること。

    float intrusion{};

    // --- x ---
    /*comparePos = GetPos().x - p_filter_->GetPos().x;*/
    // どれくらいplayerにfilterがめり込んでいるか
    intrusion = std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2.f + p_filter_->GetSize().x / 2.f);

    DrawFormatString(500, 400, 0xffffff, isNegative<float>(std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2 + p_filter_->GetSize().y / 2)) ? "bool_y: (true)" : "bool_y: (false)");

    // 左右の重なりの前に上下がめり込んでるかだけ判定。 ※じゃないと全範囲になっちゃうもんね
    if (isNegative<float>(std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2.f + p_filter_->GetSize().y / 2.f))) {
        // 左右でめり込んでる場合
        if (isNegative<float>(intrusion)) {
            // playerの左端(L2Rの原点 == R2Lの初期値)から見たとき、filterの中心が右にある場合、L2Rの値をめり込んでいる分だけ減らす
            if (GetPos().x - GetSize().x / 2.f < p_filter_->GetPos().x) width_.fromL2R = GetSize().x + intrusion;
            // playerの右端(R2Lの原点 == L2Rの初期値)から見たとき、filterの中心が左にある場合、R2Lの値をめり込んでいる分だけ減らす
            if (GetPos().x + GetSize().x / 2.f > p_filter_->GetPos().x) width_.fromR2L = GetSize().x + intrusion;

            // 常に値は0を下回らない。
            width_.fromL2R = (std::max)(width_.fromL2R, 0.f);
            width_.fromR2L = (std::max)(width_.fromR2L, 0.f);
        }
        else { // めり込んでいない場合、常にもとのsize値に補正
            width_.fromL2R = GetSize().x;
            width_.fromR2L = GetSize().x;
        }
    }
    else { // めり込んでいない場合、常にもとのsize値に補正
        width_.fromL2R = GetSize().x;
        width_.fromR2L = GetSize().x;
    }

    // --- y ---
    /*comparePos = GetPos().y - p_filter_->GetPos().y;*/
    // どれくらいplayerにfilterがめり込んでいるか
    intrusion = std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2 + p_filter_->GetSize().y / 2);

    DrawFormatString(500, 420, 0xffffff, isNegative<float>(std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2 + p_filter_->GetSize().x / 2)) ? "bool_x: (true)" : "bool_x: (false)");

    // 上下の重なりの前に左右がめり込んでるかだけ判定。 ※じゃないと全範囲になっちゃうもんね
    if (isNegative<float>(std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2 + p_filter_->GetSize().x / 2))) {
        // 上下でめり込んでいる場合。
        if (isNegative<float>(intrusion)) {
            // playerの上端(T2Bの原点 == B2Tの初期値)から見たとき、filterの中心が下にある場合、T2Bの値をめり込んでいる分だけ減らす
            if (GetPos().y - GetSize().y / 2.f < p_filter_->GetPos().y) height_.fromT2B = GetSize().y + intrusion;
            // playerの下端(B2Tの原点 == T2Bの初期値)から見たとき、filterの中心が上にある場合、B2Tの値をめり込んでいる分だけ減らす
            if (GetPos().y + GetSize().y / 2.f > p_filter_->GetPos().y) height_.fromB2T = GetSize().y + intrusion;

            // 常に値は0を下回らない。
            height_.fromT2B = (std::max)(height_.fromT2B, 0.f);
            height_.fromB2T = (std::max)(height_.fromB2T, 0.f);
        }
        else { // めり込んでいない場合、常にもとのsize値に補正
            height_.fromT2B = GetSize().y;
            height_.fromB2T = GetSize().y;
        }
    }
    else { // めり込んでいない場合、常にもとのsize値に補正
        height_.fromT2B = GetSize().y;
        height_.fromB2T = GetSize().y;
    }
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize, bool isFormer, float correct)
{
    float result{};

    isFormer ? result = pos - correct : result = pos + correct;

    // 値が0未満ならめり込んでる。
    return std::abs(result - blockpos + vel) - (size + blocksize / 2) < 0;
}

bool Player::CheckHit(float pos, float size, float vel, float blockpos, float blocksize, float& surplus, bool isFormer, float correct)
{
    float result{};

    isFormer ? result = pos - correct : result = pos + correct;

    surplus = std::abs(result - blockpos + vel) - (size + blocksize / 2);

    // 値が0未満ならめり込んでる。
    return surplus < 0;
}

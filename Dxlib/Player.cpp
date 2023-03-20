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
    for (std::unique_ptr<IBlock>& i : StageManager::GetStage()->blocks_) {
        if (std::abs(i->GetPos().x - GetPos().x) > StageManager::defaultBlockSize_ * 3) {
            continue;
        }

        float surplus{};

        // y軸方向
        if (CheckHit(GetPos().x, { sizeX_.left,sizeX_.right }, 0, i->GetPos().x, i->GetSize().x)) {
            if (CheckHit(GetPos().y, { sizeY_.top,sizeY_.bottom }, vel.y, i->GetPos().y, i->GetSize().y, surplus)) {
                // めり込んでいる場合、めり込んでいる量だけ移動量を減らす。場合によっては押し出す。
                isPositive<float>(vel.y) ? vel.y += surplus, isJump_ = false : vel.y -= surplus;
                // ※重力方向が"+"だが、参照渡しをしている"surplus"に入る値はめり込んでいる状態なら"-"値が入るので"true = + surplus"で問題ない
            }
        }

        // x軸方向
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
    // どれくらいplayerにfilterがめり込んでいるか
    intrusion = std::abs(comparePos) - (GetSize().x / 2 + p_filter_->GetSize().x / 2);

    DrawFormatString(500, 400, 0xffffff, isNegative<float>(std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2 + p_filter_->GetSize().y / 2)) ? "bool_y: (true)" : "bool_y: (false)");
    // 左右の重なりの前に上下がめり込んでるかだけ判定。 ※じゃないと全範囲になっちゃうもんね
    if (isNegative<float>(std::abs(GetPos().y - p_filter_->GetPos().y) - (GetSize().y / 2 + p_filter_->GetSize().y / 2))) {
        if (isNegative<float>(intrusion)) {
            // playerから見たfilterの位置 ? 右 : 左
            isNegative<float>(comparePos) ? sizeX_.right += intrusion : sizeX_.left += intrusion; // sizeX.value += intrusion(-value)

            if (isNegative<float>(sizeX_.right)) sizeX_.left += sizeX_.right;
            if (isNegative<float>(sizeX_.left)) sizeX_.right += sizeX_.left;

            sizeX_.right = (std::max)(sizeX_.right, 0.f);
            sizeX_.left = (std::max)(sizeX_.left, 0.f);
        }
        else { // めり込んでいない場合、常にもとのsize値に補正
            sizeX_.right = GetSize().x / 2;
            sizeX_.left = GetSize().x / 2;
        }
    }
    else { // めり込んでいない場合、常にもとのsize値に補正
        sizeX_.right = GetSize().x / 2;
        sizeX_.left = GetSize().x / 2;
    }

    // --- y ---
    comparePos = GetPos().y - p_filter_->GetPos().y;
    intrusion = std::abs(comparePos) - (GetSize().y / 2 + p_filter_->GetSize().y / 2);

    DrawFormatString(500, 420, 0xffffff, isNegative<float>(std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2 + p_filter_->GetSize().x / 2)) ? "bool_x: (true)" : "bool_x: (false)");
    // 上下の重なりの前に左右がめり込んでるかだけ判定。 ※じゃないと全範囲になっちゃうもんね
    if (isNegative<float>(std::abs(GetPos().x - p_filter_->GetPos().x) - (GetSize().x / 2 + p_filter_->GetSize().x / 2))) {
        if (isNegative<float>(intrusion)) {
            // playerから見たfilterの位置 ? 下 : 上
            isNegative<float>(comparePos) ? sizeY_.bottom += intrusion : sizeY_.top += intrusion;

            if (isNegative<float>(sizeY_.bottom)) sizeY_.top += sizeY_.bottom;
            if (isNegative<float>(sizeY_.top)) sizeY_.bottom += sizeY_.top;

            sizeY_.bottom = (std::max)(sizeY_.bottom, 0.f);
            sizeY_.top = (std::max)(sizeY_.top, 0.f);
        }
        else { // めり込んでいない場合、常にもとのsize値に補正
            sizeY_.bottom = GetSize().y / 2;
            sizeY_.top = GetSize().y / 2;
        }
    }
    else { // めり込んでいない場合、常にもとのsize値に補正
        sizeY_.bottom = GetSize().y / 2;
        sizeY_.top = GetSize().y / 2;
    }

}

bool Player::CheckHit(float pos, const Vector2& size_tElem, float vel, float blockpos, float blocksize)
{
    float comparePos{ pos - blockpos };

    // playerに対してblockが左右どちらにいるか
    if (isPositive<float>(comparePos)) { // filter部分透過のためsize分割したせいで判定せざるを得ん
        // 値が0未満ならめり込んでる。
        return std::abs(comparePos + vel) - (size_tElem.x + blocksize / 2) < 0; // size_tElem.x == sizeX_.left
    }
    else {
        // 値が0未満ならめり込んでる。
        return std::abs(comparePos + vel) - (size_tElem.y + blocksize / 2) < 0; // size_tElem.y == sizeX_.right
    }
}

bool Player::CheckHit(float pos, const Vector2& size_tElem, float vel, float blockpos, float blocksize, float& surplus)
{
    float comparePos{ pos - blockpos };

    // playerに対してblockが左右どちらにいるか
    if (isPositive<float>(comparePos)) { // filter部分透過のためsize分割したせいで判定せざるを得ん
        surplus = std::abs(comparePos + vel) - (size_tElem.x + blocksize / 2); // size_tElem.x == sizeX_.left
    }
    else {
        surplus = std::abs(comparePos + vel) - (size_tElem.y + blocksize / 2); // size_tElem.y == sizeX_.right
    }

    // 値が0未満ならめり込んでる。
    return surplus < 0;
}

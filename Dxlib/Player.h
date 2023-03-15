#pragma once
#include "IEntity.h"
#include "IColor.h"
#include "StageManager.h"
#include "staging/PlayerDrawer.h"

class Player : public IEntity, public IColor
{
public:
    // 定数
    static constexpr uint32_t defaultWidth_{ 16 };
    static constexpr uint32_t defaultHeight_{ 64 };
    static constexpr float moveSpeed_{ 3.f };       // 移動速度
    static constexpr float jumpPower_{ 7.f };       // ジャンプ力
    static constexpr float fallValue_{ 0.2f };      // ジャンプ力の減衰
    static constexpr float gravity_{ 3.5f };      // 重力

    // 関数
    Player(const Vector2 pos, const Vector2 size, const Color color);

    void Update(void);
    void Draw(void);

    void DisplayDebug(void);

private:
    void Move(void);
    void Jump(Vector2& vel);

    void Collision(Vector2& vel);
    bool CheckHit(float pos, float size, float vel, float blockpos, float blocksize);
    bool CheckHit(float pos, float size, float vel, float blockpos, float blocksize, float& surplus);

    // 変数
    bool isJump_{ true };
    PlayerDrawer drawer_{};
};
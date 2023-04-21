#pragma once
#include "IEntity.h"
#include "Vector2.h"

class Player : public IEntity
{
public:
    // 定数
    static constexpr float moveSpeed_{ 3.f };       // 移動速度
    static constexpr float jumpPower_{ 7.f };       // ジャンプ力
    static constexpr float fallValue_{ 0.2f };      // ジャンプ力の減衰
    static constexpr float gravity_{ 3.5f };        // 重力

    // 関数
    Player(const Vector2& pos, const Vector2& radius);
    void Update(void);
    void Draw(void);

private:
    void Move(void);
    void Jump(Vector2& vel);

    void Collision(Vector2& vel);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus);

    // 変数
    bool isJump_;
};


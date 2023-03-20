#pragma once
#include "IEntity.h"
#include "IColor.h"
#include "StageManager.h"
#include "staging/PlayerDrawer.h"
#include "Filter.h"

class Player : public IEntity, public IColor
{
private:
    // 定義
    struct SizeX_t
    {
        float left{};
        float right{};
    };

    struct SizeY_t
    {
        float top{};
        float bottom{};
    };

public:
    // 定数
    static constexpr uint32_t defaultSizeX_{ 16 };
    static constexpr uint32_t defaultSizeY_{ 64 };

    // 関数
    Player(const Vector2& pos, const Vector2& size, const Color& color);
    Player(const Vector2& pos, const Vector2& size, float moveSpeed, float jumpPower, float fallValue, float gravity, const Color& color);

    void Update(bool isInput);
    void Draw(void) override;

    void DisplayDebug(void);

    inline void SetFilterPtr(Filter* p_filter) { p_filter_ = p_filter; }
private:
    void Move(bool isInput);
    void Jump(Vector2& vel);

    void Collision(Vector2& vel);
    void CheckFilterDistance(void);
    bool CheckHit(float pos, const Vector2& size_tElem, float vel, float blockpos, float blocksize);
    bool CheckHit(float pos, const Vector2& size_tElem, float vel, float blockpos, float blocksize, float& surplus);

    // 変数
    PlayerDrawer drawer_{};
    Filter* p_filter_{ nullptr };

    bool isJump_{ true };
    bool isInsideFilter_{ false };

    float moveSpeed_{ 3.f };       // 移動速度
    float jumpPower_{ 7.f };       // ジャンプ力
    float fallValue_{ 0.2f };      // ジャンプ力の減衰
    float gravity_{ 3.5f };        // 重力
    
    SizeX_t sizeX_{};
    SizeY_t sizeY_{};
};
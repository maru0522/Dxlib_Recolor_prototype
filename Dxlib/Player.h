#pragma once
#include "IEntity.h"
#include "IColor.h"
#include "StageManager.h"
#include "staging/PlayerDrawer.h"

class Player : public IEntity, public IColor
{
public:
    // �萔
    static constexpr uint32_t defaultSizeX_{ 16 };
    static constexpr uint32_t defaultSizeY_{ 64 };

    // �֐�
    Player(const Vector2& pos, const Vector2& size, const Color& color);
    Player(const Vector2& pos, const Vector2& size, float moveSpeed, float jumpPower, float fallValue, float gravity, const Color& color);

    void Update(bool isInput);
    void Draw(void) override;

    void DisplayDebug(void);

private:
    void Move(bool isInput);
    void Jump(Vector2& vel);

    void Collision(Vector2& vel);
    bool CheckHit(float pos, float size, float vel, float blockpos, float blocksize);
    bool CheckHit(float pos, float size, float vel, float blockpos, float blocksize, float& surplus);

    // �ϐ�
    PlayerDrawer drawer_{};
    bool isJump_{ true };
    //bool isJumpValue_{ false };

    float moveSpeed_{ 3.f };       // �ړ����x
    float jumpPower_{ 7.f };       // �W�����v��
    float fallValue_{ 0.2f };      // �W�����v�͂̌���
    float gravity_{ 3.5f };        // �d��
};
#pragma once
#include "IEntity.h"
#include "IColor.h"
#include "StageManager.h"

class Player : public IEntity, public IColor
{
public:
    // �萔
    static constexpr uint32_t defaultWidth_{ 16 };
    static constexpr uint32_t defaultHeight_{ 64 };
    static constexpr float moveSpeed_{ 2.f };       // �ړ����x
    static constexpr float jumpPower_{ 2.f };       // �W�����v��
    static constexpr float fallValue_{ 0.5f };      // �W�����v�͂̌���
    static constexpr float gravity_{ 0.9f };      // �d��

    // �֐�
    Player(const Vector2 pos, const Vector2 size, const Color color);

    void Update(void);
    void Draw(void);

private:
    void Move(void);
    void Jump(Vector2& vel);

    void Collision(Vector2& vel);
    bool CheckHit(float pos, float size, float vel, float blockpos, float blocksize, float& surplus);

    // �ϐ�
    bool isJump_{ true };
};
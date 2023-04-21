#pragma once
#include "IEntity.h"
#include "Vector2.h"

class Player : public IEntity
{
public:
    // �萔
    static constexpr float moveSpeed_{ 3.f };       // �ړ����x
    static constexpr float jumpPower_{ 7.f };       // �W�����v��
    static constexpr float fallValue_{ 0.2f };      // �W�����v�͂̌���
    static constexpr float gravity_{ 3.5f };        // �d��

    // �֐�
    Player(const Vector2& pos, const Vector2& radius);
    void Update(void);
    void Draw(void);

private:
    void Move(void);
    void Jump(Vector2& vel);

    void Collision(Vector2& vel);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus);

    // �ϐ�
    bool isJump_;
};


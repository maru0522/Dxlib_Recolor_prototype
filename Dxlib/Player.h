#pragma once
#include "Vector2.h"
#include "Stage.h"

class Player
{
public:
    // �萔
    static constexpr uint32_t defaultWidth_{ 4 };
    static constexpr uint32_t defaultHeight_{ 8 };
    static constexpr float moveSpeed_{ 3.f };       // �ړ����x
    static constexpr float jumpPower_{ 10.f };       // �W�����v��
    static constexpr float fallValue_{ 0.2f };      // �W�����v�͂̌���
    static constexpr float gravity_{ 3.5f };        // �d��

    // �֐�
    Player(Stage* stagePtr);
    void Update(void);
    void Draw(void);

private:
    void Move(void);
    void Jump(Vector2& vel);

    void Collision(Vector2& vel);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius);
    bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus);

    // �ϐ�
    Vector2 pos_{};
    Vector2 radius_{};
    Vector2 offsetForPieceCenter_{};

    bool isJump_{ true };

    Stage* stagePtr_;
    size_t indexPiecePlayerInside_{};

public:
    // setter�Egetter
    inline void SetPos(const Vector2& pos) { pos_ = pos; };
    inline void SetRadius(const Vector2& radius) { radius_ = radius; };
    inline void SetIndexPiece(size_t index) { indexPiecePlayerInside_ = index; }
    inline void SetOffset(const Vector2& offset) { offsetForPieceCenter_ = offset; }

    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetRadius(void) { return radius_; }
    inline Vector2* GetPosPtr(void) { return &pos_; }
    inline size_t GetIndexPiece(void) { return indexPiecePlayerInside_; }
    inline const Vector2& GetOffset(void) { return offsetForPieceCenter_; }

};


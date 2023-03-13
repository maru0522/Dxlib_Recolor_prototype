#pragma once
#include "IEntity.h"
#include "IColor.h"

class Player : public IEntity, public IColor
{
public:
    // íËêî
    static constexpr uint32_t defaultWidth_{ 16 };
    static constexpr uint32_t defaultHeight_{ 64 };
    static constexpr float moveSpeed_{ 2.f };

    // ä÷êî
    Player(const Vector2 pos, const Vector2 size, const Color color);

    void Update(void);
    void Draw(void);

private:
    void Move(void);
};


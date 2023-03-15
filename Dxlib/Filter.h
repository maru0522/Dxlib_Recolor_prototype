#pragma once
#include "IEntity.h"
#include "IColor.h"
#include "staging/FillterDrawer.h"

class Filter :
    public IEntity, public IColor
{
public:
    // �萔
    static constexpr float defaultSizeX_{ 160 };
    static constexpr float defaultSizeY_{ 80 };
    static constexpr float moveSpeed_{ 3.f };

    // �֐�
    Filter(const Vector2& pos, const Vector2& size, const Color& color);

    void Update(void) override;
    void Draw(void) override;

    void DisplayDebug(void);

private:
    void Move(void);

    // �ϐ�
    FillterDrawer drawer_{};
};


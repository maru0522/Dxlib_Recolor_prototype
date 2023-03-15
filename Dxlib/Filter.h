#pragma once
#include "IEntity.h"
#include "IColor.h"
#include "staging/FillterDrawer.h"

class Filter :
    public IEntity, public IColor
{
public:
    // 定数
    static constexpr float defaultSizeX_{ 160 };
    static constexpr float defaultSizeY_{ 80 };
    static constexpr float moveSpeed_{ 3.f };

    // 関数
    Filter(const Vector2& pos, const Vector2& size, const Color& color);

    void Update(void) override;
    void Draw(void) override;

    void DisplayDebug(void);

private:
    void Move(void);

    // 変数
    FillterDrawer drawer_{};
};


#pragma once
#include "IEntity.h"
#include "IColor.h"
#include "staging/FillterDrawer.h"

class Filter :
    public IEntity, public IColor
{
public:
    // íËêî
    static constexpr float defaultSizeX_{ 160 };
    static constexpr float defaultSizeY_{ 80 };

    // ä÷êî
    Filter(const Vector2& pos, const Vector2& size, const Color& color);
    Filter(const Vector2& pos, const Vector2& size, float moveSpeed, const Color& color);

    void Update(bool isInput);
    void Draw(void) override;

    void DisplayDebug(void);

private:
    void Move(bool isInput);

    // ïœêî
    FillterDrawer drawer_{};

    float moveSpeed_{ 3.f };
};


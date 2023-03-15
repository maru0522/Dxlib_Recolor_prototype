#pragma once
#include "IEntity.h"
#include "IColor.h"

class Filter :
    public IEntity, public IColor
{
public:
    // �萔
    static constexpr float defaultSizeX_{ 80 };
    static constexpr float defaultSizeY_{ 320 };

    // �֐�
    Filter(const Vector2& pos, const Vector2& size, const Color& color);

    void Update(void) override;
    void Draw(void) override;

    void DisplayDebug(void);
};


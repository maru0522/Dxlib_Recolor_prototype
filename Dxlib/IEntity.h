#pragma once
#include "Vector2.h"

class IEntity
{
public:
    IEntity(void) = default;
    virtual ~IEntity(void) = default;

    inline void SetPos(const Vector2 & pos) { pos_ = pos; };
    inline void SetRadius(const Vector2 & size) { radius_ = size; };

    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetRadius(void) { return radius_; }
    inline Vector2* GetPosPtr(void) { return &pos_; }

private:
    Vector2 pos_{};
    Vector2 radius_{};
};


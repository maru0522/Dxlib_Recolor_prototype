#pragma once
#include "Vector2.h"

class IEntity
{
public:
    IEntity(const Vector2& pos, const Vector2& radius) : pos_(pos), radius_(radius) {};
    virtual ~IEntity(void) = default;

    inline void SetPos(const Vector2& pos) { pos_ = pos; };
    inline void SetRadius(const Vector2& size) { radius_ = size; };

    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetRadius(void) { return radius_; }
    inline Vector2* GetPosPtr(void) { return &pos_; }

private:
    Vector2 pos_{ 0.f,0.f };
    Vector2 radius_{ 0.f,0.f };
};


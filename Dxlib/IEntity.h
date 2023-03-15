#pragma once
#include "Vector2.h"

class IEntity
{
public:
    // ä÷êî
    virtual ~IEntity(void) = default;

    virtual void Update(void) = 0;
    virtual void Draw(void) = 0;

    inline void SetPos(const Vector2& pos) { pos_ = pos; };
    inline void SetSize(const Vector2& size) { size_ = size; };

    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetSize(void) { return size_; }
    inline Vector2* GetPosPtr(void) { return &pos_; }

private:
    // ïœêî
    Vector2 pos_{};
    Vector2 size_{};
};


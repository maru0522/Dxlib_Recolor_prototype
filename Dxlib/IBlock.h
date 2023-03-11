#pragma once
#include <array>
#include "Vector2.h"

class IBlock
{
public:
    // íËã`
    enum class Type
    {
        NONE,
        STONE,
        COLORED,
    };

    // ä÷êî
    virtual ~IBlock(void) = default;

    virtual void Update(void) = 0;
    virtual void Draw(void) = 0;

    inline void SetPos(const Vector2& pos) { pos_ = pos; };
    inline void SetSize(const Vector2& size) { size_ = size; };
    inline void SetBlockType(Type id) { type_ = id; }

    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetSize(void) { return size_; }

private:
    // ïœêî
    Vector2 pos_{ 0.f,0.f };
    Vector2 size_{ 16.f,16.f };
    Type type_{ Type::NONE };
};


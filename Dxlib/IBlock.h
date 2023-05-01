#pragma once
#include "Vector2.h"
#include <DxLib.h>

class IBlock
{
public:
    // íËã`
    enum class Type
    {
        NONE,
        PIECEBASIC,
        PIECEENTRANCE,
        BASIC,
        PLATFORM,
        OBJECT,
    };

    static constexpr float radiusBase_{ 16.f };

    // ä÷êî
    IBlock(const Vector2& pos, const Vector2& radius = { radiusBase_,radiusBase_ });
    virtual ~IBlock(void) = default;

    virtual void Update(void);
    virtual void Draw(void);

private:
    // ïœêî
    Type type_;

    Vector2 pos_;
    Vector2 radius_;

    int rotate_;

public:
    // setterÅEgetter
    inline void SetType(const Type& type) { type_ = type; }
    inline void SetPos(const Vector2& pos) { pos_ = pos; }
    //inline void SetOffset(const Vector2& offset) { offsetPiecePos_ = offset; }
    inline void SetRadius(const Vector2& radius) { radius_ = radius; }
    inline void SetRotate(int rotate) { rotate = rotate; }

    inline const Type& GetType(void) { return type_; }
    inline const Vector2& GetPos(void) { return pos_; }
    //inline const Vector2& GetOffset(void) { return offsetPiecePos_; }
    inline const Vector2& GetRadius(void) { return radius_; }
    inline int GetRotate(void) { return rotate_; }
};


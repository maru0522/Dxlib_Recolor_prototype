#pragma once
#include "Vector2.h"
#include <DxLib.h>

class IBlock
{
public:
    // 定義
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

    // 関数
    IBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius = { radiusBase_,radiusBase_ });
    virtual ~IBlock(void) = default;

    virtual void Update(void);
    virtual void Draw(void);

private:
    // 変数
    Type type_;

    Vector2 pos_;
    Vector2 radius_;
    Vector2 offset_;

    int rotate_;

    bool isEntranceOpen_{};

public:
    // setter・getter
    inline void SetEntranceOpen(bool inPiece) { isEntranceOpen_ = inPiece; }

    inline bool GetEntranceOpen(void) { return isEntranceOpen_; }

    inline void SetType(const Type& type) { type_ = type; }
    inline void SetPos(const Vector2& pos) { pos_ = pos; }
    inline void SetOffset(const Vector2& offset) { offset_ = offset; }
    inline void SetRadius(const Vector2& radius) { radius_ = radius; }
    inline void SetRotate(int rotate) { rotate = rotate; }

    inline const Type& GetType(void) { return type_; }
    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetOffset(void) { return offset_; }
    inline const Vector2& GetRadius(void) { return radius_; }
    inline int GetRotate(void) { return rotate_; }
};


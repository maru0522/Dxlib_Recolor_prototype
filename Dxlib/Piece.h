#pragma once
#include "IBlock.h"
#include <list>
#include <memory>

class Piece
{
public:
    // 関数
    Piece(const Vector2& pos, const Vector2& radius);
    
    void Update(void);
    void Draw(void);

    void Register(IBlock* ptr);

private:
    // 変数
    std::list<std::unique_ptr<IBlock>> blockList_;

    Vector2 pos_;
    Vector2 radius_;

    int rotate_;

    // 各方向への凹凸の有無 >> true ならでっぱってる
    bool isTabTop_; 
    bool isTabRight_;
    bool isTabLeft_;
    bool isTabBottom_;

    // はめ込まれているかどうか
    bool isInPlace_;

public:
    // setter・getter
    inline void SetPos(const Vector2& pos) { pos_ = pos; }
    inline void SetRadius(const Vector2& radius) { radius_ = radius; }
    inline void SetRotate(int rotate) { rotate = rotate; }

    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetRadius(void) { return radius_; }
    inline int GetRotate(void) { return rotate_; }
};


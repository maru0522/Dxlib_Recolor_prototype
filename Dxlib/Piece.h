#pragma once
#include "IBlock.h"
#include <list>
#include <vector>
#include <memory>

class Piece
{
public:
    // 定義
    enum class Dir
    {
        TOP,
        RIGHT,
        LEFT,
        BOTTOM,
    };

    struct Tab_t
    {
        bool isTab_{};
        Vector2 pos_{};
        Dir dir_{};
        size_t indexBlockVector_{};
    };

    // 関数
    Piece(const Vector2& pos, const Vector2& radiusBlockCount);
    
    // Tabをすべて追加してから行うこと。
    void Initialize(void);
    void Update(void);
    void Draw(void);

    void RegisterBlock(IBlock* ptr);
    void RegisterTab(bool isTab, int indexBlockVector,const Dir& dir);

private:
    void ChangeTabsDir(int changeValue);
    void RotateBlocks(int rotateValue);

    // 変数
    std::vector<std::unique_ptr<IBlock>> blockVector_;

    // 中心点
    Vector2 pos_;
    // 中心点を1ブロックとして、何ブロック分伸ばすか
    Vector2 radiusBlockCount_;

    int rotate_;

    std::vector<Tab_t> tabs_;

    // はめ込まれているかどうか
    bool isInPlace_;

public:
    // setter・getter
    inline void SetPos(const Vector2& pos) { pos_ = pos; }
    inline void SetRadius(const Vector2& radius) { radiusBlockCount_ = radius; }
    inline void SetRotate(int rotate) { rotate = rotate; }

    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetRadius(void) { return radiusBlockCount_; }
    inline int GetRotate(void) { return rotate_; }
};


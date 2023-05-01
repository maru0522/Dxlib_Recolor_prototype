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

    void Update(void);
    void Draw(void);

    void RegisterBlock(IBlock* ptr);
    void RegisterTab(bool isTab, int indexBlockVector,const Dir& dir); // PieceEntranceBlockの追加関数

private:
    void ChangeTabsDir(int changeValue); // tabs_回転時情報更新用関数
    void RotateBlocks(int rotateValue); // 全ブロック回転時更新関数
    void MoveBlocks(const Vector2& moveValue); // 全ブロック移動時更新関数

    void UpdateTabs(void); // 全ブロック移動時tabs_情報更新関数
    void WriteBlockPos(void);

    // 変数
    std::vector<std::unique_ptr<IBlock>> blockVector_;

    // 中心点
    Vector2 pos_;
    // 中心点を1ブロックとして、何ブロック分伸ばすか
    Vector2 radiusBlockCount_;

    int rotate_;

    std::vector<Tab_t> tabs_;

    /// ↓↓↓debgu_info
    // はめ込まれているかどうか
    bool isInPlace_;

    bool isOperator_{};

public:
    // setter・getter
    inline void SetPos(const Vector2& pos) { pos_ = pos; }
    inline void SetRadius(const Vector2& radius) { radiusBlockCount_ = radius; }
    inline void SetRotate(int rotate) { rotate = rotate; }
    inline void SetOperator(bool isOperator) { isOperator_ = isOperator; }

    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetRadius(void) { return radiusBlockCount_; }
    inline int GetRotate(void) { return rotate_; }
    inline const std::vector<std::unique_ptr<IBlock>>* GetBlocksPtr(void) { return &blockVector_; }
    inline const std::vector<Tab_t>& GetTabs(void) { return tabs_; }
    inline bool GetOperator(void) { return isOperator_; }
};


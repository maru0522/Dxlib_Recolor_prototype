#pragma once
#include "IBlock.h"
#include <list>
#include <vector>
#include <memory>

class Piece
{
public:
    // ��`
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

    // �֐�
    Piece(const Vector2& pos, const Vector2& radiusBlockCount);
    
    // Tab�����ׂĒǉ����Ă���s�����ƁB
    void Update(void);
    void Draw(void);

    void RegisterBlock(IBlock* ptr);
    void RegisterTab(bool isTab, int indexBlockVector,const Dir& dir);

    void SetMove(bool isMove) { isMove_ = isMove; }

private:
    void ChangeTabsDir(int changeValue);
    void RotateBlocks(int rotateValue);
    void MoveBlocks(const Vector2& moveValue);

    void UpdateTabs(void);

    // �ϐ�
    std::vector<std::unique_ptr<IBlock>> blockVector_;

    // ���S�_
    Vector2 pos_;
    // ���S�_��1�u���b�N�Ƃ��āA���u���b�N���L�΂���
    Vector2 radiusBlockCount_;

    int rotate_;

    std::vector<Tab_t> tabs_;

    // �͂ߍ��܂�Ă��邩�ǂ���
    bool isInPlace_;

    bool isMove_{};

public:
    // setter�Egetter
    inline void SetPos(const Vector2& pos) { pos_ = pos; }
    inline void SetRadius(const Vector2& radius) { radiusBlockCount_ = radius; }
    inline void SetRotate(int rotate) { rotate = rotate; }

    inline const Vector2& GetPos(void) { return pos_; }
    inline const Vector2& GetRadius(void) { return radiusBlockCount_; }
    inline int GetRotate(void) { return rotate_; }
};


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

    void Update(void);
    void Draw(void);

    void RegisterBlock(IBlock* ptr);
    void RegisterTab(bool isTab, int indexBlockVector,const Dir& dir); // PieceEntranceBlock�̒ǉ��֐�

private:
    void ChangeTabsDir(int changeValue); // tabs_��]�����X�V�p�֐�
    void RotateBlocks(int rotateValue); // �S�u���b�N��]���X�V�֐�
    void MoveBlocks(const Vector2& moveValue); // �S�u���b�N�ړ����X�V�֐�

    void UpdateTabs(void); // �S�u���b�N�ړ���tabs_���X�V�֐�
    void WriteBlockPos(void);

    // �ϐ�
    std::vector<std::unique_ptr<IBlock>> blockVector_;

    // ���S�_
    Vector2 pos_;
    // ���S�_��1�u���b�N�Ƃ��āA���u���b�N���L�΂���
    Vector2 radiusBlockCount_;

    int rotate_;

    std::vector<Tab_t> tabs_;

    /// ������debgu_info
    // �͂ߍ��܂�Ă��邩�ǂ���
    bool isInPlace_;

    bool isOperator_{};

public:
    // setter�Egetter
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


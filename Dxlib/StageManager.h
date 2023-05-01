#pragma once
#include "Piece.h"
#include <memory>
#include <vector>

class StageManager
{
public:
    // �֐�
    StageManager(void) {};

    void Update(void);
    void Draw(void);

private:
    // �ϐ�
    std::vector<std::vector<std::unique_ptr<IBlock>>> pieceVector2_;
};


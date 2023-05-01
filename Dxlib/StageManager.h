#pragma once
#include "Piece.h"
#include <memory>
#include <vector>

class StageManager
{
public:
    // ŠÖ”
    StageManager(void) {};

    void Update(void);
    void Draw(void);

private:
    // •Ï”
    std::vector<std::vector<std::unique_ptr<IBlock>>> pieceVector2_;
};


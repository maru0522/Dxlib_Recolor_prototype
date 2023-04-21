#include "Filter.h"
#include "StageManager.h"
#include "BlockFactory.h"

void Filter::CopyToFilter(void)
{
    //Stage* curStgPtr = StageManager::GetInstance()->GetStagePtr();

    //// くそ回りくどくてワロタ
    //switch (dir_)
    //{
    //case Filter::Direction::TOP:
    //    mapchip_[0][0] = std::make_unique<IBlock>(CutPointingBlock(-3, -1));
    //    mapchip_[0][1] = std::make_unique<IBlock>(CutPointingBlock(-3, 0));
    //    mapchip_[0][2] = std::make_unique<IBlock>(CutPointingBlock(-3, +1));
    //    mapchip_[1][0] = std::make_unique<IBlock>(CutPointingBlock(-2, -1));
    //    mapchip_[1][1] = std::make_unique<IBlock>(CutPointingBlock(-2, 0));
    //    mapchip_[1][2] = std::make_unique<IBlock>(CutPointingBlock(-2, +1));
    //    mapchip_[2][0] = std::make_unique<IBlock>(CutPointingBlock(-1, -1));
    //    mapchip_[2][1] = std::make_unique<IBlock>(CutPointingBlock(-1, 0));
    //    mapchip_[2][2] = std::make_unique<IBlock>(CutPointingBlock(-1, +1));
    //    break;
    //case Filter::Direction::RIGHT:
    //    break;
    //case Filter::Direction::BOTTOM:
    //    break;
    //case Filter::Direction::LEFT:
    //    break;
    //default:
    //    break;
    //}
}

IBlock* Filter::CutPointingBlock(int offsetY, int offsetX)
{
    IBlock* curBlockPtr{ StageManager::GetInstance()->GetStagePtr()->mapchip_[(int)basePointByElem_.y - offsetY][(int)basePointByElem_.x - offsetX] };
    IBlock::Type blockType{};

    // nullptrチェック
    if (curBlockPtr != nullptr)
        // 欲しい部分のブロックタイプ取得
        blockType = curBlockPtr->GetType();

    // コピー可能なブロックならそのブロックのインスタンスを返す。
    switch (blockType)
    {
    case IBlock::Type::STONE:
        //std::swap(curBlockPtr, std::make_unique<IBlock>());
        return BlockFactory::CreateBlock("STONE", curBlockPtr->GetPos());
        possibleMoveBlock_++;
        break;

    // nullptr or Type::NONE ~ Type::BASIC
    default:
        return BlockFactory::CreateBlock("NONE", curBlockPtr->GetPos());
        break;
    }
}

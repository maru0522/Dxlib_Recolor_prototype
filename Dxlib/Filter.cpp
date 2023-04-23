#include "Filter.h"
#include "StageManager.h"
#include "Input.h"
#include <DxLib.h>
#include "IBlock.h"
#include "StoneBlock.h"

Filter::Filter(Player* pPtr) :
    pPtr_(pPtr)
{
    Vector2 pos{ 0,0 };
    Vector2 radius{ IBlock::defaultRadius_,IBlock::defaultRadius_ };

    for (size_t y = 0; y < mapchip_.size(); y++) {
        for (size_t x = 0; x < mapchip_[0].size(); x++) {
            mapchip_[y][x] = std::make_unique<IBlock>(pos, radius);
        }
    }
}

void Filter::Update(void)
{
    Vector2 detectionOffset{ IBlock::defaultRadius_ - 1,IBlock::defaultRadius_ - 1 };

    basePointByElemX_ = float{ (pPtr_->GetPos().x + detectionOffset.x) / (IBlock::defaultRadius_ * 2) };
    basePointByElemY_ = float{ (pPtr_->GetPos().y + detectionOffset.y) / (IBlock::defaultRadius_ * 2) };

    UpdatePos();

    if (KEY::IsTrigger(KEY_INPUT_C)) CopyToFilter();
    if (KEY::IsTrigger(KEY_INPUT_P)) PlaceToMapchip();
}

void Filter::Draw(void)
{
    for (size_t y = 0; y < mapchip_.size(); y++) {
        for (size_t x = 0; x < mapchip_[0].size(); x++) {
            DrawBox(
                mapchip_[y][x]->GetPos().x - IBlock::defaultRadius_, mapchip_[y][x]->GetPos().y - IBlock::defaultRadius_,
                mapchip_[y][x]->GetPos().x + IBlock::defaultRadius_, mapchip_[y][x]->GetPos().y + IBlock::defaultRadius_,
                0xff0000, false
            );
            mapchip_[y][x]->Draw();
        }
    }

#ifdef _DEBUG
    DrawDebug();
#endif // _DEBUG

}

void Filter::CopyToFilter(void)
{
    switch (dir_)
    {
        // 上方向
    case Filter::Direction::TOP:
        //if (StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ - 3][basePointByElemX_ - 1]->GetType() == IBlock::Type::STONE) {
        //    mapchip_[0][0] = std::make_unique<StoneBlock>(StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ - 3][basePointByElemX_ - 1]->GetPos(), StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ - 3][basePointByElemX_ - 1]->GetRadius());
        //    StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ - 3][basePointByElemX_ - 1] = std::make_unique<IBlock>(StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ - 3][basePointByElemX_ - 1]->GetPos(), StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ - 3][basePointByElemX_ - 1]->GetRadius());
        //}

        //mapchip_[0][0] = CutPointingBlock(-3, -1);
        //mapchip_[0][1] = CutPointingBlock(-3, 0);
        //mapchip_[0][2] = CutPointingBlock(-3, 1);
        //mapchip_[1][0] = CutPointingBlock(-2, -1);
        //mapchip_[1][1] = CutPointingBlock(-2, 0);
        //mapchip_[1][2] = CutPointingBlock(-2, 1);
        //mapchip_[2][0] = CutPointingBlock(-1, -1);
        //mapchip_[2][1] = CutPointingBlock(-1, 0);
        //mapchip_[2][2] = CutPointingBlock(-1, 1);
        CheckMapchipAutoC(0, 0, -3, -1);
        CheckMapchipAutoC(0, 1, -3, 0);
        CheckMapchipAutoC(0, 2, -3, 1);
        CheckMapchipAutoC(1, 0, -2, -1);
        CheckMapchipAutoC(1, 1, -2, 0);
        CheckMapchipAutoC(1, 2, -2, 1);
        CheckMapchipAutoC(2, 0, -1, -1);
        CheckMapchipAutoC(2, 1, -1, 0);
        CheckMapchipAutoC(2, 2, -1, 1);
        break;

        // 右方向
    case Filter::Direction::RIGHT:
        //mapchip_[0][0] = CutPointingBlock(-1, 1);
        //mapchip_[0][1] = CutPointingBlock(-1, 2);
        //mapchip_[0][2] = CutPointingBlock(-1, 3);
        //mapchip_[1][0] = CutPointingBlock(0, 1);
        //mapchip_[1][1] = CutPointingBlock(0, 2);
        //mapchip_[1][2] = CutPointingBlock(0, 3);
        //mapchip_[2][0] = CutPointingBlock(1, 1);
        //mapchip_[2][1] = CutPointingBlock(1, 2);
        //mapchip_[2][2] = CutPointingBlock(1, 3);
        CheckMapchipAutoC(0, 0, -1, 1);
        CheckMapchipAutoC(0, 1, -1, 2);
        CheckMapchipAutoC(0, 2, -1, 3);
        CheckMapchipAutoC(1, 0, 0, 1);
        CheckMapchipAutoC(1, 1, 0, 2);
        CheckMapchipAutoC(1, 2, 0, 3);
        CheckMapchipAutoC(2, 0, 1, 1);
        CheckMapchipAutoC(2, 1, 1, 2);
        CheckMapchipAutoC(2, 2, 1, 3);
        break;

        // 下方向
    case Filter::Direction::BOTTOM:
        //mapchip_[0][0] = CutPointingBlock(1, -1);
        //mapchip_[0][1] = CutPointingBlock(1, 0);
        //mapchip_[0][2] = CutPointingBlock(1, 1);
        //mapchip_[1][0] = CutPointingBlock(2, -1);
        //mapchip_[1][1] = CutPointingBlock(2, 0);
        //mapchip_[1][2] = CutPointingBlock(2, 1);
        //mapchip_[2][0] = CutPointingBlock(3, -1);
        //mapchip_[2][1] = CutPointingBlock(3, 0);
        //mapchip_[2][2] = CutPointingBlock(3, 1);
        CheckMapchipAutoC(0, 0, 1, -1);
        CheckMapchipAutoC(0, 1, 1, 0);
        CheckMapchipAutoC(0, 2, 1, 1);
        CheckMapchipAutoC(1, 0, 2, -1);
        CheckMapchipAutoC(1, 1, 2, 0);
        CheckMapchipAutoC(1, 2, 2, 1);
        CheckMapchipAutoC(2, 0, 3, -1);
        CheckMapchipAutoC(2, 1, 3, 0);
        CheckMapchipAutoC(2, 2, 3, 1);
        break;

        // 左方向
    case Filter::Direction::LEFT:
        //mapchip_[0][0] = CutPointingBlock(-1, -1);
        //mapchip_[0][1] = CutPointingBlock(-1, -2);
        //mapchip_[0][2] = CutPointingBlock(-1, -3);
        //mapchip_[1][0] = CutPointingBlock(0, -1);
        //mapchip_[1][1] = CutPointingBlock(0, -2);
        //mapchip_[1][2] = CutPointingBlock(0, -3);
        //mapchip_[2][0] = CutPointingBlock(1, -1);
        //mapchip_[2][1] = CutPointingBlock(1, -2);
        //mapchip_[2][2] = CutPointingBlock(1, -3);
        CheckMapchipAutoC(0, 0, -1, -1);
        CheckMapchipAutoC(0, 1, -1, -2);
        CheckMapchipAutoC(0, 2, -1, -3);
        CheckMapchipAutoC(1, 0, -0, -1);
        CheckMapchipAutoC(1, 1, -0, -2);
        CheckMapchipAutoC(1, 2, -0, -3);
        CheckMapchipAutoC(2, 0, 1, -1);
        CheckMapchipAutoC(2, 1, 1, -2);
        CheckMapchipAutoC(2, 2, 1, -3);
        break;

    default:
        // 上方向
        for (size_t y = 0; y < mapchip_.size(); y++) {
            for (size_t x = 0; x < mapchip_[0].size(); x++) {
                mapchip_[y][x] = CutPointingBlock(y - 3, x - 1);
            }
        }
        break;
    }
}

void Filter::PlaceToMapchip(void)
{
    switch (dir_)
    {
        // 上方向
    case Filter::Direction::TOP:
        CheckMapchipAutoP(0, 0, -3, -1);
        CheckMapchipAutoP(0, 1, -3, 0);
        CheckMapchipAutoP(0, 2, -3, 1);
        CheckMapchipAutoP(1, 0, -2, -1);
        CheckMapchipAutoP(1, 1, -2, 0);
        CheckMapchipAutoP(1, 2, -2, 1);
        CheckMapchipAutoP(2, 0, -1, -1);
        CheckMapchipAutoP(2, 1, -1, 0);
        CheckMapchipAutoP(2, 2, -1, 1);
        break;

        // 右方向
    case Filter::Direction::RIGHT:
        mapchip_[0][0] = CutPointingBlock(-1, 1);
        mapchip_[0][1] = CutPointingBlock(-1, 2);
        mapchip_[0][2] = CutPointingBlock(-1, 3);
        mapchip_[1][0] = CutPointingBlock(0, 1);
        mapchip_[1][1] = CutPointingBlock(0, 2);
        mapchip_[1][2] = CutPointingBlock(0, 3);
        mapchip_[2][0] = CutPointingBlock(1, 1);
        mapchip_[2][1] = CutPointingBlock(1, 2);
        mapchip_[2][2] = CutPointingBlock(1, 3);
        break;

        // 下方向
    case Filter::Direction::BOTTOM:
        mapchip_[0][0] = CutPointingBlock(1, -1);
        mapchip_[0][1] = CutPointingBlock(1, 0);
        mapchip_[0][2] = CutPointingBlock(1, 1);
        mapchip_[1][0] = CutPointingBlock(2, -1);
        mapchip_[1][1] = CutPointingBlock(2, 0);
        mapchip_[1][2] = CutPointingBlock(2, 1);
        mapchip_[2][0] = CutPointingBlock(3, -1);
        mapchip_[2][1] = CutPointingBlock(3, 0);
        mapchip_[2][2] = CutPointingBlock(3, 1);
        break;

        // 左方向
    case Filter::Direction::LEFT:
        mapchip_[0][0] = CutPointingBlock(-1, -1);
        mapchip_[0][1] = CutPointingBlock(-1, -2);
        mapchip_[0][2] = CutPointingBlock(-1, -3);
        mapchip_[1][0] = CutPointingBlock(0, -1);
        mapchip_[1][1] = CutPointingBlock(0, -2);
        mapchip_[1][2] = CutPointingBlock(0, -3);
        mapchip_[2][0] = CutPointingBlock(1, -1);
        mapchip_[2][1] = CutPointingBlock(1, -2);
        mapchip_[2][2] = CutPointingBlock(1, -3);
        break;

    default:
        // 上方向
        for (size_t y = 0; y < mapchip_.size(); y++) {
            for (size_t x = 0; x < mapchip_[0].size(); x++) {
                mapchip_[y][x] = CutPointingBlock(y - 3, x - 1);
            }
        }
        break;
    }
}

void Filter::UpdatePos(void)
{
    switch (dir_)
    {
    case Filter::Direction::TOP:
        for (size_t y = 0; y < mapchip_.size(); y++) {
            for (size_t x = 0; x < mapchip_[0].size(); x++) {
                mapchip_[y][x]->SetPos({ (basePointByElemX_ + x - 1) * IBlock::defaultRadius_ * 2, (basePointByElemY_ + y - 3) * IBlock::defaultRadius_ * 2 });
            }
        }
        break;
    case Filter::Direction::RIGHT:
        for (size_t y = 0; y < mapchip_.size(); y++) {
            for (size_t x = 0; x < mapchip_[0].size(); x++) {
                mapchip_[y][x]->SetPos({ (basePointByElemX_ + x + 1) * IBlock::defaultRadius_ * 2, (basePointByElemY_ + y - 1) * IBlock::defaultRadius_ * 2 });
            }
        }
        break;
    case Filter::Direction::BOTTOM:
        for (size_t y = 0; y < mapchip_.size(); y++) {
            for (size_t x = 0; x < mapchip_[0].size(); x++) {
                mapchip_[y][x]->SetPos({ (basePointByElemX_ + x - 1) * IBlock::defaultRadius_ * 2, (basePointByElemY_ + y + 1) * IBlock::defaultRadius_ * 2 });
            }
        }
        break;
    case Filter::Direction::LEFT:
        for (size_t y = 0; y < mapchip_.size(); y++) {
            for (size_t x = 0; x < mapchip_[0].size(); x++) {
                mapchip_[y][x]->SetPos({ (basePointByElemX_ + x - 1) * IBlock::defaultRadius_ * 2, (basePointByElemY_ + y - 1) * IBlock::defaultRadius_ * 2 });
            }
        }
        break;
    default:
        break;
    }
}

std::unique_ptr<IBlock> Filter::CutPointingBlock(int offsetY, int offsetX)
{
    IBlock* curBlockPtr{ StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ + offsetY][basePointByElemX_ + offsetX].get() };
    Vector2 vec2DefRadius{ IBlock::defaultRadius_,IBlock::defaultRadius_ };

    // コピー可能なブロックならそのブロックのインスタンスを返す。
    switch (curBlockPtr->GetType())
    {
    case IBlock::Type::STONE:
        //std::swap(curBlockPtr, std::make_unique<IBlock>());
        //StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ + offsetY][basePointByElemX_ + offsetX] = BlockFactory::CreateBlock("NONE", curBlockPtr->GetPos());
        StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ + offsetY][basePointByElemX_ + offsetX] = std::make_unique<IBlock>(curBlockPtr->GetPos(), vec2DefRadius);
        possibleMoveBlock_++;
        //return BlockFactory::CreateBlock("STONE", curBlockPtr->GetPos());
        return std::make_unique<StoneBlock>(curBlockPtr->GetPos(), vec2DefRadius);
        break;

        // nullptr or Type::NONE ~ Type::BASIC
    default:
        //return BlockFactory::CreateBlock("NONE", curBlockPtr->GetPos());
        return std::make_unique<IBlock>(curBlockPtr->GetPos(), vec2DefRadius);
        break;
    }
}

void Filter::CheckMapchipAutoC(int mceY, int mceX, int offsetY, int offsetX)
{
    if (mapchip_[mceY][mceX]->GetType() != IBlock::Type::NONE) return;
    mapchip_[mceY][mceX] = CutPointingBlock(offsetY, offsetX);
}

std::unique_ptr<IBlock> Filter::PastePointingBlock(int mcElemY, int mcElemX)
{
    //// コピー可能なブロックならそのブロックのインスタンスを返す。
    //switch (mapchip_[mcElemY][mcElemX]->GetType())
    //{
    //case IBlock::Type::STONE:
    //    //std::swap(curBlockPtr, std::make_unique<IBlock>());
    //    mapchip_[mcElemY][mcElemX] = BlockFactory::CreateBlock("NONE", mapchip_[mcElemY][mcElemX]->GetPos());
    //    possibleMoveBlock_--;
    //    return BlockFactory::CreateBlock("STONE", mapchip_[mcElemY][mcElemX]->GetPos());
    //    break;

    //    // nullptr or Type::NONE ~ Type::BASIC
    //default:
    //    return BlockFactory::CreateBlock("NONE", mapchip_[mcElemY][mcElemX]->GetPos());
    //    break;
    //}

    //IBlock* curBlockPtr{ StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ + offsetY][basePointByElemX_ + offsetX].get() };
    Vector2 vec2DefRadius{ IBlock::defaultRadius_,IBlock::defaultRadius_ };

    // コピー可能なブロックならそのブロックのインスタンスを返す。
    switch (mapchip_[mcElemY][mcElemX]->GetType())
    {
    case IBlock::Type::STONE:
        //std::swap(curBlockPtr, std::make_unique<IBlock>());
        //StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ + offsetY][basePointByElemX_ + offsetX] = BlockFactory::CreateBlock("NONE", curBlockPtr->GetPos());
        //StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ + offsetY][basePointByElemX_ + offsetX] = std::make_unique<IBlock>(curBlockPtr->GetPos(), vec2DefRadius);
        //possibleMoveBlock_++;
        ////return BlockFactory::CreateBlock("STONE", curBlockPtr->GetPos());
        //return std::make_unique<StoneBlock>(curBlockPtr->GetPos(), vec2DefRadius);
        mapchip_[mcElemY][mcElemX] = std::make_unique<IBlock>(mapchip_[mcElemY][mcElemX]->GetPos(), vec2DefRadius);
        possibleMoveBlock_--;
        return std::make_unique<StoneBlock>(mapchip_[mcElemY][mcElemX]->GetPos(), vec2DefRadius);
        break;

        // nullptr or Type::NONE ~ Type::BASIC
    default:
        //return BlockFactory::CreateBlock("NONE", curBlockPtr->GetPos());
        return std::make_unique<IBlock>(mapchip_[mcElemY][mcElemX]->GetPos(), vec2DefRadius);
        break;
    }
}

void Filter::CheckMapchipAutoP(int mceY, int mceX, int offsetY, int offsetX)
{
    IBlock* curBlockPtr{ StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ + offsetY][basePointByElemX_ + offsetX].get() };
    if (curBlockPtr->GetType() != IBlock::Type::NONE) return;
    StageManager::GetInstance()->GetStagePtr()->mapchip_[basePointByElemY_ + offsetY][basePointByElemX_ + offsetX] = PastePointingBlock(mceY,mceX);
}

void Filter::DrawDebug(void)
{
    DrawFormatString(0, 0, 0xffffff, "basePointElemX: %d", basePointByElemX_);
    DrawFormatString(0, 20, 0xffffff, "basePointElemY: %d", basePointByElemY_);
    DrawFormatString(200, 0, 0xffffff, "basePointElemX * br * 2: %f", basePointByElemX_ * IBlock::defaultRadius_ * 2);
    DrawFormatString(200, 20, 0xffffff, "basePointElemY * br * 2: %f", basePointByElemY_ * IBlock::defaultRadius_ * 2);
    DrawFormatString(600, 0, 0xffffff, "pposX: %f", pPtr_->GetPos().x);
    DrawFormatString(600, 20, 0xffffff, "pposY: %f", pPtr_->GetPos().y);
    DrawFormatString(0, 40, 0xffffff, "possibleMoveBlock: %d", possibleMoveBlock_);
    switch (dir_)
    {
    case Filter::Direction::TOP:
        DrawFormatString(0, 60, 0xffffff, "direction: TOP");
        break;
    case Filter::Direction::RIGHT:
        DrawFormatString(0, 60, 0xffffff, "direction: RIGHT");
        break;
    case Filter::Direction::BOTTOM:
        DrawFormatString(0, 60, 0xffffff, "direction: BOTTOM");
        break;
    case Filter::Direction::LEFT:
        DrawFormatString(0, 60, 0xffffff, "direction: LEFT");
        break;
    default:
        DrawFormatString(0, 60, 0xffffff, "direction: UNKNOWN");
        break;
    }

    for (size_t y = 0; y < mapchip_.size(); y++) {
        for (size_t x = 0; x < mapchip_[0].size(); x++) {
            DrawFormatString(x * 280, y * 20 + 400, 0xffffff, "mcX/Y: %f,%f", mapchip_[y][x]->GetPos().x, mapchip_[y][x]->GetPos().y);
        }
    }
}

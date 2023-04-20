#include "StageManager.h"
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "StoneBlock.h"

void StageManager::Update(void)
{

}

void StageManager::Draw(void)
{
    int offsetX{ blockRadius_ + 10 };
    int offsetY{ blockRadius_ };

    for (size_t y = 0; y < mapchip_.size(); y++)
    {
        for (size_t x = 0; x < mapchip_[0].size(); x++)
        {
            switch (mapchip_[y][x])
            {
            case 0:
                DrawBox(
                    x * blockSize_ + offsetX, y * blockSize_ + offsetY,
                    (x + 1) * blockSize_ + offsetX, (y + 1) * blockSize_ + offsetY,
                    0xffffff, false
                );
                break;

            case 1:
                DrawBox(
                    x * blockSize_ + offsetX, y * blockSize_ + offsetY,
                    (x + 1) * blockSize_ + offsetX, (y + 1) * blockSize_ + offsetY,
                    0xff0000, false
                );
                break;

            case 2:
                DrawBox(
                    x * blockSize_ + offsetX, y * blockSize_ + offsetY,
                    (x + 1) * blockSize_ + offsetX, (y + 1) * blockSize_ + offsetY,
                    0x0000ff, false
                );
                break;

            default:
                break;
            }

        }
    }
}

//void StageManager::LoadCSV(Stage* ins, std::string csvPath)
//{
//    std::ifstream ifs{ csvPath };
//
//    std::string line, temp;
//    size_t loopY{};
//
//    while (std::getline(ifs, line)) {
//        std::istringstream line_stream{ line };
//        size_t loopX{};
//
//        while (std::getline(line_stream, temp, ',')) {
//            switch (std::stoi(temp))
//            {
//            case 0: // IBlock::Type::NONE
//                break;;
//
//            case 1: // IBlock::Type::STONE
//                ins->Register(new StoneBlock{ 
//                    {(float)loopX * blockDistance_ + defaultBlockPosOffset_,(float)loopY * blockDistance_ + defaultBlockPosOffset_}, // pos
//                    {defaultBlockSize_,defaultBlockSize_} } // size
//                );
//
//            default:
//                break;
//            }
//
//            loopX++;
//        }
//        loopY++;
//    }
//}

//void StageManager::Stage::Register(IBlock* p_block)
//{
//    blocks_.emplace_back(p_block);
//}
//
//void StageManager::Stage::Update(void)
//{
//    for (std::unique_ptr<IBlock>& i : blocks_) {
//        i->Update();
//    }
//}
//
//void StageManager::Stage::Draw(void)
//{
//    for (std::unique_ptr<IBlock>& i : blocks_) {
//        i->Draw();
//    }
//}

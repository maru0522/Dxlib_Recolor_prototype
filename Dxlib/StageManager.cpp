#include "StageManager.h"
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "BasicBlock.h"
#include "StoneBlock.h"

void StageManager::LoadCSV(Stage* ins, std::string csvPath)
{
    std::ifstream ifs{ csvPath };

    std::string line, temp;
    size_t loopY{};

    while (std::getline(ifs, line)) {
        std::istringstream line_stream{ line };
        size_t loopX{};

        while (std::getline(line_stream, temp, ',')) {
            switch (std::stoi(temp))
            {
            case 0: // IBlock::Type::NONE
                break;;

            case 1: // IBlock::Type::BASIC
                ins->Register(new BasicBlock{
                    {(float)loopX * blockDistance_ + defaultBlockPosOffset_,(float)loopY * blockDistance_ + defaultBlockPosOffset_}, // pos
                    {defaultBlockSize_,defaultBlockSize_} } // size
                );
                break;

            case 2: // IBlock::Type::STONE
                ins->Register(new StoneBlock{
                {(float)loopX * blockDistance_ + defaultBlockPosOffset_,(float)loopY * blockDistance_ + defaultBlockPosOffset_}, // pos
                {defaultBlockSize_,defaultBlockSize_}, // size
                Color::RED } // color
                );
                break;

            default:
                break;
            }

            loopX++;
        }
        loopY++;
    }
}

void StageManager::Stage::Register(IBlock* p_block)
{
    blocks_.emplace_back(p_block);
}

void StageManager::Stage::Update(void)
{
    for (std::unique_ptr<IBlock>& i : blocks_) {
        i->Update();
    }
}

void StageManager::Stage::Draw(void)
{
    for (std::unique_ptr<IBlock>& i : blocks_) {
        i->Draw();
    }
}



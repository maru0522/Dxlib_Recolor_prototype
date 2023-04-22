#include "StageManager.h"
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "Input.h"

StageManager* StageManager::GetInstance(void)
{
    static StageManager ins;
    return &ins;
}

void StageManager::Update(void)
{
    currentPtr_->Update();
}

void StageManager::Draw(void)
{
    currentPtr_->Draw();
}

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

void Stage::Update(void)
{
    //if (Input::Keyboard::IsDown(KEY_INPUT_W)) offsetY -= 2;
    //if (Input::Keyboard::IsDown(KEY_INPUT_S)) offsetY += 2;
    //if (Input::Keyboard::IsDown(KEY_INPUT_A)) offsetX -= 2;
    //if (Input::Keyboard::IsDown(KEY_INPUT_D)) offsetX += 2;

    for (IBlock* i : blocks_) {
        i->Update();
    }
}

void Stage::Draw(void)
{
    for (IBlock* i : blocks_) {
        i->Draw();
    }
}

void Stage::LoadCSV(std::string csvPath)
{
    std::ifstream ifs{ csvPath };

    std::string line, temp;
    size_t loopY{};

    while (std::getline(ifs, line)) {
        std::istringstream line_stream{ line };
        size_t loopX{};

        while (std::getline(line_stream, temp, ',')) {
            Vector2 pos{ (float)loopX * IBlock::defaultRadius_ * 2,(float)loopY * IBlock::defaultRadius_ * 2 };
            Vector2 radius{ IBlock::defaultRadius_,IBlock::defaultRadius_ };

            mapchip_.emplace_back(std::vector<std::unique_ptr<IBlock>>{});

            switch (std::stoi(temp))
            {
            case 0: // IBlock::Type::NONE
                mapchip_[loopY].emplace_back(BlockFactory::CreateBlock("NONE", pos, radius));
                break;

            case 1:
                mapchip_[loopY].emplace_back(BlockFactory::CreateBlock("BASIC", pos, radius));
                blocks_.emplace_back(mapchip_[loopY][loopX].get());
                break;
            case 2:
                mapchip_[loopY].emplace_back(BlockFactory::CreateBlock("STONE", pos, radius));
                blocks_.emplace_back(mapchip_[loopY][loopX].get());
                break;

            default:
                mapchip_[loopY].emplace_back(BlockFactory::CreateBlock("NONE", pos, radius));
                break;
            }
            loopX++;
        }
        loopY++;
    }
}

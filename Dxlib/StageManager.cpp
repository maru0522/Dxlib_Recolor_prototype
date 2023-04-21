#include "StageManager.h"
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "Input.h"

BlockFactory blockFactory;

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

    for (std::unique_ptr<IBlock>& i : blocks_) {
        i->Update();
    }
}

void Stage::Draw(void)
{
    for (std::unique_ptr<IBlock>& i : blocks_) {
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
            switch (std::stoi(temp))
            {
            case 0: // IBlock::Type::NONE
                break;

            case 1:
                blocks_.emplace_back(blockFactory.CreateBlock(
                    "BASIC",
                    { (float)loopX * IBlock::defaultRadius_ * 2,(float)loopY * IBlock::defaultRadius_ * 2 }
                ));
                break;

            default:
                break;
            }

            loopX++;
        }
        loopY++;
    }
}

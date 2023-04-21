#include "StageManager.h"
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "StoneBlock.h"
#include "Input.h"

void StageManager::Update(void)
{
    if (Input::Keyboard::IsDown(KEY_INPUT_W)) offsetY -= 2;
    if (Input::Keyboard::IsDown(KEY_INPUT_S)) offsetY += 2;
    if (Input::Keyboard::IsDown(KEY_INPUT_A)) offsetX -= 2;
    if (Input::Keyboard::IsDown(KEY_INPUT_D)) offsetX += 2;
}

void StageManager::Draw(void)
{

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

void StageManager::LoadCSV(std::string csvPath)
{
    std::ifstream ifs{ csvPath };

    std::string line, temp;
    size_t loopY{};

    while (std::getline(ifs, line)) {
        std::istringstream line_stream{ line };
        size_t loopX{};

        while (std::getline(line_stream, temp, ',')) {
            mapchip_[loopY][loopX] = std::stoi(temp);

            loopX++;
        }
        loopY++;
    }
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

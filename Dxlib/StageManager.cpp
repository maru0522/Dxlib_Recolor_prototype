#include "StageManager.h"
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include <iostream>
#include <algorithm>

void StageManager::Initialize(int width, int height)
{
    // ブロック
    mapchip_.resize(height);
    for (size_t i = 0; i < mapchip_.size(); i++) mapchip_.at(i).resize(width);
}

void StageManager::Update(void)
{

    ControllBlockNumber();

    int x{ MOUSE::GetPos().mx_ };
    int y{ MOUSE::GetPos().my_ };

    int mapchipElemX{}, mapchipElemY{};

    if (isResize_) Resize();
    else if (startPoint_.mx_ <= x && x <= endPoint_.mx_ &&
        startPoint_.my_ <= y && y <= endPoint_.my_) {

        // 要素数の算出
        mapchipElemX = int{ (x - startPoint_.mx_) / basicBlockSize_ };
        mapchipElemY = int{ (y - startPoint_.my_) / basicBlockSize_ };

        // 配列の要素数よりも大きかったり小さかったりしないかチェック
        if (0 <= mapchipElemX && mapchipElemX < (int)mapchip_[0].size() &&
            0 <= mapchipElemY && mapchipElemY < (int)mapchip_.size()) {

            debugElemCursor_.mx_ = mapchipElemX;
            debugElemCursor_.my_ = mapchipElemY;
        }
        //DrawFormatString(500, 80, 0xffffff, "blockNum: %d", mapchip_.at(mapchipElemY).at(mapchipElemX));

        if (KEY::IsDown(KEY_INPUT_SPACE)) {
            // 配列の要素数よりも大きかったり小さかったりしないかチェック
            if (0 <= mapchipElemX && mapchipElemX < (int)mapchip_[0].size() &&
                0 <= mapchipElemY && mapchipElemY < (int)mapchip_.size()) {

                // 対象のintをブロックの数字に書き換え
                mapchip_[mapchipElemY][mapchipElemX] = holdBlockNumber_;
            }
        }

        if (KEY::IsDown(KEY_INPUT_E)) {
            // 配列の要素数よりも大きかったり小さかったりしないかチェック
            if (0 <= mapchipElemX && mapchipElemX < (int)mapchip_[0].size() &&
                0 <= mapchipElemY && mapchipElemY < (int)mapchip_.size()) {

                // 対象のintを0に書き換え
                mapchip_[mapchipElemY][mapchipElemX] = 0;
            }
        }
    }

    if (KEY::IsDown(KEY_INPUT_W)) {
        startPoint_.my_ -= 5;
    }
    else if (KEY::IsDown(KEY_INPUT_S))
    {
        startPoint_.my_ += 5;
    }

    if (KEY::IsDown(KEY_INPUT_A)) {
        startPoint_.mx_ -= 5;
    }
    else if (KEY::IsDown(KEY_INPUT_D)) {
        startPoint_.mx_ += 5;
    }

    if (KEY::IsDown(KEY_INPUT_LSHIFT) && KEY::IsTrigger(KEY_INPUT_Q)) {
        ClearMapchip();
    }

    if (KEY::IsTrigger(KEY_INPUT_R)) {
        isResize_ = true;
    }

    if (KEY::IsDown(KEY_INPUT_LSHIFT) && KEY::IsTrigger(KEY_INPUT_RETURN)) {
        Export();
    }
}

void StageManager::Draw(void)
{
    DrawMapchip();
    DrawLattice();

    DrawBox(0, 0, 960, 80, 0x7c69bf, true);
    DrawDebug();
}

void StageManager::DrawLattice(void)
{
    // 縦線をx方向に増やす
    for (size_t i = 0; i <= mapchip_.at(0).size(); i++) {
        DrawLine(startPoint_.mx_ + i * basicBlockSize_, startPoint_.my_,
            startPoint_.mx_ + i * basicBlockSize_, startPoint_.my_ + mapchip_.size() * basicBlockSize_,
            0xffffff, 1);

        // 横線をy方向に増やす
        for (size_t i = 0; i <= mapchip_.size(); i++) {
            DrawLine(startPoint_.mx_, startPoint_.my_ + i * basicBlockSize_,
                startPoint_.mx_ + mapchip_.at(0).size() * basicBlockSize_, startPoint_.my_ + i * basicBlockSize_,
                0xffffff, 1);
        }
    }
}

void StageManager::DrawDebug(void)
{
    std::string holdStr{};
    switch (holdBlockNumber_)
    {
    case 0:
        holdStr = "AIR";
        break;

    case 1:
        holdStr = "BASIC";
        break;

    case 2:
        holdStr = "STONE";
        break;

    case 3:
        holdStr = "START";
        break;

    case 4:
        holdStr = "GOAL";
        break;

    case 5:
        holdStr = "COLLECT";
        break;

    case 6:
        holdStr = "RESPAWN";
        break;

    default:
        holdStr = "unknown";
        break;
    }

    DrawFormatString(0, 20, 0xffffff, "mapchip(x, y):     (%d, %d)", debugElemCursor_.mx_, debugElemCursor_.my_);
    DrawFormatString(0, 40, YELLOW, "startPoint_(x, y): (%d, %d)", startPoint_.mx_, startPoint_.my_);
    DrawFormatString(0, 60, YELLOW, "endPoint_(x, y):   (%d, %d)", endPoint_.mx_, endPoint_.my_);
    DrawFormatString(300, 0, 0xffffff, "holdBlockNumber[int]: %d", holdBlockNumber_);
    DrawFormatString(300, 20, 0xffffff, "holdBlockNumber[str]: %s", holdStr.c_str());
    DrawFormatString(300, 40, 0xffffff, "resizeVal_(x, y):     (%d, %d)", resizeVal_.mx_, resizeVal_.my_);
    DrawFormatString(300, 60, 0xffffff, "countExport_:         %d", countExport_);
    DrawFormatString(570, 0, 0xffffff, "Move:    [W][A][S][D]");
    DrawFormatString(570, 20, 0xffffff, "ReWrite: [SPACE]");
    DrawFormatString(570, 40, 0xffffff, "Erase:   [E]");
    DrawFormatString(570, 60, 0xffffff, "Clear:   [LSHIFT] + [Q]");
    DrawFormatString(810, 0, 0xffffff, "Resize: [R]");
    DrawFormatString(810, 20, 0xffffff, "Export: \n[LSHIFT]\n+ [RETURN]");
    //DrawFormatString(500, 100, 0xffffff, MOUSE::IsTrigger(MOUSE::Click::LEFT) ? "Left: ON" : "Left: OFF");
}

void StageManager::DrawMapchip(void)
{
    for (size_t y = 0; y < mapchip_.size(); y++) {
        for (size_t x = 0; x < mapchip_[0].size(); x++) {

            int blockcolor{};
            int circlecolor{};

            switch (mapchip_[y][x])
            {
            case 0:
                blockcolor = BLACK;
                break;

            case 1:
                blockcolor = WHITE;
                break;

            case 2:
                blockcolor = RED;
                break;

            case 3:
                blockcolor = GREEN;
                break;

            case 4:
                blockcolor = YELLOW;
                break;

            case 5:
                blockcolor = CYAN;
                break;

            case 6:
                blockcolor = MAGENTA;
                break;

            default:
                blockcolor = BLACK;
                break;
            }

            //DrawFormatString(800, 0, 0xffffff, "blockNum:%d", mapchip_[0][0]);

            DrawBox(x * basicBlockSize_ + startPoint_.mx_, y * basicBlockSize_ + startPoint_.my_,
                x * basicBlockSize_ + basicBlockSize_ + startPoint_.mx_, y * basicBlockSize_ + basicBlockSize_ + startPoint_.my_,
                blockcolor, 1);

            //if (mapchipObject_[y][x] != 0)
            //    DrawCircle(x * basicBlockSize_ + startPoint_.mx_ + basicBlockSize_ / 2,
            //        y * basicBlockSize_ + startPoint_.my_ + basicBlockSize_ / 2,
            //        basicBlockSize_ / 8,
            //        circlecolor, 1, 1);

            //DrawBox(
            //    startPoint_.mx_, // x1
            //    startPoint_.my_ - mapchip_.size() * basicBlockSize_, // y1
            //    startPoint_.mx_ + x * basicBlockSize_ + basicBlockSize_, // x2
            //    startPoint_.my_ - (mapchip_.size() - y) * basicBlockSize_ + basicBlockSize_, // y2
            //    color, true);
        }
    }

    DrawCircle(startPoint_.mx_, startPoint_.my_, 3, YELLOW, 1, 1);
    DrawCircle(endPoint_.mx_, endPoint_.my_, 3, YELLOW, 1, 1);
}

void StageManager::ClearMapchip(void)
{
    for (size_t y = 0; y < mapchip_.size(); y++) {
        for (size_t x = 0; x < mapchip_[0].size(); x++) {
            mapchip_[y][x] = 0;
        }
    }
}

void StageManager::Resize(void)
{
    // x
    resizeVal_.mx_ = KeyInputNumber(-500, -500, 500, 0, false);

    // y
    resizeVal_.my_ = KeyInputNumber(-500, -500, 500, 0, false);

    // ブロック
    mapchip_.resize(resizeVal_.my_);
    for (size_t i = 0; i < mapchip_.size(); i++) mapchip_[i].resize(resizeVal_.mx_);

    isResize_ = false;
}

void StageManager::Export(void)
{
    const std::string blockFileName{ "exportBlock" + std::to_string(countExport_) + ".csv" };
    const std::string objectFileName{ "exportObject" + std::to_string(countExport_) + ".csv" };
    std::ofstream ofs{};

    ofs.open(blockFileName, std::ios::out);
    for (size_t y = 0; y < mapchip_.size(); y++) {
        for (size_t x = 0; x < mapchip_[0].size(); x++) {
            if (x == mapchip_[0].size() - 1) {
                ofs << mapchip_[y][x];
            }
            else ofs << mapchip_[y][x] << ',';
        }
        ofs << std::endl;
    }
    ofs.close();

    //ofs.open(objectFileName, std::ios::out);
    //for (size_t y = 0; y < mapchipObject_.size(); y++) {
    //    for (size_t x = 0; x < mapchipObject_[0].size(); x++) {
    //        if (x == mapchipObject_[0].size() - 1) {
    //            ofs << mapchipObject_[y][x];
    //        }
    //        else ofs << mapchipObject_[y][x] << ',';
    //    }
    //    ofs << std::endl;
    //}
    //ofs.close();

    countExport_++;
}

void StageManager::ControllBlockNumber(void)
{
    if (KEY::IsTrigger(KEY_INPUT_1)) holdBlockNumber_ = 1;
    if (KEY::IsTrigger(KEY_INPUT_2)) holdBlockNumber_ = 2;
    if (KEY::IsTrigger(KEY_INPUT_3)) holdBlockNumber_ = 3;
    if (KEY::IsTrigger(KEY_INPUT_4)) holdBlockNumber_ = 4;
    if (KEY::IsTrigger(KEY_INPUT_5)) holdBlockNumber_ = 5;
    if (KEY::IsTrigger(KEY_INPUT_6)) holdBlockNumber_ = 6;
    if (KEY::IsTrigger(KEY_INPUT_7)) holdBlockNumber_ = 7;
    if (KEY::IsTrigger(KEY_INPUT_8)) holdBlockNumber_ = 8;
    if (KEY::IsTrigger(KEY_INPUT_9)) holdBlockNumber_ = 9;
}

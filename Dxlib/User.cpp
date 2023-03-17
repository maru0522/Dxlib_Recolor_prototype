#include "User.h"
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "Input.h"
#include "Player.h"
#include "Filter.h"

using KEY = Input::Keyboard;

User::User(std::string UserCsv)
{
    LoadCsv(UserCsv);
}

void User::Update(void)
{
    if (KEY::IsTrigger(KEY_INPUT_G)) isControllPlayer_ ? isControllPlayer_ = false : isControllPlayer_ = true;

    if (isControllPlayer_) {
        player_->Update(true);
        filter_->Update(false);
    }
    else {
        // player は [1 / perFrame] でしか Update() が実行されない
        if (fpsCounter_ % perFrame_ == 0) player_->Update(false);
        filter_->Update(true);
    }

    fpsCounter_++;
    if (fpsCounter_ >= 100000000) fpsCounter_ = 0; // 1,0000,0000 == 1億
}

void User::Draw(void)
{
    player_->Draw();
    filter_->Draw();
}

void User::LoadCsv(std::string UserCsv)
{
    std::ifstream ifs{ UserCsv };
    std::string line, temp;

    std::getline(ifs, line);
    if (line != "UserInfomation") return;

    size_t lineCount{ 1 };
    PlayerInfo_t pInfo{};
    FilterInfo_t fInfo{};

    while (std::getline(ifs, line)) {
        std::size_t wordCount{ 0 };

        // 各項目に沿って削除。重複部は流用可
        if (line.find("pos :") != std::string::npos) {
            line.erase(0, 5);
        }
        if (line.find("size :") != std::string::npos) {
            line.erase(0, 6);
        }
        if (line.find("moveSpeed :") != std::string::npos) {
            line.erase(0, 11);
        }
        if (line.find("jumpPower :") != std::string::npos) {
            line.erase(0, 11);
        }
        if (line.find("fallValue :") != std::string::npos) {
            line.erase(0, 11);
        }
        if (line.find("gravity :") != std::string::npos) {
            line.erase(0, 9);
        }
        if (line.find("color :") != std::string::npos) {
            line.erase(0, 7);
        }

        std::istringstream line_stream{ line };
        while (std::getline(line_stream, temp, ',')) {
            switch (lineCount)
            {
                // =====player=====
            case 3: // pos :float,float
                !wordCount ? pInfo.pos.x = std::stof(temp) : pInfo.pos.y = std::stof(temp);
                break;

            case 4: // size :float,float
                !wordCount ? pInfo.size.x = std::stof(temp) : pInfo.size.y = std::stof(temp);
                break;

            case 5: // moveSpeed :float
                pInfo.moveSpeed = std::stof(temp);
                break;

            case 6: // jumpPower :float
                pInfo.jumpPower = std::stof(temp);
                break;

            case 7: // fallValue :float
                pInfo.fallValue = std::stof(temp);
                break;

            case 8: // gravity :float
                pInfo.gravity = std::stof(temp);
                break;

            case 9: // color :color
                pInfo.color = CheckColor(temp);
                break;

                // =====filter=====
            case 12: // pos :float,float
                !wordCount ? fInfo.pos.x = std::stof(temp) : fInfo.pos.y = std::stof(temp);
                break;

            case 13: // size :float,float
                !wordCount ? fInfo.size.x = std::stof(temp) : fInfo.size.y = std::stof(temp);
                break;

            case 14: // moveSpeed :float,float
                fInfo.moveSpeed = std::stof(temp);
                break;

            case 15: // color :color
                fInfo.color = CheckColor(temp);
                break;

            default:
                break;
            }
            wordCount++;
        }
        lineCount++;
    }

    player_ = std::make_unique<Player>(pInfo.pos, pInfo.size, pInfo.moveSpeed, pInfo.jumpPower, pInfo.fallValue, pInfo.gravity, pInfo.color);
    filter_ = std::make_unique<Filter>(fInfo.pos, fInfo.size, fInfo.moveSpeed, fInfo.color);
}

Color User::CheckColor(std::string string)
{
    if (string == "red" || string == "Red" || string == "RED") {
        return Color::RED;
    }
    else if (string == "blue" || string == "Blue" || string == "BLUE") {
        return Color::BLUE;
    }
    else if (string == "green" || string == "Green" || string == "GREEN") {
        return Color::GREEN;
    }
    else if (string == "yellow" || string == "Yellow" || string == "YELLOW") {
        return Color::YELLOW;
    }
    else if (string == "magenta" || string == "Magenta" || string == "MAGENTA") {
        return Color::MAGENTA;
    }
    else if (string == "cyan" || string == "Cyan" || string == "CYAN") {
        return Color::CYAN;
    }
    else {
        return Color::RED;
    }
}

#include "User.h"
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "Input.h"
#include "Player.h"
#include "Filter.h"
#include "Util.h"

using KEY = Input::Keyboard;
using namespace Util::Math;

User::User(std::string UserCsv)
{
    LoadCsv(UserCsv);
}

void User::Update(void)
{
    // "G"�ő���Ώۂ��X�C�b�`
    if (KEY::IsTrigger(KEY_INPUT_G)) {
        // player.Update()���z������������s����Ȃ��悤�ɂ��邽�ߏ������B
        fpsCounter_ = 0;
        // ����ΏەύX�̏���
        if (isControllPlayer_ == false) {
            // �t�B���^�[ => �v���C���[
            isControllPlayer_ = true;
        }
        else if (isPlayerInsideFilter_ == false) { // �v���C���[���t�B���^�[�̓����ɂ��Ȃ���������
            // �v���C���[ => �t�B���^�[
            isControllPlayer_ = false;
        }
    }

    // �ǂ���̑�����s�����̔���
    if (isControllPlayer_) {
        // �v���C���[�̑�����s��
        player_->Update(true);
        filter_->Update(false);
    }
    else {
        // �t�B���^�[�̑�����s���B
        filter_->Update(true);
        player_->Update(false);
        // player �� [1 / perFrame] �ł��� Update() �����s����Ȃ�
        //if (fpsCounter_ % perFrame_ == 0) 
    }

    // �v���C���[���t�B���^�[���ɂ��邩�ǂ����Ď�
    CheckPlayerInsideFilter();

    // ���̑��̏���
    fpsCounter_++;
    if (fpsCounter_ >= 100000000) fpsCounter_ = 0; // 1,0000,0000 == 1��
}

void User::Draw(void)
{
    player_->Draw();
    filter_->Draw();

#ifdef _DEBUG
    DisplayDebug();
#endif // _DEBUG
}

void User::DisplayDebug(void)
{
    DrawFormatString(0, 400, 0xffffff, "WASD�ňړ�");
    DrawFormatString(0, 420, 0xffffff, "SPACE�ŃW�����v");
    DrawFormatString(0, 440, 0xffffff, "G�ő���ؑ�");
}

void User::CheckPlayerInsideFilter(void)
{
    if (isNegative<float>(std::abs(player_->GetPos().x - filter_->GetPos().x) - (player_->GetSize().x / 2 + filter_->GetSize().x / 2)) ||
        isNegative<float>(std::abs(player_->GetPos().y - filter_->GetPos().y) - (player_->GetSize().y / 2 + filter_->GetSize().y / 2))) {
        // �v���C���[���t�B���^�[���ɂ��邩�ǂ���
        isPlayerInsideFilter_ = true;
    }
    else isPlayerInsideFilter_ = false;
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

        // �e���ڂɉ����č폜�B�d�����͗��p��
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

    player_->SetFilterPtr(filter_.get());
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

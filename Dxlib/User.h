#pragma once
#include "Player.h"
#include "Filter.h"
#include <memory>
#include <string>

class User
{
private:
    // ��`
    struct PlayerInfo_t
    {
        Vector2 pos{};
        Vector2 size{};
        float moveSpeed{};
        float jumpPower{};
        float fallValue{};
        float gravity{};
        Color color{};
    };

    struct FilterInfo_t
    {
        Vector2 pos{};
        Vector2 size{};
        float moveSpeed{};
        Color color{};
    };

    // �萔
    static constexpr int32_t perFrame_{ 60 };

public:
    // �֐�
    User(std::string UserCsv);

    void Update(void);
    void Draw(void);

    void DisplayDebug(void);
private:
    void CheckPlayerInsideFilter(void);

    // UserCsv
    void LoadCsv(std::string UserCsv);

    Color CheckColor(std::string strings);

    // �ϐ�
    std::unique_ptr<Player> player_{ nullptr };
    std::unique_ptr<Filter> filter_{ nullptr };

    // ���݂̑���Ώۂ̓v���C���[��
    bool isControllPlayer_{ true };
    // �v���C���[���t�B���^�[���ɂ��邩
    bool isPlayerInsideFilter_{ false };

    int32_t fpsCounter_{};
};


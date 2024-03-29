#pragma once
#include "Player.h"
#include "Filter.h"
#include <memory>
#include <string>

class User
{
private:
    // 定義
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

    // 定数
    static constexpr int32_t perFrame_{ 60 };

public:
    // 関数
    User(std::string UserCsv);

    void Update(void);
    void Draw(void);

    void DisplayDebug(void);
private:
    // UserCsv
    void LoadCsv(std::string UserCsv);

    Color CheckColor(std::string strings);

    // 変数
    std::unique_ptr<Player> player_{ nullptr };
    std::unique_ptr<Filter> filter_{ nullptr };

    bool isControllPlayer_{ true };

    int32_t fpsCounter_{};
};


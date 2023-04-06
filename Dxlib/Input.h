#pragma once
#include <array>

namespace Input {
    class Keyboard
    {
    public: 
        // 関数
        static void Update(void);

        // 押した瞬間
        static bool IsTrigger(char key) { return !keysPre_[key] && keys_[key]; }

        // 押されているとき
        static bool IsDown(char key) { return keys_[key]; }

        // 離された瞬間
        static bool IsReleased(char key) { return keysPre_[key] && !keys_[key]; }

    private:
        // 変数
        static char keys_[256];
        static char keysPre_[256];
    };

    class Mouse
    {
    public:
        // 定義
        enum class Click
        {
            LEFT,
            RIGHT,
            CENTER,
        };

        struct IntXY_t
        {
            int mx_{};
            int my_{};
        };

        // 関数
        static void Update(void);

        // 押した瞬間
        static bool IsTrigger(const Click& clickSide) { return !buttonsPre_[static_cast<int>(clickSide)] && buttons_[static_cast<int>(clickSide)]; }

        // 押されているとき
        static bool IsDown(const Click& clickSide) { return buttons_[static_cast<int>(clickSide)]; }

        // 離された瞬間
        static bool IsReleased(const Click& clickSide) { return buttonsPre_[static_cast<int>(clickSide)] && !buttons_[static_cast<int>(clickSide)]; }

        // カーソルの座標取得
        static inline const IntXY_t& GetPos(void) { return pos_; }

    private:
        // 変数
        static IntXY_t pos_;
        static int mouseInput_;
        static char buttons_[3];
        static char buttonsPre_[3];
    };
}

using KEY = Input::Keyboard;
using MOUSE = Input::Mouse;
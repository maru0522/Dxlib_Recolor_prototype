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
}
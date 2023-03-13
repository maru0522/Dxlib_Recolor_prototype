#pragma once
#include <array>

namespace Input {
    class Keyboard
    {
    public: 
        // ŠÖ”
        static void Update(void);

        // ‰Ÿ‚µ‚½uŠÔ
        static bool IsTrigger(char key) { return !keysPre_[key] && keys_[key]; }

        // ‰Ÿ‚³‚ê‚Ä‚¢‚é‚Æ‚«
        static bool IsDown(char key) { return keys_[key]; }

        // —£‚³‚ê‚½uŠÔ
        static bool IsReleased(char key) { return keysPre_[key] && !keys_[key]; }

    private:
        // •Ï”
        static char keys_[256];
        static char keysPre_[256];
    };
}
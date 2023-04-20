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

    class Mouse
    {
    public:
        // ’è‹`
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

        // ŠÖ”
        static void Update(void);

        // ‰Ÿ‚µ‚½uŠÔ
        static bool IsTrigger(const Click& clickSide) { return !buttonsPre_[static_cast<int>(clickSide)] && buttons_[static_cast<int>(clickSide)]; }

        // ‰Ÿ‚³‚ê‚Ä‚¢‚é‚Æ‚«
        static bool IsDown(const Click& clickSide) { return buttons_[static_cast<int>(clickSide)]; }

        // —£‚³‚ê‚½uŠÔ
        static bool IsReleased(const Click& clickSide) { return buttonsPre_[static_cast<int>(clickSide)] && !buttons_[static_cast<int>(clickSide)]; }

        // ƒJ[ƒ\ƒ‹‚ÌÀ•Wæ“¾
        static inline const IntXY_t& GetPos(void) { return pos_; }

    private:
        // •Ï”
        static IntXY_t pos_;
        static int mouseInput_;
        static char buttons_[3];
        static char buttonsPre_[3];
    };
}

using KEY = Input::Keyboard;
using MOUSE = Input::Mouse;